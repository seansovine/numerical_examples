# C BMP Color-to-Grayscale Converter

This project is a C program that reads the data from a 24-bit
color BMP file, converts the image it contains to a grayscale
image, and then writes the grayscale image to a file.

**Note:** Bitmap represents pixels only using colors.
Specifically, 24-bit BMP uses the RGB system with one
byte per color red, green, and blue. But, there are
established formula's for converting RGB values to grayscale,
and we can represent grayscale values as

$$t \cdot (255, 255, 255) ~~~\text{with}~~ t \in [0, 1].$$

We will start with the formula mapping

$$(R, G, B) ~~\Rightarrow~~ (n, n, n)$$

where the greyscale value $n$ is given by

$$n = \lfloor 0.229 * R + 0.587 * G + 0.114 * B \rfloor.$$
