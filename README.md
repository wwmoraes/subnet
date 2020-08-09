# subnet

> ip engineering CLI to help work with IPv4 sub-networks

## Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Contributing](../CONTRIBUTING.md)

## About <a name = "about"></a>

CLI tool that provides info about a CIDR provided, or test overlaps between two
provided CIDRs.

## Getting Started <a name = "getting_started"></a>

Clone the repository and run `make` or even run the sample with `make run`.

### Prerequisites

This is a simple and independent code, and thus requires only a C++ toolchain:

- clang/g++
- make
- glibc/musl or equivalent for your OS

There's also some phony targets to run valgrind, massif and heaptrack for performance
checks, and thus some optional dependencies:

- valgrind
- massif-visualizer
- heaptrack

### Installing

Currently there's no target that installs the tool. You can copy the compiled
`subnet` binary to any folder on your PATH to make it available system-wide.

## Usage <a name = "usage"></a>

To get info about a CIDR use

```shell
subnet 10.0.0.1/24
```

To check if two CIDRs overlap use

```shell
subnet 10.0.0.1/24 10.0.0.1/16
```
