FROM spack/ubuntu-jammy:latest as builder

RUN mkdir /opt/spack-environment \
&&  (echo spack: \
&&   echo '  packages:' \
&&   echo '    all:' \
&&   echo '      target: [x86_64]' \
&&   echo '' \
&&   echo '  specs:' \
&&   echo '  - petsc+mpi ^openmpi' \
&&   echo '' \
&&   echo '  concretizer:' \
&&   echo '    unify: true' \
&&   echo '  config:' \
&&   echo '    install_tree: /opt/software' \
&&   echo '  view: /opt/views/view') > /opt/spack-environment/spack.yaml

RUN cd /opt/spack-environment && spack env activate . && spack install --fail-fast && spack gc -y
RUN cd /opt/spack-environment && spack env activate --sh -d . > activate.sh

FROM ubuntu:latest
LABEL NS-EOF=https://github.com/TUM-I5/NS-EOF

ENV FORCE_UNSAFE_CONFIGURE=1 \
DEBIAN_FRONTEND=noninteractive \
TZ=UTC \
DISPLAY=host.docker.internal:0.0 \
OMPI_ALLOW_RUN_AS_ROOT=1 \
OMPI_ALLOW_RUN_AS_ROOT_CONFIRM=1

COPY --from=builder /opt/spack-environment /opt/spack-environment
COPY --from=builder /opt/software /opt/software

# paths.view is a symlink, so copy the parent to avoid dereferencing and duplicating it
COPY --from=builder /opt/views /opt/views

RUN { \
      echo '#!/bin/sh' \
      && echo '.' /opt/spack-environment/activate.sh \
      && echo 'exec "$@"'; \
    } > /entrypoint.sh \
&& chmod a+x /entrypoint.sh \
&& ln -s /opt/views/view /opt/view

RUN apt-get update -y && apt-get upgrade -y && apt-get install -y --no-install-recommends --fix-missing \
software-properties-common \
apt-utils \
build-essential \
bash \
wget \
git \
curl \
ssh \
subversion \
tar \
unzip \
patch \
gzip \
bzip2 \
file \
gnupg \
coreutils \
mercurial \
nano \
pkg-config \
tree \
flex \
automake \
make \
cmake \
cmake-curses-gui \
ccache \
cppcheck \
libtool \
gcovr \
vim \
less \
meld \
gedit \
gdb \
strace \
linux-tools-common \
linux-tools-generic \
valgrind \
unifdef \
ninja-build \
meson \
graphviz \
iwyu \
doxygen \
xorg-dev \
mesa-utils \
mesa-common-dev \
freeglut3-dev \
ca-certificates \
libxml2-dev \
libbz2-dev \
libxslt1-dev \
libelf-dev \
libtbb-dev \
libtbb2 \
libsimde-dev \
libcurl4-openssl-dev \
libgl-dev \
libgl1-mesa-dev \
libglu1-mesa-dev \
libglvnd-core-dev \
libyaml-cpp-dev \
nodejs \
gcc \
g++ \
gfortran \
libgomp1 \
libnuma-dev \
libnuma1 \
g++-multilib \
gcc-multilib \
zlib1g \
zlib1g-dev \
python3 \
python3-dev \
python3-venv \
python3-pip && \
apt-get clean -y && \
apt-get autoremove -y && \
apt-get autoclean -y && \
rm -rf /var/lib/apt/lists/*

RUN python3 -m pip install --upgrade \
pip \
clang-format \
clang-tidy

ENTRYPOINT ["/entrypoint.sh"]
CMD ["/bin/bash"]