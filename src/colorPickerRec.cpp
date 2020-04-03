#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;
Rect selection;
bool selectObject=false;
Point origin;
Point Last;
Mat frame;
bool hasDown=false;

static void onMouse( int event, int x, int y, int, void* )
{
    if( selectObject )
    {
        selection.x = MIN(x, origin.x);
        selection.y = MIN(y, origin.y);
        selection &= Rect(0, 0, frame.cols, frame.rows);
    }
    switch( event )
    {
	case EVENT_MOUSEMOVE:
		selection.width = abs(x - origin.x);
		selection.height = abs(y - origin.y);
		selectObject = true;
		break;
    case EVENT_LBUTTONDOWN:
        origin = Point(x,y);
        selection = Rect(x,y,0,0);
        selectObject = true;
		hasDown = true;
        break;
    case EVENT_LBUTTONUP:
		origin = Point(-1,-1);
		hasDown = false;
        selectObject = false;
        break;
    }
}

int main(int argc, unsigned char* argv[])
{
    char c;

    //打开摄像头
//    VideoCapture cam(0);
//    if (!cam.isOpened())
//        return -1;

	frame = imread("../srcImg/frame0000.jpg");

	Mat cp,cp1;
	cp1=frame.clone();
    //建立窗口
	namedWindow("camera",1);//显示视频原图像的窗口

    //捕捉鼠标
	setMouseCallback("camera",onMouse,0);

	vector<Point> selectPoints;
	vector<Rect> rects;
    while(1)
    {
        //读取一帧图像
//        cam>>frame;
  
  		if(frame.empty())
            return -1;

		cp = frame.clone();
        //画出矩形框
		if(selectObject && hasDown)
		{
			rectangle(cp,selection,Scalar(255,0,0),3,8,0);//能够实时显示在画矩形窗口时的痕迹
		}
/*		if(hasDown)
		{
			for(int i=0;i<selection.height;i++)
			{
				for(int j=0;j<selection.width;j++)
				{
					selectPoints.push_back(Point(selection.x+i,selection.y+j));
				}
			}
		}
		for( auto point : selectPoints)
		{
			int blue = frame.at<Vec3b>(point)[0];
			int green = frame.at<Vec3b>(point)[1];
			int red = frame.at<Vec3b>(point)[2];
			printf("b=%d\t", blue);
			printf("g=%d\t", green);
			printf("r=%d\t", red);
			for (int len = 0; len < frame.rows; len++)
			{
				for (int yth = 0; yth < frame.cols; yth)
				{
				
					Point w = Point(yth, len);
					if (frame.at<Vec3b>(w)[0] == blue && frame.at<Vec3b>(w)[1] == green && frame.at<Vec3b>(w)[2] == red)
				{
					circle(cp1, w, 0.5, Scalar(255), 1);
				}

			}
		}	
		}*/
        //显示视频图片到窗口
		imshow("camera",cp);

    //    select.zeros();
        //键盘响应
        c=(char)waitKey(20);
        if(27==c)//ESC键
            return -1;
    }

    return 0;
}
