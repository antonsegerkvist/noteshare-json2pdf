/*
Noteshare JSON 2 PDF generates a PDF and a set of previews from the specified
input.
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
  fz_document* document;

  // Check the command line input.
  if (argc != 3)
  {
    fprintf(stderr, "-->\n");
    fprintf(stderr, "--> usage: json2pdf [json] [output]\n");
    fprintf(stderr, "--> json: the json representing the PDF\n");
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

  // Create a new document.
  document = fz_new_document_of_size(ctx, 1024);

  // Clean up.
  fz_drop_document(ctx, document);
  fz_drop_context(ctx);
  return EXIT_SUCCESS;
}