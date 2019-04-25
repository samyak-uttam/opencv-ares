#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>

using namespace std;
using namespace cv;

int main()
{
	const string img_file = "mountains.jpg";

	Mat input = imread(img_file, 1);
	// Check if we can open the file
	if (input.empty())
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	// Show the original and the result
	namedWindow("Original image", WINDOW_AUTOSIZE);
	imshow("Original image", input);

	// code for scaling of image
	Mat scaled_img, translated_img, rotated_img, pres_trans_img;
	resize(input, scaled_img, scaled_img.size(), 0.75, 0.75, INTER_NEAREST);
	namedWindow("Scaled image", WINDOW_AUTOSIZE);
	imshow("Scaled image", scaled_img);

	// code for translation of image
	double row = 25.0, col = 25.0 ;
	Mat translationMatrix = (Mat_<double>(2, 3) << 1, 0, col, 0, 1, row);
	warpAffine(input, translated_img,translationMatrix,input.size());
	namedWindow("Translated image", WINDOW_AUTOSIZE);
	imshow("Translated image", translated_img);

	// code for rotation of image
	double angle = 45;
	// get rotation matrix for rotating the image around its center in pixel coordinates
	Point2f center((input.cols - 1) / 2.0, (input.rows - 1) / 2.0);
	Mat rot = getRotationMatrix2D(center, angle, 1.0);
	Rect2f bbox = RotatedRect(Point2f(), input.size(), angle).boundingRect2f();
	// adjust transformation matrix
	rot.at<double>(0, 2) += bbox.width / 2.0 - input.cols / 2.0;
	rot.at<double>(1, 2) += bbox.height / 2.0 - input.rows / 2.0;
	warpAffine(input, rotated_img, rot, bbox.size());
	namedWindow("Rotated image", WINDOW_AUTOSIZE);
	imshow("Rotated image", rotated_img);

	// code for perspective transformation of image
	// Input Quadilateral or Image plane coordinates
	Point2f inputQuad[4];
	// Output Quadilateral or World plane coordinates
	Point2f outputQuad[4];
	// Lambda Matrix
	Mat lambda(2, 4, CV_32FC1);
	// Set the lambda matrix the same type and size as input
	lambda = Mat::zeros(input.rows, input.cols, input.type());
	// The 4 points that select quadilateral on the input , from top-left in clockwise order
	// These four pts are the sides of the rect box used as input 
	inputQuad[0] = Point2f(-30, -60);
	inputQuad[1] = Point2f(input.cols + 50, -50);
	inputQuad[2] = Point2f(input.cols + 100, input.rows + 50);
	inputQuad[3] = Point2f(-50, input.rows + 50);
	// The 4 points where the mapping is to be done , from top-left in clockwise order
	outputQuad[0] = Point2f(0, 0);
	outputQuad[1] = Point2f(input.cols - 1, 0);
	outputQuad[2] = Point2f(input.cols - 1, input.rows - 1);
	outputQuad[3] = Point2f(0, input.rows - 1);
	// Get the Perspective Transform Matrix i.e. lambda 
	lambda = getPerspectiveTransform(inputQuad, outputQuad);
	// Apply the Perspective Transform just found to the src image
	warpPerspective(input, pres_trans_img, lambda, pres_trans_img.size());
	//Display input and output
	namedWindow("Perspective transformated image", WINDOW_AUTOSIZE);
	imshow("Perspective transformated image", pres_trans_img);

	// Wait until the user presses any key
	waitKey(0);
	return 0;
}
