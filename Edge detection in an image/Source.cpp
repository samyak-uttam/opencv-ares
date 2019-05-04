
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;

int lowThreshold = 10;
const int ratio = 3;
const int kernel_size = 3;

int main()
{
	const std::string input= "mountains.jpg";
	Mat src, src_gray, dst, detected_edges;
	src = imread(input, IMREAD_COLOR);
	if (src.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		return -1;
	}

	dst.create(src.size(), src.type());
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	blur(src_gray, detected_edges, Size(3, 3));
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
	dst = Scalar::all(0);
	src.copyTo(dst, detected_edges);
	namedWindow("Original image", WINDOW_AUTOSIZE);
	imshow("Original image", src);
	
	namedWindow("Edges", WINDOW_AUTOSIZE);
	imshow("Edges", dst);

	waitKey(0);
	return 0;
}
