CXX = gcc
CXXFLAGS = -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow

INC = -I include/
SRC = $(wildcard src/*/*.c)

all:
	$(CXX) $(CXXFLAGS) $(INC) $(SRC) example/FFJPEG.c -o bin/FFJPEG.exe -lm

run:
	@cmd /k "cd bin & FFJPEG.exe -b images/David.bmp Blur.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -c 128 images/David.bmp Contrast.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -g images/David.bmp Grayscale.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -i 128 images/David.bmp Bright.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -r images/David.bmp Reflect.bmp & exit"
	@cmd /k "cd bin & FFJPEG.exe -s images/David.bmp Sepia.bmp & exit"

clean:
	@cmd /k "cd bin & del * & exit"
