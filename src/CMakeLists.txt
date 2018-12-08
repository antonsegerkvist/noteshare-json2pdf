set(
  JSON2PDF_INCLUDE_DIRS
  "/usr/local/opt/mupdf"
)
set(
  PDF2PNG_INCLUDE_DIRS
  "/usr/local/opt/mupdf"
)
set(
  JSON2PDF_LINK_LIBRARIES
  "/usr/local/opt/mupdf/lib/libmupdf.a"
  "/usr/local/opt/mupdf/lib/libmupdf-third.a"
)
set(
  PDF2PNG_LINK_LIBRARIES
  "/usr/local/opt/mupdf/lib/libmupdf.a"
  "/usr/local/opt/mupdf/lib/libmupdf-third.a"
)

include_directories(
  ${JSON2PDF_INCLUDE_DIRS}
  ${PDF2PNG_INCLUDE_DIRS}
)

file(GLOB JSON2PDF_HDR json2pdf/*.h)
file(GLOB JSON2PDF_SRC json2pdf/*.c)

file(GLOB PDF2PNG_SRC pdf2png/*.h)
file(GLOB PDF2PNG_SRC pdf2png/*.c)

add_executable(json2pdf.out ${JSON2PDF_SRC} ${JSON2PDF_HDR})
target_link_libraries(json2pdf.out ${JSON2PDF_LINK_LIBRARIES})

add_executable(pdf2png.out ${PDF2PNG_SRC} ${PDF2PNG_HDR})
target_link_libraries(pdf2png.out ${PDF2PNG_LINK_LIBRARIES})