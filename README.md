## 🪬 IMAGE TO ASCII
A C++ CLI tool that converts png/jpg images into ASCII art

## 🔨 How to Build?

#### Important❗❗❗ this project requires the **OpenCV** library

1. Clone the repository
```git clone https://github.com/eXXXmortis/image-to-ASCII.git```
```cd image-to-ASCII```

2. Create and enter a build directory
```mkdir build && cd build```

3. Configure the project using CMake
```cmake -DOpenCV_DIR="your path" ..```
replace "your path" with path that points to the folder containing 'OpenCVConfig.cmake'.

4. Compile the project
```cmake --build . --config Release```

## 💥 How to Use?

```imageToASCII.exe "path-to-image"```
replace "path-to-image" with the path to the image you want

