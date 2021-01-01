#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
void Make_PPM(const string& fname, const vector<uint8_t>& pixel, const int& width, const int& height);

int main()
{
	//Write PPM
	const string filename = "Example_Sqaures.PPM";
	const int image_width = 128;
	const int image_height = 128;
	const int vector_width_start = 20;
	const int vector_width_end = 70;
	const int vector_height_start = 30;
	const int vector_height_end = 80;

	vector<uint8_t> buffer(image_width * image_height * 3);

	for (int j = 0; j < image_height;j++)
	{
		for (int i = 0; i < image_width;i++)
		{
			const int offset = (i + j * image_height) * 3;
			if ( (j >= vector_height_start) && (j <= vector_height_end) && (i>= vector_width_start) && (i<= vector_width_end))
			{
				buffer[offset] = 255;
				buffer[offset + 1] = 255;
				buffer[offset + 2] = 0;
			}
			else
			{
				buffer[offset] = 0xAD;
				buffer[offset + 1] = 0xEF;
				buffer[offset + 2] = 0xD1;
			}
		}
	}

	Make_PPM(filename, buffer, image_width, image_height);
	return 0;
}

void Make_PPM(const string& fname, const vector<uint8_t>& pixel, const int& width, const int& height)
{
	ofstream ofile(fname);

	ofile << "P3\n" << width << " " << height << "\n255\n";

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			const int offset = (i + j * width) * 3;
			for (int c = 0; c < 3; c++)
			{
				// uint8_t -> casting to int when ofile
				ofile << (int)pixel[offset + c];
				ofile << " ";
			}
		}
		ofile << "\n";
	}
	ofile << flush;
}