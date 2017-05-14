# teletype

[![Build Status](https://travis-ci.org/monome/teletype.svg?branch=master)](https://travis-ci.org/monome/teletype)

monome eurorack module

http://monome.org/docs/modular/teletype

## Directories

- `src`: source code for the teletype algorithm
- `module`: `main.c` and additional code for the Eurorack module (e.g. IO and UI)
- `tests`: algorithm tests
- `simulator`: a (very) simple teletype command parser and simulator

## Building

See the [libavr32 repo][libavr32] for more detailed instructions. You will also need `ragel` installed and on the path, see below.

**Make sure that the `libavr32` submodule is correctly checked out**

```bash
cd module
make clean
make
./flash.sh
```

## Tests

To run the tests:

```bash
cd tests
make clean  # only needed if you've built the module code
make test
```

## Ragel

The [Ragel state machine compiler][ragel] is required to build the firmware. It needs to be installed and on the path:

```bash
brew install ragel  # Homebrew (OSX)
apt install ragel   # Debian / Ubuntu / WSL (Windows 10)
pacman -Sy ragel    # Arch Linux / MSYS2 (Windows)
```

Version 6.9 is known to work.

See section 6.3 in the Ragel manual for information on the `=>` scanner constructor used.

## Adding a new `OP` or `MOD` (a.k.a. `PRE`)

If you want to add a new `OP` or `MOD`, please create the relevant `tele_op_t` or `tele_mod_t` in the `src/ops` directory. You will then need to reference it in the following places:

- `src/ops/op.c`: add a reference to your struct to the relevant table, `tele_ops` or `tele_mods`. Ideally grouped with other ops from the same file.
- `src/ops/op_enum.h`: please run `utils/op_enums.py` to generate this file using Python3.
- `src/match_token.rl`: add an entry to the Ragel list to match the token to the struct. Again, please try to keep the order in the list sensible.

There is a test that checks to see if the above have all been entered correctly. (See above to run tests.)

## Code Formatting

To format the code using `clang-format`, run `make format` in the project's root directory. This *shouldn't* format any code in the `libavr32` submodule.

[libavr32]: https://github.com/monome/libavr32
[ragel]: http://www.colm.net/open-source/ragel/
