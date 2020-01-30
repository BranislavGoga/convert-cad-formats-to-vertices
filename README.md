# Covert STEP and IGES file formats to vertex mesh

Example conversion of STEP and IGES file formats to list of vertices using the OpenCascade Community edition library.

# Build

1. Build and install OpenCascade (e.g. 0.18.3 - https://github.com/tpaviot/oce) to the fixed path specified in CMakeFile.txt.
1.1 Clone the repository.
1.2 Run the CMake, configure the build.
2. Change directory to the CMake`s build directory.
2.1 Expecting, that source directory is '../src' from the build directory, run:
```
conan install ../src
```
3. Generate the project files
4. Compile and run
