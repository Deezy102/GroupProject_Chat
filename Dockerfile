#Totally stable

FROM postgres:latest
LABEL maintainer="https://github.com/Xacor"
ARG DEBIAN_FRONTEND=noninteractive



RUN apt-get update
RUN apt-get -y install build-essential qt5-default qtbase5-dev-tools qt5-qmake libqt5sql5-psql postgresql libpq5

ADD init.sql /docker-entrypoint-initdb.d
ADD chatr_server ./chatr_server



#Building server app
WORKDIR /chatr_server
RUN qmake -o Makefile chatr_server.pro
RUN make

EXPOSE 5432
EXPOSE 12345

#docker run -it -p 5432:5432 -p 12345:12345 -e POSTGRES_PASSWORD=password -e POSTGRES_USER=postgres -e POSTGRES_HOST_AUTH_METOD=trust serv