#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"

using namespace std;
using namespace cv;

int main()
{
	const string img_file = "mountains.jpg";
	Mat input = imread(img_file, IMREAD_COLOR);
	if (input.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	Mat sharpened_image, smoothened_image;
	GaussianBlur(input, sharpened_image, cv::Size(0, 0), 3);
	addWeighted(input, 1.5, sharpened_image, -0.5, 0, sharpened_image);

	namedWindow("Original image", WINDOW_AUTOSIZE);
	imshow("Original image", input);

	namedWindow("Sharpened image", WINDOW_AUTOSIZE);
	imshow("Sharpened image", sharpened_image);

	medianBlur(input, smoothened_image, 5);

	namedWindow("Smoothened image", WINDOW_AUTOSIZE);
	imshow("Smoothened image", smoothened_image);

	// Wait until the user presses any key
	waitKey(0);
	return 0;
}