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
	bin/FFJPEG -b bin/images/David.bmp bin/Blur.bmp
	bin/FFJPEG -c 128 bin/images/David.bmp bin/Contrast.bmp
	bin/FFJPEG -g bin/images/David.bmp bin/Grayscale.bmp
	bin/FFJPEG -i 128 bin/images/David.bmp bin/Bright.bmp
	bin/FFJPEG -r bin/images/David.bmp bin/Reflect.bmp
	bin/FFJPEG -s bin/images/David.bmp bin/Sepia.bmp

# Delete compiled binaries and other files
clean:
	rm bin/*
