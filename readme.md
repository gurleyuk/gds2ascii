
GDS to ASCII Dump
====================

A GDS2 to ASCII converter (ascii dump) following the virtuoso 5.1 format.
The main objetctive is to use Cadence Virtuoso 6.1, which no longer has an ascii dump, with the Matthew Beckler's [cadence_converter](http://www.mbeckler.org/cadence_plot/) tool to generate svg images from virtuoso layouts. It is also possible to use with any other gds file.

To compile:
```
make
```

To clean the folder:
```
make clean
```

Converting a GDS 2 to ASCII Dump
```
./gds2ascii GDS_FILE > ASCIIDUMP_FILE
```
