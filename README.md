<!-- omit in toc -->
# Roman Numerals Converter

- [Description](#description)
- [Versions](#versions)
  - [Version 1.0.0](#version-100)
  - [Version 1.1.0](#version-110)


# Description

Simple **Qt Widgets** interface to manage the conversion between base 10 numbers and Roman numerals.

The back-end code for the actual conversion was previously developed to work from the command line, and was slightly adapted so that it could be easily integrated into a Qt Widgets context.

# Versions

This program exists in multiple consecutive releases, to illustrate its evolution and to learn the various facets of Qt Widgets programming along the way.

## Version 1.0.0

In this version the backend uses only the C++ standard library. The reason for this (instead of using the analogous Qt types) is that we imported an existing project that was originally command-line only. As a consequence, the output is command-line only in this initial version as well.

This is the simplest form of integration between our existing project and Qt.

## Version 1.1.0

In this version the result is presented in the GUI via `QLabel`. Errors are still presented on the command line.
