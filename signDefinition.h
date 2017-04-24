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

