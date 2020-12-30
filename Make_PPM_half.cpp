#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void writePPM(const string& filename, const int width, const int height, const vector<int> buf);

int main()
{
	const string filename = "example3.PPM";

	// make an image
	const int image_width = 128;
	const int image_height = 128;

	vector<int> buffer(image_width * image_height * 3);

	for (int j = 0; j < image_height; j++)
	{
		for (int i = 0; i < image_width; i++)
		{
			const int offset = ((i + image_height * j) * 3);
			if (i < (image_width / 2))
			{
				buffer[offset] = 255;
				buffer[offset+1] = 0;
				buffer[offset+2] = 0;
			}
			else
			{
				buffer[offset] = 0;
				buffer[offset + 1] = 0;
				buffer[offset + 2] = 255;
			}
		}
	}

	// write to file
	writePPM(filename, image_width, image_height, buffer);

	return 0;
}

void writePPM(const string& filename, const int width, const int height, const vector<int> buf)
{
	ofstream ofile(filename);

	ofile << "P3\n" << width << " " << height << "\n255\n";

	for (int j = 0; j < height;j++)
	{
		for (int i = 0; i < width; i++)
		{
			const int offset = ((i + width * j) * 3);
			for (int c = 0; c < 3;c++)
			{
				ofile << buf[offset + c];
				if (i < width - 1 || c < 2)
				{
					ofile << " ";
				}
			}
		}
		ofile << "\n";
	}
	ofile << flush;
}
