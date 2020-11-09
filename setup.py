import os
import re
import sys
import platform
import subprocess

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
from wheel.bdist_wheel import bdist_wheel
from distutils.version import LooseVersion


class CMakeExtension(Extension):
    def __init__(self, name, sourcedir=''):
        Extension.__init__(self, name, sources=[])
        self.sourcedir = os.path.abspath(sourcedir)


class CMakeBuild(build_ext):
    def run(self):
        try:
            out = subprocess.check_output(['cmake', '--version'])
        except OSError:
            raise RuntimeError("CMake must be installed to build the following extensions: " +
                               ", ".join(e.name for e in self.extensions))

        if platform.system() == "Windows":
            raise RuntimeError("Currently this pacakge has only been developed for Linux")

        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        extdir = os.path.abspath(os.path.dirname(self.get_ext_fullpath(ext.name)))
        # required for auto-detection of auxiliary "native" libs
        if not extdir.endswith(os.path.sep):
            extdir += os.path.sep

        cmake_args = ['-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=' + extdir,
                      '-DPYTHON_EXECUTABLE=' + sys.executable]

        cfg = 'Debug' if self.debug else 'Release'
        build_args = ['--config', cfg]

        if platform.system() == "Windows":
            raise RuntimeError("Currently this pacakge has only been developed for Linux")
        else:
            cmake_args += ['-DCMAKE_BUILD_TYPE=' + cfg]
            build_args += ['--', '-j2']

        env = os.environ.copy()
        env['CXXFLAGS'] = '{} -DVERSION_INFO=\\"{}\\"'.format(env.get('CXXFLAGS', ''),
                                                              self.distribution.get_version())
        if not os.path.exists(self.build_temp):
            os.makedirs(self.build_temp)
        subprocess.check_call(['cmake', ext.sourcedir] + cmake_args, cwd=self.build_temp, env=env)
        subprocess.check_call(['cmake', '--build', '.'] + build_args, cwd=self.build_temp)
                


class CMakeWheel(bdist_wheel):
    user_options = bdist_wheel.user_options + [
        ("skip-cmake-tests", None, "Skip the tests defined in CMakeLists.txt")
    ]
    boolean_options = bdist_wheel.boolean_options + ["skip_cmake_tests"]

    def initialize_options(self):
        bdist_wheel.initialize_options(self)
        self.skip_cmake_tests = False
        self.build_temp = None

    def finalize_options(self):
        bdist_wheel.finalize_options(self)
        self.set_undefined_options("build", ("build_temp", "build_temp"))

    def run(self):
        bdist_wheel.run(self)
        if not self.skip_cmake_tests:
            subprocess.check_call(['make', 'test'], cwd=self.build_temp)

        
setup(
    name='pyrational',
    version='0.0.1',
    author='Brian Walshe',
    author_email='walshe.brian@gmail.com',
    description='A test project using pybind11 and CMake',
    long_description='',
    ext_modules=[CMakeExtension('pyrational')],
    cmdclass=dict(bdist_wheel=CMakeWheel, build_ext=CMakeBuild),
    zip_safe=False,
    tests_require=['pytest']
)