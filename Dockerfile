FROM emscripten/emsdk:3.1.20

WORKDIR /build

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
    vim

RUN apt-get install python3
RUN pip install bottle

EXPOSE 8000