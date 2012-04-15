# LuaSVG

A library load SVG files from paths.

## Supported SVG features

Currently it only supports paths.

## Tests

There is a LOVE project file called `svg_test`.
This crashes when ran on windows.

## Building

I have compiled this on a `mingw32` machine, so you might need to fiddle with stuff to get it working on other platforms.

Make sure you have a `lua` source at `../lua`

Now you should just do a:

    make

and you will either get a `.so` or a `.dll` file.
