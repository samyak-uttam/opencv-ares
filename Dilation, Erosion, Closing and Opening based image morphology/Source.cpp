#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include "iostream"
#include <stdio.h>

using namespace std;
using namespace cv;

int erosion_size = 3;
int dilation_size = 3;
int morph_size = 3;

int main()
{
	const string img_file = "Lenna.png";

	Mat src, erosion_dst, dilation_dst, opening_dst, closing_dst;

	/// Load an image
	src = imread(img_file,IMREAD_COLOR);

	if (!src.data)
	{
		cout << "Can't open file " << img_file << endl;
		return -1;
	}

	// Create windows
	namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
	namedWindow("Dilation Demo", WINDOW_AUTOSIZE);
	namedWindow("Opening Demo", WINDOW_AUTOSIZE);
	namedWindow("Closing Demo", WINDOW_AUTOSIZE);

	// For Erosion
	Mat element1 = getStructuringElement(MORPH_RECT,
		Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		Point(erosion_size, erosion_size));

	erode(src, erosion_dst, element1);
	imshow("Erosion Demo", erosion_dst);

	// For Dilation
	Mat element2 = getStructuringElement(MORPH_RECT,
		Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		Point(dilation_size, dilation_size));

	dilate(src, dilation_dst, element2);
	imshow("Dilation Demo", dilation_dst);
	
	// For Opening
	int operation1 = 2;

	Mat element3 = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(src, opening_dst, operation1, element3);
	imshow("Opening Demo", opening_dst);

	// For Closing
	int operation2 = 3;

	Mat element4 = getStructuringElement(MORPH_RECT, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));
	morphologyEx(src, closing_dst, operation2, element3);
	imshow("Closing Demo", closing_dst);

	waitKey(0);
	return 0;
}