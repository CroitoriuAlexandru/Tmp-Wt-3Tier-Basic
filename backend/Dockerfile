FROM wt:wt as builder

COPY /comunication /comunication
COPY /backend /app
RUN cd comunication && make
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

COPY --from=builder /app /app
WORKDIR /app
CMD ./backend

# Launch the build command from the parent directory
# docker build -t wt:backend -f backend/Dockerfile .

# docker run -it -d -p 9090:9090 --name wt-app wt