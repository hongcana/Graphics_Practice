#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void writePPM(const string& filename, const int width, const int height, const vector<int> buf);
// Blue Atoll (#00,B1,D2,FF) and Vibrant Yellow (#FD,DB,27,FF)

int main()
{
	const string filename = "example6.PPM";

	const int image_width = 128;
	const int image_height = 128;
	const int image_checker = 32;

	vector<int> buffer(image_width * image_height * 3);

	for (int j = 0; j < image_height; j++)
	{
		for (int i = 0; i < image_width; i++)
		{
			const int offset = ((i + image_height * j) * 3);
			if ((j / image_checker % 2) ^ (i / image_checker % 2))
			{
				buffer[offset] = 0xFD;
				buffer[offset + 1] = 0xDB;
				buffer[offset + 2] = 0x27;
			}
			else
			{
				buffer[offset] = 0x00;
				buffer[offset + 1] = 0xB1;
				buffer[offset + 2] = 0xD2;
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
				//if (i < width - 1 || c < 2)
				//{
				//	ofile << " ";
				//}
				ofile << " ";
			}
		}
		ofile << "\n";
	}
	ofile << flush;
}