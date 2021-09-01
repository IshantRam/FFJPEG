# Compiler and compiler option
CXX = gcc
CXXFLAGS = -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow

# Inclued and Source directory
INC = -I include/
SRC = $(wildcard src/*/*.c)

# Compile the FFJPEG
all:
	$(CXX) $(CXXFLAGS) $(INC) $(SRC) example/FFJPEG.c -o bin/FFJPEG -lm

# Run the FFJPEG
run:
	@cmd /k "cd bin & FFJPEG.exe -b images/BMP/David.bmp Blur.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -c 128 images/BMP/David.bmp Contrast.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -g images/BMP/David.bmp Grayscale.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -i 128 images/BMP/David.bmp Bright.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -r images/BMP/David.bmp Reflect.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -s images/BMP/David.bmp Sepia.bmp & exit"

# Delete compiled binaries and other files
clean:
	@cmd /k "cd bin & del * & exit"
