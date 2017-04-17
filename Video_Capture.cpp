#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "opencv2/core/mat.hpp"
#include <cmath>
#include <ctime>
using namespace cv;
using namespace std;
Mat frame;
Mat roi_img;
int pos;
Mat src;
VideoCapture source=VideoCapture();
void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
static int count = 0;
static int x_coord1, x_coord2, y_coord1, y_coord2, offset_x,offset_y;
	if  ( event == EVENT_LBUTTONDOWN )
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		if(count == 0){
		  x_coord1 = x;
                  y_coord1 = y;
		  count = count+1; 
 		  line(src,Point(x_coord1 + 10,y_coord1),Point(x_coord1-10,y_coord1), Scalar(0,255,0), 2, 8, 0  );
        	  line(src,Point(x_coord1,y_coord1 + 10),Point(x_coord1,y_coord1-10), Scalar(0,255,0), 2, 8, 0  );
                  imshow("My Window", src);
		}
		
		else if(count == 1){
		  x_coord2 = x;
		  y_coord2 = y;
		  cout << "Left button of the mouse is clicked - position ("<< "x1 "<< x_coord1 << "y1 " << y_coord1 << ")" << endl;
		  cout << "Left button of the mouse is clicked - position (" <<"x2 " << x_coord2 << "y2 " << y_coord2 << ")" << endl;
		  line(src,Point(x_coord2 + 10,y_coord2),Point(x_coord2-10,y_coord2), Scalar(0,255,0), 2, 8, 0  );
        	  line(src,Point(x_coord2,y_coord2 + 10),Point(x_coord2,y_coord2-10), Scalar(0,255,0), 2, 8, 0  );
		  imshow("My Window", src);
		  offset_x = (x_coord2 - x_coord1);
                  offset_y = (y_coord2 - y_coord1);	
 		  count = 0;
		  Rect Rec(x_coord1, y_coord1,offset_x , offset_y);
		  Mat Roi = src(Rec);
		  imwrite("ROI.jpg",Roi);
		  namedWindow("ROI",WINDOW_NORMAL);  
                  imshow("ROI", Roi);
		}	              	
	}
}
static void onMouse(int event, int x, int y, int, void* ){

if( event == EVENT_LBUTTONUP ){
		waitKey(0);
		imshow("Video", frame);
		pos =getTrackbarPos("seek", "Video");
		source.set(CAP_PROP_POS_FRAMES, pos);		
		return;
	}
	else if(event == EVENT_RBUTTONDOWN){
		time_t now = time(0);
		string timeStamp=ctime(&now);
		string name = "Capture"+ timeStamp+".jpg";
		imwrite(name.c_str(),frame);
 		src = imread(name); 
		namedWindow("My Window",WINDOW_NORMAL); 
  		imshow("My Window", src);
                cout<<"Captured"<<endl;
		setMouseCallback("My Window", MouseCallBackFunc, 0 );
		
	}
}
int main(int argc, char **argv)
{	
	source=VideoCapture(argv[1]);
	if(!source.isOpened()) { // check if we succeeded
		cout<<"Open Failure"<<endl;        
		return -1;
	}
	int fc=source.get(CAP_PROP_FRAME_COUNT);
	namedWindow("Video",WINDOW_NORMAL);
	
	createTrackbar( "seek", "Video", &pos, fc);
	setMouseCallback("Video", onMouse, 0 );
	cout<<"frame height" << source.get(CV_CAP_PROP_FRAME_HEIGHT)<<"frame width "<<source.get(CV_CAP_PROP_FRAME_WIDTH)<<endl	;
	for(;;){

		source>>frame;
		pos=source.get(CAP_PROP_POS_FRAMES);
		if(frame.empty()){
			cout<<"EOF"<<endl;
			break;
		}
		setTrackbarPos("seek", "Video", pos);	
		imshow("Video", frame);
		waitKey(70);
	}
	source.release();
return 0;
}
