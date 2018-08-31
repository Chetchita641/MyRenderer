///////////////////////////////////////////////////////////////////////////////
// render.cpp
// vim: ts=8 sts=4 sw=4 noet

#include <stdio.h>
#include <stdint.h>

struct color {
    uint8_t _red;
    uint8_t _green;
    uint8_t _blue;

    color(uint8_t red, uint8_t green, uint8_t blue)
    {
	_red = red;
	_green = green;
	_blue = blue;
    }
};

struct surface {
    uint8_t* _data;
    size_t _stride;
    size_t _height;
    size_t _width;

    surface(uint8_t* data, size_t stride, size_t height, size_t width)
    {
	_data = data;
	_stride = stride;
	_height = height;
	_width = width;
    }
};

struct vertex {
    size_t _x;
    size_t _y;

    vertex(size_t x, size_t y)
    {
	_x = x;
	_y = y;
    }
};

void swap(size_t& a, size_t&b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

void DrawLine(size_t x0, size_t x1, size_t y, surface& s, color c)
{
    if (x0 > x1)
	swap(x0, x1);
    if (x0 < 0)
	x0 = 0;
    if (x1 > s._width)
	x1 = s._width;

    for (size_t x = x0; x < x1; ++x)
	*(color*)(s._data + y * s._stride + x * 3) = c;
}

void MakeBox(size_t x0, size_t y0, size_t x1, size_t y1, surface& s, color c)
{
    if (x0 > x1)
	swap(x0, x1);
    if (y0 > y1)
	swap(y0, y1);
    if (x0 < 0)
	x0 = 0;
    if (x1 > s._width)
	x1 = s._width;
    if (y0 < 0)
	y0 = 0;
    if (y1 > s._height)
	y1 = s._height;

    for (size_t y = y0; y < y1; ++y)
	DrawLine(x0, x1, y, s, c);

    return;
}

void DrawTriangle(vertex& v1, vertex& v2, vertex& v3, surface& s, color c)
{
    
    
    return;
}

int main (int argv, char** argc)
{
    uint8_t buf[800 * 640 * 3] = { 0 };
    surface s(buf, 800*3, 640, 800);

    color red(255, 0, 0);
    color green(0, 255, 0);
    color blue(0, 0, 255);
    
    //squares
    MakeBox(200, 100, 400, 300, s, red);
    MakeBox(500, 400, 600, 600, s, green);

    //triangles
    vertex v1(600, 100);
    vertex v2(700, 200);
    vertex v3(500, 200);
    DrawTriangle(v1, v2, v3, s, blue);

    
    FILE* f = fopen("out.ppm", "wb");
    fprintf(f, "P6\n800 640\n255\n");
    fwrite(buf, sizeof(buf), 1, f);
    fclose(f);
    return 0;    
}
