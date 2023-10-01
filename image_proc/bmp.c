#include <locale.h>
#include <stdio.h> // For calloc.
#include <stdlib.h>
#include <string.h> // For strncpy.

#include "bmp.h"

/**
 *  Functions for working with
 *  BMP header data structures.
 */

BMPHeader *readHeader(FILE *fp) {
  // Dynamically allocate.
  BMPHeader *bmpHeader = (BMPHeader *)calloc(1, sizeof(struct BMPHeader));

  // Using this way as an example.
  char type[3] = {'\0', '\0', '\0'};
  fread(&type, 1, 2, fp);
  strncpy(bmpHeader->type, type, 3);

  fread(&bmpHeader->size, 4, 1, fp);
  // Ignore reserved fields.
  fseek(fp, 4, SEEK_CUR);
  fread(&bmpHeader->offset, 4, 1, fp);

  // Don't forget to free when finished.
  return bmpHeader;
}

BMPInfoHeader *readInfoHeader(FILE *fp) {
  BMPInfoHeader *infoHeader =
      (BMPInfoHeader *)calloc(1, sizeof(struct BMPInfoHeader));

  fread(&infoHeader->size, 4, 1, fp);
  fread(&infoHeader->width, 4, 1, fp);
  fread(&infoHeader->height, 4, 1, fp);
  fread(&infoHeader->planes, 2, 1, fp);
  fread(&infoHeader->bitcount, 2, 1, fp);
  fread(&infoHeader->compression, 4, 1, fp);
  fread(&infoHeader->sizeImage, 4, 1, fp);
  fread(&infoHeader->xPelsPerMeter, 4, 1, fp);
  fread(&infoHeader->yPelsPerMeter, 4, 1, fp);
  fread(&infoHeader->colorsUsed, 4, 1, fp);
  fread(&infoHeader->colorsImportant, 4, 1, fp);
  // We ignore remaining v5 header fields (for now).

  return infoHeader;
}

void printHeaderInfo(BMPHeader *bmpHeader, BMPInfoHeader *infoHeader) {
  // For comma thousands separators.
  setlocale(LC_NUMERIC, "");

  // File header info.
  printf("Type bytes: %s\n", bmpHeader->type);
  printf("Size of file: %'d bytes\n", bmpHeader->size);
  printf("Offset of pixel data: %'d\n", bmpHeader->offset);

  // Info header info.
  printf("\nInfo header size: %d (124 means BITMAPV5HEADER)\n",
         infoHeader->size);
  printf("Image width: %'d\n", infoHeader->width);
  printf("Image height: %'d\n", infoHeader->height);
  printf("Color planes: %d\n", infoHeader->planes);
  printf("Bit count: %d\n", infoHeader->bitcount);
  printf("Compression: %'d\n", infoHeader->compression);
  printf("Size of raw bitmap: %'d\n", infoHeader->sizeImage);
  printf("X pixels per meter: %'d\n", infoHeader->xPelsPerMeter);
  printf("Y pixels per meter: %'d\n", infoHeader->yPelsPerMeter);
  printf("Colors used: %'d (0 = max for bit count)\n", infoHeader->colorsUsed);
  printf("Important colors: %'d\n", infoHeader->colorsImportant);
}

Pixel *readPixels(BMPHeader *bmpHeader, BMPInfoHeader *infoHeader, FILE *fp) {
  // Rows are padded to a multiple of 4 bytes.
  size_t rowSize = (infoHeader->bitcount / 8) * infoHeader->width;
  size_t padding = (4 - rowSize % 4) % 4;

  size_t numPixels = infoHeader->width * infoHeader->height;
  Pixel *pixels = (Pixel *)calloc(numPixels, sizeof(struct Pixel));

  // TODO: Under construction.

  return pixels;
}
