# Active Appearance Model

Active Appearance Model for OpenCV3. No other dependencies required.

---
>  :warning: :warning: The project is in progress  :warning: :warning:
---

## Prerequisites

- [x] OpenCV 4
- [x] CMake 3.14+
- [x] [Fmt](http://fmtlib.net/latest/usage.html#building-the-library)
- [x] [Backward CPP](https://github.com/bombela/backward-cpp) ~ in case of debugging mode

> NOTE: Even though the project is implemented with C++11, you don't have to install OpenCV3 with C++11 compatibility at all.

On OSX, you can install OpenCV with Homebrew with following command:

```bash
$ brew install opencv --with-ffmpeg --without-numpy --without-test --with-contrib --with-python3
```

---

## Making

All you need is executing the script:

```bash
$ ./make
```

Wait for the compilation to finish, you will have the final output 
of the library stored inside `/lib` directory.

---

## Testing

No need for the external suite, just compile the project and run:

```bash
$ bin/aam-test
```

Enjoy!

---

## Licence

[CopyLeft](https://en.wikipedia.org/wiki/Copyleft)
This software repository freely permits anybody to modify 
and/or redistribute the library as long as the release 
is also under CopyLeft licence.

---