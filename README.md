# CppCon 2022 Session - The ride with WebAssembly

This repo sets up all the working examples being taught in the session.

## Docker Setup

### One time setup

Please install docker & bash shell 

For mac can install docker using following:
```
brew install --cask docker
```

Build the docker with following command:

```
./app build
```

Run any example with following command:
```
./app console
python server.py > /dev/null &
http://localhost:8000
<make anything and reload the page on host machine localhost>
```

Running Chrome in SAB:
```
/Applications/Google\ Chrome\ Canary.app/Contents/MacOS/Google\ Chrome\ Canary --args --enable-features=SharedArrayBuffer
```