# C++ binary with Python interpreter

## Reproducing this result

High level: you want to:
- compile Python from source
- copy the resulting library into this repo
- copy the required runtime dependencies over to this repo
- configure the environment to resolve the libraries, both inside and outside the program
- there may be other better ways, but this one works

### Compile Python from source
Download from source, e.g. https://www.python.org/downloads/release/python-386/
Unpack
```bash
cd <unpacked_folder>
mkdir out && cd out
../configure --enable-shared
make -j8
```
Done.

### Copy the resulting library and `pyconfig.h`
E.g.
```bash
cp <unpacked_folder>/out/libpython3.8.dylib ./3rdparty/python_interpreter/  # OSX
cp <unpacked_folder>/out/libpython3.8.so ./3rdparty/python_interpreter/  # Linux
cp <unpacked_folder>/out/pyconfig.h 3rdparty/python_interpreter/  # configuration header
```
You'll want to double-check you're copying the correct file. On Linux,
you can test this with
```bash
ldd <unpacked_folder>/out/python
```
because it will tell you which library the `python` binary will try to load.
If they can do it, you can. Note that if you didn't `configure` with `--enable-shared`,
this won't work because the `python` binary will statically link and have
no dependency.

### Copy the required runtime dependencies
Now, there are two dependencies that you both need to include because the
python shared library depends on them (I've had no success compiling the static library yet, as it needs to link correctly at compile time which I haven't managed):
1. C shared libraries
2. Python libraries

Both will be loaded at runtime. For instance, for OSX:
```bash
cp -r <unpacked_folder>/out/build/lib.macosx-10.15-x86_64-3.8 3rdparty/python_interpreter/  # C shared libraries
cp -r <unpacked_folder>/Lib 3rdparty/python_interpreter  # .py code
```
Check the `BUILD` file, as well as `main.cpp` to see how this code is used.

### Configure the environment
1. You need to tell the OS where to find the libraries that are being used by the program. On Linux, you might be able to use RPATH (Google). Alternatively, you can always add additional library paths, e.g., `LD_LIBRARY_PATH=3rdparty/python_interpreter ./main`. Use `DYLD_LIBRARY_PATH` on OSX.
2. The first step only makes sure the Python library you link directly gets found. Python seems to resolve its additional modules (whether written in C or in Python) at runtime, i.e. using `dlopen`. Therefore, in your binary, you'll need to set `PYTHONHOME` and `PYTHONPATH` to ensure everything loads as expected.

I have confirmed this simple test program works on OSX Catalina 10.15.6. It should be simple to follow these steps and create a version for Linux, too.
