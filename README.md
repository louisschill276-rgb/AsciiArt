# AsciiArt
Small C++ project to convert .pgm images into ASCII art, with support for a customizable character palette via a text file.
School project — S1.01, BUT Informatique.

# How to use

Build the solution in Visual Studio (`Ctrl+Shift+B`), then run from `x64/Debug/`:

in the cmd:
```
.\asciiart.exe --input image.pgm
.\asciiart.exe --input image.pgm --output result.txt --palette palette2.txt
.\asciiart.exe --help
```

Without `--input`, the program asks for a filename interactively.
Without `--output`, the result is printed to the console.

# Palettes

Four palette files are included. Each maps pixel brightness (0–255) to a character across 8 levels, from darkest to lightest. The default is `W w l i : , . ` — UTF-8 palettes give more detailed output.

A test image (`test_img.pgm`) is included to try it out.

# Authors

Julien Dupuis, Louis Schill
