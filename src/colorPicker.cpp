#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<yaml-cpp/yaml.h>
#include<yaml-cpp/emitter.h>
#include<stdio.h>
#include<string>
#pragma warning(disable:4996) //解决sprintf出现error C4996问题

using namespace cv;
using namespace std;

class colorPicker{
	public:
		colorPicker();
		static void on_mouse(int event,int x, int y, int flags, void* ustc);
		Mat src;
		Mat temp1;
		Mat getMat();
		vector<int> getVec();
		static vector<int> pt;
		void makeclone();
		void run();
};

vector<int> colorPicker::pt;

colorPicker::colorPicker()
{
	src=imread("../srcImg/frame0000.jpg");
}

void colorPicker::on_mouse(int event, int x, int y, int flags, void*ustc){
	Mat image = *(Mat*)ustc;
	Mat image1 = *(Mat*)ustc;
	if (event == EVENT_LBUTTONDOWN)
	{
		Point p(x, y);
		int a = image1.at<Vec3b>(p)[0];
		int b = image1.at<Vec3b>(p)[1];
		int c = image1.at<Vec3b>(p)[2];
		printf("b=%d\t", a);
		printf("g=%d\t", b);
		printf("r=%d\t", c);
		pt.push_back(a);
		pt.push_back(b);
		pt.push_back(c);
		for (int i = 0; i < image.rows; ++i)
		{
			for (int j = 0; j < image.cols; ++j)
			{
				
				Point w = Point(j, i);
					if (image.at<Vec3b>(w)[0] == a && image.at<Vec3b>(w)[1] == b )
				{
					circle(image, w, 0.5, Scalar(255), 1);
				}
			}
		}
	}
}

vector<int> colorPicker::getVec()
{
	return pt;
}

Mat colorPicker::getMat()
{
	return src;
}

void colorPicker::run()
{
	namedWindow("img", WINDOW_AUTOSIZE);
	Mat org = getMat();
	while(waitKey(30) != 27)
	{
		temp1 = src.clone();
		setMouseCallback("img", on_mouse, (void*)&org);	
		imshow("img", temp1);
	}
}
//TODO::用vector存数据，最后在一组一组提取并且写入。
int main()
{
	vector<int> pts;
	YAML::Node config;
	
    colorPicker cp;
	cp.run();
	pts = cp.getVec();	
	for(int i = 0; i<pts.size();i=i+3){
		printf("points is at: \n");
		printf("%d\n",pts.at(i));
		config["color_values"]["greenField"]["red"].push_back(pts.at(i+2));	
		config["color_values"]["greenField"]["green"].push_back(pts.at(i+1));
		config["color_values"]["greenField"]["blue"].push_back(pts.at(i));
	}
	config["color_values"]["greenField"]["red"].SetStyle(YAML::EmitterStyle::Flow);
    config["color_values"]["greenField"]["green"].SetStyle(YAML::EmitterStyle::Flow);
    config["color_values"]["greenField"]["blue"].SetStyle(YAML::EmitterStyle::Flow);
	ofstream file("../config.yaml");
	file << config << endl;
	return 0;
}























