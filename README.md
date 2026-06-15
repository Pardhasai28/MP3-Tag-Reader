# MP3 Tag Reader and Editor

## Overview

MP3 Tag Reader and Editor is a command-line application developed in C to view and modify metadata stored in MP3 files using the ID3v2.3 tag format.

The application allows users to extract and update essential song information such as title, artist, album, year, composer, genre, and comments directly from the terminal.

This project demonstrates concepts including file handling, command-line argument processing, binary file manipulation, and endian conversion.

---

## Features

### View MP3 Metadata

Display the following information from an MP3 file:

* Song Title
* Artist Name
* Album Name
* Composer Name
* Year
* Genre
* Comments

### Edit MP3 Metadata

Modify the following ID3 tags:

* Title
* Artist
* Album
* Year
* Composer Name
* Content Type
* Genre

### Input Validation

* Verifies MP3 file extension (`.mp3`)
* Validates ID3 header presence
* Supports only ID3v2.3 tags
* Checks file availability before processing
* Validates year input before updating metadata

---

## Technologies Used

* Programming Language: C
* Standard Libraries:

  * stdio.h
  * string.h
  * stdlib.h
* Operating System: Linux
* Compiler: GCC

---

## Concepts Covered

* File Handling
* Binary File Processing
* Command-Line Arguments
* Structures and Modular Programming
* Endianness Conversion
* String Manipulation
* ID3v2.3 Metadata Format
* Memory Management

---

## Project Structure

```text
.
├── main.c
├── view.c
├── edit.c
├── common.h
├── common.c
├── Makefile
└── sample.mp3
```

---

## Supported ID3 Frames

| Tag Option | Frame ID | Description |
| ---------- | -------- | ----------- |
| `-t`       | `TIT2`   | Title       |
| `-a`       | `TPE1`   | Artist      |
| `-A`       | `TALB`   | Album       |
| `-y`       | `TYER`   | Year        |
| `-m`       | `TCOM`   | Composer    |
| `-c`       | `COMM`   | Comment     |
| `-g`       | `TCON`   | Genre       |

---

## Build Instructions

Compile the project using GCC:

```bash
gcc *.c -o mp3tag
```

Or use the Makefile:

```bash
make
```

---

## Usage

### View MP3 Tags

```bash
./mp3tag -v song.mp3
```

### Edit MP3 Tags

```bash
./mp3tag -e <tag_option> <new_value> <song.mp3>
```

Example:

```bash
./mp3tag -e -t "New Title" song.mp3
```

### Display Help

```bash
./mp3tag --help
```

---

## Sample Commands

Edit artist name:

```bash
./mp3tag -e -a "A. R. Rahman" song.mp3
```

Edit album name:

```bash
./mp3tag -e -A "Greatest Hits" song.mp3
```

Edit release year:

```bash
./mp3tag -e -y 2025 song.mp3
```

View metadata:

```bash
./mp3tag -v song.mp3
```

---

## Workflow

1. Read command-line arguments.
2. Validate MP3 file and ID3v2.3 header.
3. Identify the requested operation.
4. Read or update the selected frame.
5. Create a temporary file while editing.
6. Replace the original file with the updated version.
7. Display the operation status.

---

## Future Enhancements

* Support for ID3v2.4 tags
* Batch editing multiple MP3 files
* Album artwork extraction and editing
* Unicode metadata support
* Interactive menu-driven interface
* Graphical user interface (GUI)

---

## Author

**Pardha Sai**

GitHub: https://github.com/Pardhasai28

