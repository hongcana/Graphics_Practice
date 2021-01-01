#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void writePPM(const string& filename, const int&width, const int& height, const vector<uint8_t>& buf);

int main()
{
	const string filename = "example7.PPM";

	const int image_width = 128;
	const int image_height = 128;

	vector<uint8_t> buffer(image_width * image_height * 3);

	for (int j = 0; j < image_height; j++)
	{
		//using linear interpolation(선형 보간)
		const float alpha = (float)j / (image_height - 1); // 0.0f <= alpha <= 1.0f
		for (int i = 0; i < image_width; i++)
		{
			const int offset = (i + j*image_width) * 3;
			buffer[offset] = static_cast<uint8_t>(255 * (1.0f - alpha));
			buffer[offset + 1] = 0;
			buffer[offset + 2] = static_cast<uint8_t>(255 * alpha);
		}
	}

	// write to file
	writePPM(filename, image_width, image_height, buffer);

	return 0;
}

void writePPM(const string& filename, const int& width, const int& height, const vector<uint8_t>&buf)
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
				ofile << (int)buf[offset + c];
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
