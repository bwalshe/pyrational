FROM quay.io/pypa/manylinux2014_x86_64

RUN sh -x && for PYBIN in /opt/python/*/bin; do \
    "${PYBIN}/pip" install pytest ; \
    done

RUN git clone https://github.com/catchorg/Catch2.git \
 && cd Catch2 \
 && git checkout v2.x \
 && cmake -Bbuild -H. -DBUILD_TESTING=OFF \
 && cmake --build build/ --target install \
 && cd .. \
 && rm -rf Catch2

CMD ["/io/builld_wheels.sh"]