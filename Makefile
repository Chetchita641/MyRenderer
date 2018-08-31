all: out.png

out.png: out.ppm
	pnmtopng out.ppm > out.png

out.ppm: render
	./render

render: render.cpp Makefile
	g++ -o render render.cpp -lhylaea -lpthread -std=c++11 -Werror -Wall
