#!/bin/bash
set -e -u -x

function repair_wheel {
    wheel="$1"
    if ! auditwheel show "$wheel"; then
        echo "Skipping non-platform wheel $wheel"
    else
        auditwheel repair "$wheel" --plat manylinux2014_x86_64 -w /io/wheelhouse/
    fi
}


# Compile wheels
for PYBIN in /opt/python/*/bin; do
    "${PYBIN}/pip" wheel /io/ --no-deps -w wheelhouse/
done

# Bundle external shared libraries into the wheels
for whl in wheelhouse/*.whl; do
    repair_wheel "$whl"
done

# Install packages and test
for PYBIN in /opt/python/*/bin/; do
    "${PYBIN}/pip" install pyrational --no-index -f /io/wheelhouse
    ${PYBIN}/python3 -m pytest /io/tests/python/
done