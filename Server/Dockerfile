#Totally stable

FROM ubuntu:latest
LABEL maintainer="https://github.com/Xacor"
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get -y install build-essential qt5-default qtbase5-dev-tools qt5-qmake libqt5sql5-psql postgresql libpq5

ADD chatr_server ./chatr_server

#Building QPSQL Plugin

#Building server app
WORKDIR /chatr_server
RUN qmake -o Makefile chatr_server.pro
RUN make


EXPOSE 5432