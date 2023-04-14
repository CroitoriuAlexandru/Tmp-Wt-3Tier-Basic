FROM ubuntu:latest as builder

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

RUN cp /usr/local/lib/libwt*.so.* /usr/lib/

COPY . /app
WORKDIR /app
RUN make

# #################### Deployment image starts here ####################
FROM ubuntu:latest

# application dependencie libraries
RUN apt-get update && apt-get install -y \
    zeroc-ice-all-dev
# preferably tou can copy the libraries for zeroc ice from the builder image to this image

# copy libraries and application from builder
COPY --from=builder /usr/lib/libwt*.so.* /usr/lib/
COPY --from=builder /usr/include/boost/* /usr/include/boost/
COPY --from=builder /usr/lib/x86_64-linux-gnu/libboost* /usr/lib/x86_64-linux-gnu/

COPY --from=builder /app/resources /app/resources
COPY --from=builder /app/app /app
COPY --from=builder /app/wt_config.xml /app

WORKDIR /app
EXPOSE 9090
CMD ./app --docroot . -c ./wt_config.xml --http-address 0.0.0.0 --http-port 9090

# docker build . -t wt
# docker run -it -d -p 9090:9090 --name wt-app wt