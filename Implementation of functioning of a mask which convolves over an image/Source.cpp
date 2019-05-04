#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include "iostream"
#include <stdio.h>

using namespace cv;
using namespace std;

int main()
{
	/// Declare variables
	Mat src, dst;

	Mat kernel;
	Point anchor = Point(-1, -1);
	double delta = 0;
	int ddepth = -1;
	int kernel_size;

	int c;

	const string img_file = "Lenna.png";

	/// Load an image
	src = imread(img_file, IMREAD_COLOR);

	if (!src.data)
	{
		cout << "could not load the image" << img_file << endl;
		return -1;
	}

	namedWindow("Masked Image", WINDOW_AUTOSIZE);

	/// Loop - Will filter the image with different kernel sizes each 0.5 seconds
	int ind = 0;
	while (true)
	{
		c = waitKey(500);
		/// Press 'ESC' to exit the program
		if ((char)c == 27)
		{
			break;
		}

		/// Update kernel size for a normalized box filter
		kernel_size = 3 + 2 * (ind % 5);
		kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size * kernel_size);

		/// Apply filter
		filter2D(src, dst, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
		imshow("Masked Image", dst);
		ind++;
	}

	return 0;
}