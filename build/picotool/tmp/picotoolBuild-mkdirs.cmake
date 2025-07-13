# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/antonio/Documents/programming/C/ST7789V/build/_deps/picotool-src"
  "/home/antonio/Documents/programming/C/ST7789V/build/_deps/picotool-build"
  "/home/antonio/Documents/programming/C/ST7789V/build/_deps"
  "/home/antonio/Documents/programming/C/ST7789V/build/picotool/tmp"
  "/home/antonio/Documents/programming/C/ST7789V/build/picotool/src/picotoolBuild-stamp"
  "/home/antonio/Documents/programming/C/ST7789V/build/picotool/src"
  "/home/antonio/Documents/programming/C/ST7789V/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/antonio/Documents/programming/C/ST7789V/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/antonio/Documents/programming/C/ST7789V/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
