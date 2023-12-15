# Meta Words

## Motivation

The library extracts a list of words with a timestamp and a duration from a given audio file. It uses OpenAIs whisper.cpp as a backend which can be exchanged easily.

## Getting Started

### Prerequisite

You need a clone of the [whisper.cpp repository](https://github.com/ggerganov/whisper.cpp.git). Build the ```whisper.cpp``` executable which is simply called ```main```.

### Clone And Build

```sh
git clone https://github.com/max-and-me/meta-words.git
mkdir build
cd build
cmake [OPTIONS] ../meta-words
cmake --build . 
```

### Run and Test

Open ```source/main.cpp``` and adapt the paths according to the cloned whisper repository. Build and run the executable.