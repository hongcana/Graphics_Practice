#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void Make_imagefile(const string& fname, const int& width, const int& height, const vector<uint8_t>& pixel);

int main()
{
	const string filename = "Example_straight.PPM";

	const int image_width = 128;
	const int image_height = 128;

	vector<uint8_t> buffer(image_width * image_height * 3);

	for (int j = 0; j < image_height;j++)
	{
		for (int i = 0; i < image_width;i++)
		{
			const int offset = (i + j* image_width) * 3;
			if (j == 0 || j+1 == image_height || i == 0 || i+1 == image_width)
			{
				buffer[offset] = 0;
				buffer[offset + 1] = 0;
				buffer[offset + 2] = 0;
			}
			else if (i == j || ((image_width - (i+1)) == j))
			{
				buffer[offset] = 0;
				buffer[offset + 1] = 0;
				buffer[offset + 2] = 0;
			}
			else
			{
				buffer[offset] = 255;
				buffer[offset + 1] = 255;
				buffer[offset + 2] = 255;
			}
		}
	}

	Make_imagefile(filename, image_width, image_height, buffer);
}

void Make_imagefile(const string& fname, const int& width, const int& height, const vector<uint8_t>& pixel)
{
	ofstream ofile(fname);

	ofile << "P3\n" << width << " " << height << "\n255\n";

	for (int j = 0; j < height; ++j)
	{
		for (int i = 0; i < width; i++)
		{
			const int offset = (j + i * width) * 3;
			for (int c = 0; c < 3; c++)
			{
				ofile << (int)pixel[offset + c];
				ofile << " ";
			}
		}
	}

	ofile << flush;
}