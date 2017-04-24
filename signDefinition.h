#include<iostream>
#include<stdio.h>
#include<string>
#include <vector>
#include<stdint.h>
#include<stdlib.h>

using namespace std;
 enum color{
	BLUE_WHITE,//0
	YELLOW_BLACK,//1
	WHITE_BLACK,//2
	BLACK_WHITE,//3
	RED_WHITE,//4
	WHITE_RED_BLACK,//4
	GREEN_WHITE//5
};
 enum shape{
	SQUARE,
	CIRCLE,
	RECTANGLE_W,
	RECTANGLE_L,
	HEXAGON,
	DIAMOND
};

 enum position{
    one_1,
    one_2,
    one_3,
    two_1,
    two_2,
    two_3, 
    three_1,
    three_2,
    three_3
};

 string colorNames[]={"BLUE_WHITE",//0
						"YELLOW_BLACK",//1
						"WHITE_BLACK",//2
						"BLACK_WHITE",//3
						"RED_WHITE",//4
						"WHITE_RED_BLACK",
						"GREEN_WHITE"//5
						};
						
 string signShape[] ={"SQUARE",
					"CIRCLE",
					"RECTANGLE_W",
					"RECTANGLE_L",
					"HEXAGON",
					"DIAMOND"};
					
					
 string signposition[]={
    "one_1",
    "one_2",
    "one_3",
    "two_1",
    "two_2",
    "two_3", 
    "three_1",
    "three_2",
    "three_3"
};
		
class sign
{
	public:
	
		string name;
		color col;
		shape sh;		
		position location; 
		sign(string n, color c, shape s, position l);
		sign();                                        // constructor
		
	friend ostream & operator << (ostream &out, sign &s);
};

sign::sign(string n, color c, shape s, position l)
{
			this->name= n;
			this->col=c;
			this->sh = s;
			this->location=l;
		}
		
sign::sign()
{
	//empty constructor
}

ostream & operator << (ostream &out, sign &s)
{
	
	out<<"NAME: "<<s.name<<" COLOR: "<<colorNames[s.col]<<" SHAPE: "<<signShape[s.sh];
	out<<" LOCATION: "<<signposition[s.location]<<endl;
	return out;
}

sign stop("STOP",RED_WHITE, HEXAGON, two_3);		
sign disabled("DISABLED_PARKING",BLUE_WHITE, SQUARE,two_2);	
sign railCrossing("RAIL_CROSSING",YELLOW_BLACK, CIRCLE, two_3);
sign bikeLane("BIKE_LANE",WHITE_BLACK, RECTANGLE_W, two_3);	
sign oneWay("ONE_WAY", BLACK_WHITE, RECTANGLE_W, two_3);	
sign leftUTurn("LEFT_U_TURN",WHITE_BLACK, SQUARE, two_1);	
sign doNotEnter("DO_NOT_ENTER",RED_WHITE, SQUARE, two_3);	
sign pedestrian("PEDESTRIAN",YELLOW_BLACK,DIAMOND, two_3);	
sign noLeftTurn("NO_LEFT_TURN",WHITE_RED_BLACK, SQUARE, two_1);	
sign speedLimit("SPEED_LIMIT",WHITE_BLACK, RECTANGLE_L, two_3);

void initSigns(vector <sign *> &signList)
{
signList.push_back(&speedLimit);
signList.push_back(&stop);
signList.push_back(&noLeftTurn);
signList.push_back(&pedestrian);
signList.push_back(&doNotEnter);
signList.push_back(&leftUTurn);
signList.push_back(&oneWay);
signList.push_back(&bikeLane);
signList.push_back(&railCrossing);
signList.push_back(&disabled);
	
}

