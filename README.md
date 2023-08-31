A c++ project to show how to read a text file line by line, identify key words and extract specific information. The text file in this particular example contains a basketball game play-by-play report. The project uses some libraries from the boost set of C++ libraries, which is compatible with the C++ standard library in order to work with the file easily. To install the boost library, the vcpkg package manager can be used. 

As of Visual Studio 2022 version 17.6, visual studio has the vcpkg package included as an installable component, so you may also skip the manual package installation.
Let's see how to install the vcpkg manager. ( A short install path like: C:\src\vcpkg or C:\dev\vcpkg is recommended, since otherwise you may run into path issues for some port build systems.)

Step 1: Clone the vcpkg repo in the desired directory.
  clone git https://github.com/microsoft/vcpkg.git

Step 2: Run the bootstrap script to build vcpkg
  .\bootstrap-vcpkg.bat

Step 3 (optional): Make the vpckg libraries available to visual studio. 
  .\vcpkg integrate install

You can search for a particular library with the vcpkg manager and then install it. Here we want boost, so:
   .\vcpkg search boost
    .\vcpkg install boost

An input file is also uploaded in the repository, so the code can be tested.




