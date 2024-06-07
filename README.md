# Numerical Example Projects

_Note:_

These projects were done for fun while trying out some libraries
and algorithms hands-on, and the code hasn't been updated for a while. So
there's a good chance that many things could be done better, and I would
probably do some things differently if I redid them now.

For example, I would use a simple CMake build system for the C and C++ code.
And I might make a few different design and coding standards decisions
differently in the matrix library. One thing I would definitely do is
to use more concurrency to speed things up.

_Description:_

This repository contains example projects that I've created while learning
more computational mathematics. These projects are just for the sake of learning,
and the code in them is incomplete and less polished than what I would want for
production code. For real projects, I would use a well-maintained,
professional library when possible.

## `image_proc`

This folder is for image processing projects. Right now it contains a C program I've written that
reads a 24-bit BMP-formatted image file, following the BMP format spec, converts its pixels from color
to grayscale using a standard formula, and writes the converted image to a new file.

## `cpp_matrix`

This is a basic C++ matrix class template library, with some basic examples
of its use. I plan to use this library in code I write for other examples,
so I'll probably keep adding to it as time goes on.

See the project [README](./cpp_matrix/README.md).

## `diff_eq`

This folder contains projects for modeling with ordinary and partial differential equations
and computing and visualizing numerical approximations of their solutions.
