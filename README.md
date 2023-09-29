<!-- omit in toc -->
# Roman Numerals Converter

- [Description](#description)
- [Versions](#versions)
  - [Version 1.0.0](#version-100)
  - [Version 1.1.0](#version-110)
  - [Version 2.0.0](#version-200)
  - [Version 2.1.0](#version-210)
  - [Version 2.2.0](#version-220)
  - [Version 2.3.0](#version-230)
  - [Version 2.4.0](#version-240)
  - [Version 2.5.0](#version-250)


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

## Version 2.0.0

In this version the backend no longer uses the C++ standard library, but only Qt types.

## Version 2.1.0

The conversion algorithm has been improved with respect to version 2.0.0, replacing the `QMap`s with a single `QVector` of `QPair`s.

## Version 2.2.0

Adds the possibility to start the conversion by pressing the `ENTER` key.

## Version 2.3.0

Identical to 2.2.0, but with tabs. This is just an experiment in order to learn about tabs.

## Version 2.4.0

Evolves from 2.3.0 (without tabs).

Primitive version of *modal* pop-up (that is, blocking the execution of the program) with an error message in case the user enters invalid input. We still need to implement the message, the error recognition logic (using the return values of the conversion methods), and the connection between the `QDialogButtonBox` signals and error handling slots. See [here](https://doc.qt.io/qt-6/qdialogbuttonbox.html#details).

## Version 2.5.0

Evolution of version 2.4.0.
  - `QDialogButtonBox` has been linked to the `connect` function, and it now works as expected.
  - Implemented error recognition logic by adding `conversionError` signal, raised when a conversion error is detected.
  - Disabled debug print via `QT_NO_DEBUG_OUTPUT` macro in `CMakeLists.txt`.
  - Used `open` instead of `exec` as suggested [here](https://doc.qt.io/qt-6/qdialog.html#exec).

Information about modal pop-up windows:
- https://doc.qt.io/qt-6/qdialog.html#modal-dialogs

Documentation about the roles of `QDialogButtonBox`:
- https://doc.qt.io/qt-6/qdialogbuttonbox.html#ButtonRole-enum
- https://doc.qt.io/qt-6/qdialogbuttonbox.html#StandardButton-enum