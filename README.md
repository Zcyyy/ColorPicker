# ColorPicker  
The repository provides an ColorPicker that runs under ubuntu18.04 to extract pixel information from the image.
The current version relies on opencv4 and yaml-cpp. To use other opencv versions, you can modify CMakeLists.txt.

## Dependencies  
- yaml-cpp  
- opencv  
```sh
sudo apt-get install libyaml-cpp-dev
sudo apt-get install libopencv-dev #this This method installs opencv3.
```
## build  
```sh
git clone https://github.com/Zcyyy/ColorPicker.git  
cd ColorPicker  
mkdir build && cd build  
cmake ..
make
```

## TODOs:
  - [X] Pick r,g,b information
  - [X] Save information into .yaml file
  - [ ] Add image flow
  - [ ] Variable click radius
  - [ ] Add gui
