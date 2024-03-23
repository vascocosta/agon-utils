# Agon Utils

My own set of common utilities for MOS on the Agon Light computer. These are only loosely based on the tools for Unix-like operating systems and try to keep an extremely minimalistic set of features. Specifically the options are limited to the absolutely necessary ones.

Following Agon Light's spirit, the tools are kept as simple as possible, favouring code correctness. This approach tends to avoid bugs while at the same time providing more readable code. Ideally the code should be understandable by beginner C programmers. As an admirer of the Rust programming language, this is something important.

## Utils

* echo
* grep
* head
* strings
* wc

More coming soon...

## Install

1. Download from the bin folder of each utility or all utils from a release.
2. Copy binaries into the `mos` folder inside your sd card (run as MOSlets).

## Deps

[CE C/C++ Toolchain](https://github.com/CE-Programming/toolchain)

[AgDev - an Agon Light port of CE C/C++ Toolchain](https://github.com/pcawte/AgDev)

## Build

```
cd util-folder
make clean
make
```

## Usage

### echo

```
Usage: %s [-hn] string
-h show this help message
-n supress trailing newline
```

### grep

```
Usage: %s [-hi] pattern filename
-h show this help message
-i case insensitive matching
```

### head

```
Usage: %s [-hn] filename
-h show this help message
-n print the first n lines (default: 10)
```

### strings

```
Usage: %s [-hn min-len] filename
-h show this help message
-n strings at least min-len long (default: 4)
```

### tail

```
Usage: %s [-hn] filename
-h show this help message
-n print the last n lines (default: 10)
```

### wc

```
Usage: %s [-chlw] filename
-c print the characters count
-h show this help message
-l print the lines count
-w print the words count
```