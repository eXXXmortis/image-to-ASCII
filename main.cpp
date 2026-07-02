// imageToASCII.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <Windows.h>
#include <opencv2/opencv.hpp>

void createWindow(int width, int height) {
	_COORD coord;
	HANDLE hwindow = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = width;
	coord.Y = height;
	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height - 1;
	Rect.Right = width - 1;
	SetConsoleScreenBufferSize(hwindow, coord);
	SetConsoleWindowInfo(hwindow, TRUE, &Rect);
	std::string str = "mode con cols=" + std::to_string(width) + " lines=" + std::to_string(height);
	system(str.c_str());
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "enter an image path" << std::endl;
		return -1;
	}
	if (argc > 2) {
		std::cout << "there must be one argument" << std::endl;
		return -2;
	}
	std::string path = argv[1];
	int mywidth = 100; 
	float aspect = 11.0 / 24.0;
	//photo path
	//std::string path = "D:\\downloads\\firefox\\wrwr.jpg";
	cv::Mat image = cv::imread(path, cv::IMREAD_COLOR);

	if (image.empty()) {
		std::cout << "select a valid image!" << std::endl;
		return -3;
	}

	int im_width = image.size().width;
	int im_height = image.size().height;
	float imasp = (float)im_width / mywidth;
	int myheight = round(im_height * aspect / imasp);

	resize(image, image, { mywidth, myheight }, 0, 0, cv::INTER_NEAREST);
	createWindow(mywidth, myheight);

	char* screen = new char[mywidth * myheight + 1];
	for (int i = 0; i < mywidth * myheight + 1; i++) screen[i] = ' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	const char* gradient = " .:!/r(lZ4H9W8$@";

	for (int x = 0; x < image.rows; x++) {
		for (int y = 0; y < image.cols; y++) {
			cv::Vec3b pixel = image.at<cv::Vec3b>(x, y);
			int color = round((pixel[0] + pixel[1] + pixel[2]) / 3.0);
			screen[x * mywidth + y] = gradient[color / 16];
		}
	}

	while (1) WriteConsoleOutputCharacter(hConsole, screen, mywidth * myheight, { 0, 0 }, &dwBytesWritten);

	return 0;
}
