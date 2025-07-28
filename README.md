# Image Filter Application

## Overview

This project is a command-line image processing tool that applies various filters to BMP images. It supports five different filters: grayscale, sepia, reflection, blur, and edge detection.

## Features

- **Grayscale**: Converts the image to black and white
- **Sepia**: Applies a vintage sepia tone to the image
- **Reflect**: Mirrors the image horizontally
- **Blur**: Applies a box blur effect to the image
- **Edges**: Detects and highlights edges in the image using the Sobel operator

## Requirements
- C compiler (GCC recommended)
- Standard C libraries
- Make (optional, for building)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/ranga-nir/filter-for-bmp-image-files.git
   cd image-filter
   ```

2. Compile the program:
   ```bash
   make
   ```
   or manually compile with:
   ```bash
   gcc -o filter filter.c helpers.c -lm
   ```

## Usage

```bash
./filter [flag] input.bmp output.bmp
```

Available flags:
- `-g` for grayscale
- `-s` for sepia
- `-r` for reflection
- `-b` for blur
- `-e` for edge detection

Example:
```bash
./filter -g input.bmp grayscale.bmp
```

## File Format Support

The program only supports 24-bit uncompressed BMP 4.0 format images.
