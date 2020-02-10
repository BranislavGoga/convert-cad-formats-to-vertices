# ModelConverter
## Covert STEP and IGES file formats to vertex mesh

Example conversion of STEP and IGES file formats to list of vertices using the OpenCascade Community edition library.

# Build

0. Build the OpenCascade package (https://github.com/BranislavGoga/OpenCascade) using Conan if yu do not have it in you local Conan repository. Follow the instructions in the repository GitHub.
1. Clone the repository.
2. Run the CMake, configure the build.
3. Change directory to the CMake`s build directory.
3.1 Expecting, that source directory is '../src' from the build directory, run:
```
conan install ../src
```
4. Generate the project files
5. Compile and run
