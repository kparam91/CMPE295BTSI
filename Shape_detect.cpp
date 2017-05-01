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
#include <algorithm>
using namespace cv;
using namespace std;
Mat frame;
int flag = 0;
int H, S, V, R, G, B;
int R_MIN = 0;
int R_MAX = 255;
int G_MIN = 0;
int G_MAX = 255;
int B_MIN = 0;
int B_MAX = 255;
Mat roi_img;
Mat imggray;
Mat canny_output;
int pos;
Mat src;
Mat1b mask1;
Mat3b res;
RNG rng(12345);
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
void MouseCallBackCropFunc(int event, int x, int y, int flags, void* userdata)// Manual click of two points xmin, xmax, ymin, ymax
{
	static int count = 0;
	static int x_coord1, x_coord2, y_coord1, y_coord2, offset_x,offset_y;
	if  ( event == EVENT_LBUTTONDOWN )
	{
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		if(count == 0)
		{
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

void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)// manual rgb color selection
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
			res = src.clone();
			src.copyTo(Black_img,mask1);
			namedWindow("Detected",WINDOW_NORMAL);
    			imshow("Detected", Black_img);
			setMouseCallback("Detected", MouseCallBackCropFunc, 0 );
	}
}
static void onMouse(int event, int x, int y, int, void* ){ // mouse click to pause the video

if( event == EVENT_LBUTTONUP ){
		waitKey(0);
		imshow("Video", frame);
		pos =getTrackbarPos("seek", "Video");
		source.set(CAP_PROP_POS_FRAMES, pos);		
		return;
	}
	else if(event == EVENT_RBUTTONDOWN){ // right click to save the frame
		
		time_t now = time(0);
		string timeStamp=ctime(&now);
		string name = "Capture"+ timeStamp+".jpg";
		imwrite(name.c_str(),frame);
 		src = imread(name); 
		namedWindow("My Window",WINDOW_NORMAL); 
  		imshow("My Window", src);
                cout<<"Captured"<<endl;
		cvtColor(src, imggray,CV_BGR2GRAY);
		blur(imggray, canny_output, Size(3,3));

		vector<Vec3f> circles; //Circles
		Mat image_shape = src.clone();
		HoughCircles(imggray, circles, HOUGH_GRADIENT, 1, 200, 100, 30, 1, 30 );
		cout <<"no of circles "<< circles.size()<<endl;
		for( size_t i = 0; i < circles.size(); i++ )
		{
  			 Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
   			 int radius = cvRound(circles[i][2]);
   			// circle center
  			 circle( image_shape, center, 3, Scalar(0,255,0), -1, 8, 0 );
  			 // circle outline
   			circle( image_shape, center, radius, Scalar(0,0,255), 3, 8, 0 );
			
 		}
		imshow("My Window", image_shape);

		Canny(imggray,canny_output,80,240,3);
		namedWindow("Canny",WINDOW_NORMAL);
		imshow("Canny",canny_output);
		vector<vector<Point> >contours;	//Detecting rectangle
    		findContours(canny_output.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0,0));
		vector<vector<Point> >result(contours.size());
		int rectcount = 0, hexcount = 0, fourpointcontour = 0;
    		for(int i=0; i<contours.size(); ++i)
    		{
		    approxPolyDP(contours[i], result[i], arcLength(contours[i],true) * 0.02  , true);   	    
    		}		
		for(int i=0; i<result.size(); ++i)
    		{
			 if(result[i].size() == 4)
		    	 {
				fourpointcontour++;
				if((((abs(result[i][0].x -result[i][1].x) >=0) 
					&& (abs(result[i][0].x -result[i][1].x) <=25))
					&& ((abs(result[i][1].x -result[i][2].x) >=0) 
					&& (abs(result[i][1].x -result[i][2].x) <=25))
					&& ((abs(result[i][2].x -result[i][3].x) >=0) 
					&& (abs(result[i][2].x -result[i][3].x) <=25))) 
					|| (((abs(result[i][0].y -result[i][1].y) >=0) 
					&& (abs(result[i][0].y -result[i][1].y) <=25)) 
					&& ((abs(result[i][1].y -result[i][2].y) >=0) 
					&& (abs(result[i][1].y -result[i][2].y) <=25))
					&& ((abs(result[i][2].y -result[i][3].y) >=0)
					&& (abs(result[i][2].y -result[i][3].y) <=25)))) 
				{
					cout <<"improper  4 points "<<" ";
					for(int j=0; j<4; ++j)
    					{
						cout << result[i][j]<<" ";
					}
					cout <<endl;
				}
				else if(((((abs(result[i][0].x -result[i][1].x) >=0) 
					&& (abs(result[i][0].x -result[i][1].x) <=25)) 
					&& ((abs(result[i][1].x -result[i][2].x) >=0) 
					&& (abs(result[i][1].x -result[i][2].x) <=25))) 
					|| (((abs(result[i][1].x -result[i][2].x) >=0) 
					&& (abs(result[i][1].x -result[i][2].x) <=25)) 
					&& ((abs(result[i][2].x -result[i][3].x) >=0) 
					&& (abs(result[i][2].x -result[i][3].x) <=25))) 
					|| (((abs(result[i][0].x -result[i][2].x) >=0) 
					&& (abs(result[i][0].x -result[i][2].x) <=25)) 
					&& ((abs(result[i][2].x -result[i][3].x) >=0) 
					&& (abs(result[i][2].x -result[i][3].x) <=25))) 
					||(((abs(result[i][0].x -result[i][1].x) >=0) 
					&& (abs(result[i][0].x -result[i][1].x) <=25)) 
					&& ((abs(result[i][1].x -result[i][3].x) >=0) 
					&& (abs(result[i][1].x -result[i][3].x) <=25)))) 
					|| ((((abs(result[i][0].y -result[i][1].y) >=0) 
					&& (abs(result[i][0].y -result[i][1].y) <=25)) 
					&& ((abs(result[i][1].y -result[i][2].y) >=0) 
					&& (abs(result[i][1].y -result[i][2].y) <=25))) 
					|| (((abs(result[i][1].y -result[i][2].y) >=0) 
					&& (abs(result[i][1].y -result[i][2].y) <=25)) 
					&& ((abs(result[i][2].y -result[i][3].y) >=0)
					&& (abs(result[i][2].y -result[i][3].y) <=25)))
					|| (((abs(result[i][0].y -result[i][2].y) >=0) 
					&& (abs(result[i][0].y -result[i][2].y) <=25)) 
					&& ((abs(result[i][2].y -result[i][3].y) >=0) 
					&& (abs(result[i][2].y -result[i][3].y) <=25))) 
					||(((abs(result[i][0].y -result[i][1].y) >=0) 
					&& (abs(result[i][0].y -result[i][1].y) <=25))
					&& ((abs(result[i][1].y -result[i][3].y) >=0) 
					&& (abs(result[i][1].y -result[i][3].y) <=25)))))
				{
					cout <<"improper  3 points "<<" ";
					for(int j=0; j<4; ++j)
    					{
						cout << result[i][j]<<" ";
					}
					cout <<endl;
				}
				else if(((abs(result[i][0].x -result[i][1].x) >=0) 
					 && (abs(result[i][0].x -result[i][1].x) <=25)) 
					 && ((abs(result[i][0].y -result[i][1].y) >=0)  
					 && (abs(result[i][0].y -result[i][1].y) <=25)) 
					 || ((abs(result[i][1].x -result[i][2].x) >=0) 
					 && (abs(result[i][1].x -result[i][2].x) <=25)) 
					 && ((abs(result[i][1].y -result[i][2].y) >=0)  
					 && (abs(result[i][1].y -result[i][2].y) <=25)) 
					 || ((abs(result[i][2].x -result[i][3].x) >=0)  
					 && (abs(result[i][2].x -result[i][3].x) <=25)) 
					 && ((abs(result[i][2].y -result[i][3].y) >=0) 
					 && (abs(result[i][2].y -result[i][3].y) <=25))
					 || ((abs(result[i][3].x -result[i][0].x) >=0)  
					 && (abs(result[i][3].x -result[i][0].x) <=25)) 
					 && ((abs(result[i][3].y -result[i][0].y) >=0)  
					 && (abs(result[i][3].y -result[i][0].y) <=25)) 
					 || ((abs(result[i][0].x -result[i][2].x) >=0)  
					 && (abs(result[i][0].x -result[i][2].x) <=25)) 
					 && ((abs(result[i][0].y -result[i][2].y) >=0)  
					 && (abs(result[i][0].y -result[i][2].y) <=25)) 
					 || ((abs(result[i][1].x -result[i][3].x) >=0)  
					 && (abs(result[i][1].x -result[i][3].x) <=25)) 
					 && ((abs(result[i][1].y -result[i][3].y) >=0)  
					 && (abs(result[i][1].y -result[i][3].y) <=25)))
				{
					cout <<"improper 2 points "<<" ";
					for(int j=0; j<4; ++j)
    					{
						cout << result[i][j]<<" ";
					}
					cout <<endl;
				}
				else
				{
					cout <<"Rectangle "<<" ";
					cout <<"contour point "<<" ";
					for(int j=0; j<4; ++j)
    					{
						cout << result[i][j]<<" ";
					}
					cout <<endl;
					line(image_shape,result[i][0],result[i][1], Scalar(0,255,0), 1, 8, 0  );
					line(image_shape,result[i][1],result[i][2], Scalar(0,255,0), 1, 8, 0  );
					line(image_shape,result[i][2],result[i][3], Scalar(0,255,0), 1, 8, 0  );
					line(image_shape,result[i][3],result[i][0], Scalar(0,255,0), 1, 8, 0  );
					int x_coord1, y_coord1;	
					/// Get the moments
  					Moments mu; 
					mu = moments( result[i], false );	
					x_coord1 = mu.m10/mu.m00;
					x_coord1 = x_coord1 + 13;
					y_coord1 = mu.m01/mu.m00;
					y_coord1 = y_coord1 + 3;
					cout << "x coord " <<x_coord1 <<" ";
					cout << "y coord " <<y_coord1 <<endl;
				line(image_shape,Point(x_coord1 + 5,y_coord1),Point(x_coord1-5,y_coord1), Scalar(0,255,0), 1, 8, 0  );
        	  		line(image_shape,Point(x_coord1,y_coord1 + 5),Point(x_coord1,y_coord1-5), Scalar(0,255,0), 1, 8, 0  );
					int R1= 0, B1= 0, G1 =0;
					Mat image_shape1 = src.clone();
					Vec3b rgb1 = image_shape1.at<Vec3b>(y_coord1,x_coord1);
 					B1=rgb1.val[0];
 					G1=rgb1.val[1];
 					R1=rgb1.val[2];
					cout <<"R1 "<< R1 <<" G1 " << G1 <<" B1 " << B1 << endl;
					int R_low1 =0 , R_high1 =0, G_low1 =0, G_high1 =0, B_low1 =0, B_high1 =0;
					cout <<endl;
					rectcount++;
					imshow("My Window", image_shape);
					Mat image_shape2 = src.clone();
					if(((R1 >=39) && (R1 <= 84)) && ((G1 >= 58) && (G1 <= 84)) && ((B1 >= 52) && (B1 <= 84)))// BLACK
					{
						R_low1 = 39, R_high1 = 84, G_low1 = 58, G_high1 = 84, B_low1 = 52, B_high1 = 84;
						cout <<"BLACK"<<endl;
						flag = 1;
					}
				else if(((R1 >=181) && (R1 <= 201)) && ((G1 >= 63) && (G1 <= 79)) && ((B1 >= 76) && (B1 <= 103)))//RED
					{
						R_low1 = 181, R_high1 = 201, G_low1 = 63, G_high1 = 79, B_low1 = 76, B_high1 = 103;
						cout <<"RED"<<endl;
						flag = 1;
					}
				else if(((R1 >=180) && (R1 <= 255)) && ((G1 >= 130) && (G1 <= 255)) && ((B1 >= 130) && (B1 <= 255)))
					{
						R_low1 = 180, R_high1 = 255, G_low1 = 130, G_high1 = 255, B_low1 = 130, B_high1 = 255;
						cout <<"WHITE"<<endl;
						flag = 1;
					}
					else if(((R1 >=44) && (R1 <= 86)) && ((G1 >= 48) && (G1 <= 78)) && ((B1 >= 108) && (B1 <= 145)))
					{
						R_low1 = 44, R_high1 = 86, G_low1 = 48, G_high1 = 78, B_low1 = 108, B_high1 = 145;
						cout <<"BLUE"<<endl;
						flag = 1;
					}
					else
					{
						flag = 0;
						cout <<"none"<<endl;
					}
					if(flag)
					{
						flag = 0;
						int yval_count =0;
						int y_array[2];
						int offset_x =0, offset_y =0;	
						int minx_1 = std::min(result[i][0].x,result[i][1].x);
						int minx_2 = std::min(result[i][2].x,result[i][3].x);
						int minx = std::min(minx_1,minx_2);
						//cout << "min x:" << minx<<endl;

						int max_1 = std::max(result[i][0].x,result[i][1].x);
						int max_2 = std::max(result[i][2].x,result[i][3].x);
						int max_x = std::max(max_1,max_2);

						//cout << "max x:" << max_x<<endl;

						int maxy_1 = std::max(result[i][0].y,result[i][1].y);
						int maxy_2 = std::max(result[i][2].y,result[i][3].y);
						int max_y = std::max(maxy_1,maxy_2);

						//cout << "max y:" << max_y<<endl;	
						int y1 =0, y2 =0, yflag = 0;
						for(int j=0; j<4; ++j)
    						{
							if((abs(result[i][j].x - minx) >= 0) && (abs(result[i][j].x - minx) <= 10)){
								y_array[yval_count] = result[i][j].y;
								yval_count++;
								
							}
						}
						int miny = std::min(y_array[0],y_array[1]);
						//cout<< "min y :"<<miny<<endl;
						offset_x =  max_x - minx;
						offset_y = max_y - miny;
						//cout <<"offset_x :" <<offset_x<<" ";
						//cout <<"offset_y :" <<offset_y<<" ";
						//Rect Rec(result[i][3].x, result[i][3].y,offset_x , offset_y);
						Rect Rec(minx, miny,offset_x , offset_y);
		  				Mat Roi = src(Rec);
		  				imwrite("ROI.jpg",Roi);
		  				namedWindow("ROI",WINDOW_NORMAL);  
                  				imshow("ROI", Roi);		
						line(image_shape2,result[i][0],result[i][1], Scalar(0,255,0), 2, 8, 0  );
						line(image_shape2,result[i][1],result[i][2], Scalar(0,255,0), 2, 8, 0  );
						line(image_shape2,result[i][2],result[i][3], Scalar(0,255,0), 2, 8, 0  );
						line(image_shape2,result[i][3],result[i][0], Scalar(0,255,0), 2, 8, 0  ); 							imshow("My Window", image_shape2);
					}
				}
		    	}
			else if(result[i].size() == 6)
			{
				/*cout <<"hexagon"<<endl;
				cout <<"contour point "<<" ";
				for(int j=0; j<6; ++j)
    				{
					cout << result[i][j]<<" ";
				}
				line(image_shape,result[i][0],result[i][1], Scalar(0,255,0), 2, 8, 0  );
				line(image_shape,result[i][1],result[i][2], Scalar(0,255,0), 2, 8, 0  );
				line(image_shape,result[i][2],result[i][3], Scalar(0,255,0), 2, 8, 0  );
				line(image_shape,result[i][3],result[i][4], Scalar(0,255,0), 2, 8, 0  );
				line(image_shape,result[i][4],result[i][5], Scalar(0,255,0), 2, 8, 0  );
				line(image_shape,result[i][5],result[i][0], Scalar(0,255,0), 2, 8, 0  );	
				cout <<endl;
				hexcount++;
				imshow("My Window", image_shape);*/
			}
		}
		cout <<"total no of rect "<< rectcount<<endl;
		cout <<"total no of 4 point contour"<< fourpointcontour<<endl;
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
