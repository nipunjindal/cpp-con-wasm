#!/bin/bash

# This script simplifies running the docker compose configured services.

set -e

help() {
  echo "Commands for building, testing, and running a local typekit stack."
  echo
  echo "Commands:"
  echo "clean     Destroy all existing dependencies and compiled assets."
  echo "build     Build and install all dependencies from scratch."
  echo "start     Start the application stack."
  echo "stop      Stop the application stack."
  echo "console   Start an interactive console."
  echo "test      Run tests "
  echo
}

clean() {
  docker image rm \
    cppcon/wasm
}

build() {
  VERSION=latest
  docker build \
    --platform linux/amd64 \
    -t cppcon/wasm:$VERSION .
}

run() {
  docker run \
    --rm \
    -v `pwd`/:/build/ \
    --platform linux/amd64 \
    --entrypoint src/example1/entrypoint.sh \
    cppcon/wasm
}

console() {
  docker run \
    --rm -it\
    --platform linux/amd64 \
    -v `pwd`/:/build/ \
    --entrypoint /bin/bash \
    cppcon/wasm \
}

test() {
  #  No test added for now
  noop
}

main() {
  if [ "$1" = clean ]; then
    clean
  elif [ "$1" = build ]; then
    build
  elif [ "$1" = run ]; then
    run
  elif [ "$1" = console ]; then
    console
  elif [ "$1" = test ]; then
    shift
    test "$@"
  else
    help
  fi
}

(main "${@}")
