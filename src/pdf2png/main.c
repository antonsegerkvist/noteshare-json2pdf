/*
Noteshare PDF 2 PNG generates a set of previews to the specified pdf document.
*/

#include <stdio.h>
#include <stdlib.h>

#include <mupdf/fitz.h>

int main(int argc, char** argv)
{
  // Define the stack.
  char* input;
  float zoom, rotate;
  fz_context* ctx;

  // Check the command line input.
  if (argc != 3)
  {
    fprintf(stderr, "-->\n");
    fprintf(stderr, "--> usage: pdf2png [filename] [output]\n");
    fprintf(stderr, "--> filename: the filename of the PDF\n");
    fprintf(stderr, "--> output: the directory to put the output in\n");
    fprintf(stderr, "-->\n");
    return EXIT_FAILURE;
  }

  // Create a context to hold the exception stack and various caches.
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		fprintf(stderr, "--> could not create mupdf context\n");
		return EXIT_FAILURE;
	}

  // Clean up.
  fz_drop_context(ctx);
  return EXIT_SUCCESS;
}