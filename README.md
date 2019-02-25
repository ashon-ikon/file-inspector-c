# File Inspector
A light weight utility to help detect and manage duplicate files on user-space

## Inspiration
It's not uncommon these days to have duplicated files lying here and there and annoyingly taking much needed space. This utility hopes to clean this up

## Alogrithm (_in progress_)
This project seeks to employ very cost effective algorithm for sorting files within the file system and also making sure the memory is automatically allocated and deallocated as per the need. It grows or shrink as the need arise.

The conflict algorithm is designed in an extensible manner, more like a compiled "plug-in" approach which should enabled flexibility of use.
- Basic conflict search by filename and size ensures that files are sorted at insertion, and given a unique index (Hash Mapping). If the sizes of the files are within set match-threshold and first 3 characters don't match, then it is considered candidate for evaluation
- Quick conflict matching by comparing first few data bytes of the file. This algorithm uses `Merge Sort` and searching for extracting the first 16 bytes of the file, and then only considering these as candidates for evaluation

### Basic Setup
```bash
$ autoreconf --install
$ ./configure
$ make
$ make check
```

For more information on Library API please refer to [docs](./src/lib/README.md)
