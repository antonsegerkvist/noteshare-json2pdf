/*
Noteshare PDF 2 PNG generates a set of previews to the specified pdf document.
*/

#include <stdio.h>
#include <stdlib.h>

#include <mupdf/fitz.h>

#include "png.h"

int main(int argc, char** argv)
{
  // Define the stack.
  char* input;
  char* output;
  float zoom, rotate;
  int i, page_count;
  fz_context* ctx;
  fz_document* doc;
  fz_page* page;
  fz_pixmap* pix;
  fz_colorspace* cs;

  // Check the command line input.
  if (argc != 3)
  {
    fprintf(stderr, "==>\n");
    fprintf(stderr, "==> Usage: pdf2png [filename] [output]\n");
    fprintf(stderr, "==> filename: the filename of the PDF\n");
    fprintf(stderr, "==> output: the directory to put the output in\n");
    fprintf(stderr, "==>\n");
    return EXIT_FAILURE;
  }

  input = argv[1];
  output = argv[2];
  zoom = 100;
  rotate = 0;

  // Create a context to hold the exception stack and various caches.
	ctx = fz_new_context(NULL, NULL, FZ_STORE_UNLIMITED);
	if (!ctx)
	{
		fprintf(stderr, "==> Could not create mupdf context\n");
		return EXIT_FAILURE;
	}

  // Register the default file types to handle.
	fz_try(ctx)
  {
		fz_register_document_handlers(ctx);
  }
  fz_catch(ctx)
	{
		fprintf(stderr, "==> %s\n", fz_caught_message(ctx));
		fz_drop_context(ctx);
		return EXIT_FAILURE;
	}

  // Open the document.
  fz_try(ctx)
  {
    doc = fz_open_document(ctx, input);
  }
  fz_catch(ctx)
  {
    fprintf(stderr, "==> %s\n", fz_caught_message(ctx));
		fz_drop_context(ctx);
		return EXIT_FAILURE;
  }

  // Count the number of pages.
  fz_try(ctx)
  {
    page_count = fz_count_pages(ctx, doc);
  }
  fz_catch(ctx)
  {
    fprintf(stderr, "==> %s\n", fz_caught_message(ctx));
    fz_drop_document(ctx, doc);
		fz_drop_context(ctx);
		return EXIT_FAILURE;
  }

  for (i = 0; i < page_count; ++i)
  {
    // Load the relevant page for the page.
    page = fz_load_page(ctx, doc, i);

    // Compute the bounding box for each page.
    fz_rect rect = fz_bound_page(ctx, page);
    fz_irect bbox = fz_round_rect(rect);

    // Create a display list that will hold the drawing commands for the page.
    fz_display_list* list = fz_new_display_list(ctx, rect);

    // Run the loaded page through a display list device to populate the
    // page's display list.
    fz_device* dev = fz_new_list_device(ctx, list);
    fz_run_page(ctx, page, dev, fz_identity, NULL);
    fz_drop_device(ctx, dev);
    fz_drop_page(ctx, page);

    // Create a white pixmap using the correct dimensions.
    pix = fz_new_pixmap_with_bbox(ctx, fz_device_rgb(ctx), bbox, NULL, 0xff);
    fz_clear_pixmap_rect_with_value(ctx, pix, 0xff, bbox);

    // Run the loaded display list through the draw device which will render
    // the request area of the page to the pixmap.
    dev = fz_new_draw_device(ctx, fz_identity, pix);
    printf("==> starting page rendering.\n");
    fz_run_display_list(ctx, list, dev, fz_identity, rect, NULL);
    printf("==> starting page rendering.\n");
    fz_close_device(ctx, dev);
    printf("==> starting page rendering.\n");
    fz_drop_device(ctx, dev);

    printf("==> starting page rendering.\n");

    // Write the rendered image to a PNG file.
    char filename[128];
    sprintf(filename, "%s/out%d.png", output, i);

    fz_save_pixmap_as_png(ctx, pix, filename);
    fz_drop_pixmap(ctx, pix);
    fz_drop_display_list(ctx, list);
  }

  // Clean up.
  fz_drop_document(ctx, doc);
  fz_drop_context(ctx);
  return EXIT_SUCCESS;
}