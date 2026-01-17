# grain-pre
This project is for learning purposes only.
=================================================================================

## Install & Packaging

This section shows how to generate build files, build the project, install it locally, and consume it from another CMake project using `find_package`.

### Generate and build

Use an out-of-source build directory. Example (cmake + Visual Studio multi-config):

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

For single-config generators (Ninja/Makefiles) you can set `CMAKE_BUILD_TYPE`:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Install locally

Install to the system or a local prefix. Example installing to `C:/Program Files` (requires admin) or to a local folder using `CMAKE_INSTALL_PREFIX`:

```powershell
cmake --install build --config Release --prefix "C:/local/install/path"
```

After install, the package config files will be placed under `${CMAKE_INSTALL_LIBDIR}/cmake/grain-pre` (e.g. `lib/cmake/grain-pre`).

### Packaging

CPack is configured in the project. To create a package (ZIP/installer), run:

```powershell
cmake --build build --config Release --target package
```

The produced package format depends on platform and CPack configuration.

### Consume via find_package

After installing (or if the package config directory is on `CMAKE_PREFIX_PATH`), downstream projects can use:

```cmake
find_package(grain-pre CONFIG REQUIRED)
add_executable(app src/main.cpp)
target_link_libraries(app PRIVATE grain-pre::grain-pre)
```

If you installed to a custom prefix, set `CMAKE_PREFIX_PATH` when configuring the consumer, e.g.:

```powershell
# PowerShell
cmake -S consumer -B build -DCMAKE_PREFIX_PATH="C:/local/install/path" 
```

---
