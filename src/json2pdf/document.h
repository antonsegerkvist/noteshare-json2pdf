#ifndef NJ2P_JSON_2_PDF_DOCUMENT_HPP
#define NJ2P_JSON_2_PDF_DOCUMENT_HPP

struct nj2p_document_metadata
{
  float page_height;
  float page_width;
};

struct nj2p_document_page
{
};

struct nj2p_document
{
  struct nj2p_document_metadata* metadata;
  struct nj2p_document_page* pages;
};

#endif // DOCUMENT_HPP