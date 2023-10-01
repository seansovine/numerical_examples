# C BMP Color-to-Grayscale Converter

This project will be a C program that, at least to begin with,
will read the data from a 24-bit color BMP file, convert
the image it contains to a grayscale image, and then writes
the grayscale image to a file.

**Note:** Bitmap represents pixels only using colors.
Specifically, 24-bit BMP uses the RGB system with one
byte per color red, green, and blue. But, there are
established formula's for converting RGB values to grayscale,
and we can represent grayscale values as

$$t \cdot (255, 255, 255) ~~~\text{with}~~ t \in [0, 1].$$
