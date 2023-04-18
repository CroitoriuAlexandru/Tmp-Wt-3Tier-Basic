FROM ubuntu:latest

# install necesary tools
RUN apt-get update && apt-get install -y \
    git \
    cmake \
    build-essential \
    libboost-all-dev \
    zeroc-ice-all-dev

# Build step
RUN git clone https://github.com/emweb/wt.git wt && \
    cd wt/ && \
    mkdir build && \ 
    cd build/ && \
    cmake ../ && \
    make && \
    make install

RUN rm -fr /wt

RUN cp /usr/local/lib/libwt*.so.* /usr/lib/

# Launch the build command from the parent directory
# docker build -t wt:frontend -f frontend/Dockerfile .