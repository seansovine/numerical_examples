#include <stdio.h>  // For FILE utilities.
#include <stdlib.h> // For EXIT_SUCCESS and EXIT_FAILURE.
#include <string.h> // For strlen.

#include "bmp.h"

/* Main. */

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Filename (with .bmp extension) must be passed as the only "
           "command-line argument to this utility.\n");
    exit(EXIT_FAILURE);
  }

  char *FILENAME = argv[1];

  // Declare dynamic variables.
  FILE *fp = NULL;
  BMPHeader *bmpHeader = NULL;
  BMPInfoHeader *infoHeader = NULL;
  PixelData *pixData = NULL;
  PixelData *gsPixData = NULL;

  if ((fp = fopen(FILENAME, "rb")) == NULL) {
    printf("Cannot open file: %s\n\n", FILENAME);
    exit(EXIT_FAILURE);
  }

  // Read headers and display info.
  bmpHeader = readHeader(fp);
  infoHeader = readInfoHeader(fp);
  printHeaderInfo(bmpHeader, infoHeader);

  // For now we only support 24-bit pixels.
  if (strcmp(bmpHeader->type, "BM") != 0 || infoHeader->bitcount != 24) {
    printf("Only 24-bit BMP files are accepted.");
    // We still need to deallocate some vars.
  } else {
    // Read pixel data and convert to grayscale.
    pixData = readPixels(bmpHeader, infoHeader, fp);
    gsPixData = convertToGrayscale(pixData);

    // Write result to "<FILENAME_NO_EXT>_grayscale.bmp";
    writeImageFile(fp, bmpHeader, infoHeader, gsPixData, FILENAME,
                   strlen(FILENAME));
  }

  // Clean-up.
  free(gsPixData->pixels);
  free(gsPixData);
  free(pixData->pixels);
  free(pixData);
  free(infoHeader);
  free(bmpHeader);
  fclose(fp);

  return EXIT_SUCCESS;
}

//  c && gcc -Wall convert_gs.c bmp.c -o build/convert_gs && echo "---"
//    && ./build/convert_gs sample.bmp
