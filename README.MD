# Template 3 Tier Wt app 

## Instalation

Just folow the Dockerfile instructions and you are golden with one exception, the Wt libraries may not link after the install and there are two fixes for that
1. run the next command to dynamicly link to those binaries 
~~~
export LD_LIBRARY_PATH=/usr/local/lib/
~~~
2. run the next command to copy the wt library files from /usr/local/lib/ to /usr/lib/
~~~ 
cp /usr/local/lib/libwt*.so.* /usr/lib/
~~~

As an alternative you can run this as a docker app by running "make build", this will build a base image with wt, ice and all the other tools necesary for compiling the app, then it will create two more images, for frontend and backend and use the docker compose file to start them. you will be able to see the app on localhost:9095. If you want to change the port, you need to change it in the /frontend/Dockerfile, frontend/makefile and in docker-compose.yaml



