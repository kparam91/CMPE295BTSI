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
int H, S, V, R, G, B;
int R_MIN = 0;
int R_MAX = 255;
int G_MIN = 0;
int G_MAX = 255;
int B_MIN = 0;
int B_MAX = 255;
Mat roi_img;
int pos;
Mat src;
Mat1b mask1;
Mat3b res;
Mat3b Black_img(src.rows,src.cols,Vec3b(255,255,25));
int R_high =0, R_low =0, G_high =0, G_low =0, B_high =0, B_low =0; 
const string trackbarWindowName = "Trackbars";
VideoCapture source=VideoCapture();
char TrackbarName_r[3] = "R";
char TrackbarName_g[3] = "G";
char TrackbarName_b[3] = "B";
void createTrackbars() 
{
	namedWindow(trackbarWindowName, 0);     	
        createTrackbar(TrackbarName_r, trackbarWindowName, &R_MIN, R_MAX);
	createTrackbar(TrackbarName_g, trackbarWindowName, &G_MIN, G_MAX);
	createTrackbar(TrackbarName_b, trackbarWindowName, &B_MIN, B_MAX);
}


void MouseCallBackCropFunc(int event, int x, int y, int flags, void* userdata)
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
 		  line(Black_img,Point(x_coord1 + 10,y_coord1),Point(x_coord1-10,y_coord1), Scalar(0,255,0), 2, 8, 0  );
        	  line(Black_img,Point(x_coord1,y_coord1 + 10),Point(x_coord1,y_coord1-10), Scalar(0,255,0), 2, 8, 0  );
                  imshow("My Window", Black_img);
		}
		
		else if(count == 1){
		  x_coord2 = x;
		  y_coord2 = y;
		  cout << "Left button of the mouse is clicked - position ("<< "x1 "<< x_coord1 << "y1 " << y_coord1 << ")" << endl;
		  cout << "Left button of the mouse is clicked - position (" <<"x2 " << x_coord2 << "y2 " << y_coord2 << ")" << endl;
		  line(Black_img,Point(x_coord2 + 10,y_coord2),Point(x_coord2-10,y_coord2), Scalar(0,255,0), 2, 8, 0  );
        	  line(Black_img,Point(x_coord2,y_coord2 + 10),Point(x_coord2,y_coord2-10), Scalar(0,255,0), 2, 8, 0  );
		  imshow("My Window", Black_img);
		  offset_x = (x_coord2 - x_coord1);
                  offset_y = (y_coord2 - y_coord1);	
 		  count = 0;
		  Rect Rec(x_coord1, y_coord1,offset_x , offset_y);
		  Mat Roi = Black_img(Rec);
		  imwrite("ROI.jpg",Roi);
		  namedWindow("ROI",WINDOW_NORMAL);  
                  imshow("ROI", Roi);
		}	              	
	}
}

void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if  ( event == EVENT_LBUTTONDOWN )
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		Mat image=src.clone();
		Vec3b rgb=image.at<Vec3b>(y,x);
 		B=rgb.val[0];
 		G=rgb.val[1];
 		R=rgb.val[2];
		cout <<"R "<< R <<" G " << G <<" B " << B << endl;
		Mat HSV;
		Mat RGB=image(Rect(x,y,20,20));//capture that pixel in its own ROI
  		cvtColor(RGB, HSV,CV_BGR2HSV);
        	line(image,Point(x+20,y),Point(x-20,y), Scalar(0,255,0), 2, 8, 0  );
        	line(image,Point(x,y+20),Point(x,y-20), Scalar(0,255,0), 2, 8, 0  );
		imshow("My Window", image);
   		Vec3b hsv=HSV.at<Vec3b>(0,0);
    	 	H=hsv.val[0];
    	 	S=hsv.val[1];
    	 	V=hsv.val[2];
		cout <<"H "<< H <<" S " << S <<" V " << V << endl;
		setTrackbarPos(TrackbarName_r, trackbarWindowName, R);
 		setTrackbarPos(TrackbarName_g, trackbarWindowName, G);
		setTrackbarPos(TrackbarName_b, trackbarWindowName, B);

		if(((R >=39) && (R <= 67)) && ((G >= 58) && (G <= 84)) && ((B >= 52) && (B <= 80)))// BLACK
			{
				R_low = 39, R_high = 67, G_low = 58, G_high = 84, B_low = 52, B_high = 80;
				cout <<"BLACK"<<endl;
			}
			else
			{
				cout <<"none"<<endl;
			}
			inRange(src, Scalar(B_low, G_low, R_low), Scalar(B_high, G_high, R_high),mask1); 
                        namedWindow("mask1",WINDOW_NORMAL);
			imshow("mask1",mask1);
     		        Mat1b mask = mask1;
 	
    			//Mat1b kernel = getStructuringElement(MORPH_ELLIPSE, Size(7,7));
    			//morphologyEx(mask, mask, MORPH_OPEN, kernel);

    			vector<vector<Point> > contours;
    			findContours(mask1.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

    			res = src.clone();
			int cont = contours.size();
			cout<<"No of Contours "<<cont <<endl;
    			for(int i=0; i<contours.size(); ++i)
    			{
        			drawContours(res, contours, i, Scalar(0,255,0));
    			}
 			//Mat3b Black_img(src.rows,src.cols,Vec3b(255,255,25));
			src.copyTo(Black_img,mask1);
			namedWindow("Detected",WINDOW_NORMAL);
    			imshow("Detected", Black_img);

			setMouseCallback("Detected", MouseCallBackCropFunc, 0 );
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
	createTrackbars();
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
