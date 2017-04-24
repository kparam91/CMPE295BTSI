#include<iostream>
#include<stdio.h>
#include<string>
#include <vector>
#include<stdint.h>
#include<stdlib.h>
#include "signDefinition.h"

using namespace std;





int main(){
	string name,color, shape, location;
	vector <sign *> signList;
	vector <sign> filteredList;
	
	sign stop("STOP",RED_WHITE, HEXAGON, two_3);	
	signList.push_back(&stop);
	
	sign disabled("DISABLED_PARKING",BLUE_WHITE, SQUARE,two_2);
	signList.push_back(&disabled);
	
	sign railCrossing("RAIL_CROSSING",YELLOW_BLACK, CIRCLE, two_3);
	signList.push_back(&railCrossing);
	
	sign bikeLane("BIKE_LANE",WHITE_BLACK, RECTANGLE_W, two_3);
	signList.push_back(&bikeLane);
	
	sign oneWay("ONE_WAY", BLACK_WHITE, RECTANGLE_W, two_3);
	signList.push_back(&oneWay);
	
	sign leftUTurn("LEFT_U_TURN",WHITE_BLACK, SQUARE, two_1);
	signList.push_back(&leftUTurn);
	
	sign doNotEnter("DO_NOT_ENTER",RED_WHITE, SQUARE, two_3);
	signList.push_back(&doNotEnter);
	
	sign pedestrian("PEDESTRIAN",YELLOW_BLACK,DIAMOND, two_3);
	signList.push_back(&pedestrian);
	
	sign noLeftTurn("NO_LEFT_TURN",WHITE_RED_BLACK, SQUARE, two_1);
	signList.push_back(&noLeftTurn);
	
	sign speedLimit("SPEED_LIMIT",WHITE_BLACK, RECTANGLE_L, two_3);
	signList.push_back(&speedLimit);
	while(1)
	{
	
	    cout<<"Enter the shape of the sign OR enter q to exit"<<endl;
	    cout<< "Possible values:SQUARE CIRCLE RECTANGLE_W RECTANGLE_L HEXAGON DIAMOND"<<endl;
	    cin>>shape;
	    if(shape=="q")
	    {
	        break;
	    }
	    cout<<"Enter the color of the sign as Background_foreground "<<endl;
	    cout<<"Possible values for color"<<endl;
	    for(vector<sign *>::iterator i= signList.begin(); i!= signList.end(); i++ )
	    {
		    sign t;
		    t=**i;
		    if(shape.compare(signShape[t.sh])==0)
		    {
		        
		       filteredList.push_back(t);
		       cout<<colorNames[t.col]<<endl;
		      // cout<<"PUSH BACK"<<filteredList.back()<<endl;
			
		    }
	    }
	    
	    cin>>color;
	    cout<<"Enter the location of the sign "<<endl;
	    cout<<"Possible values:"<<endl;
	    for(vector<sign >::iterator j= filteredList.begin(); j!= filteredList.end(); j++ )
	    {
	    
		    sign q;
		    q=*j;

		    if(!color.compare(colorNames[q.col])==0)
		    {	 
		       filteredList.erase(j);		       
		       j--;			      	
		    }
		    else{
		         cout<<signposition[q.location]<<endl;	
		    }
	    }
	 
	    bool flag=false;
	    cin>>location;
	    for(vector<sign >::iterator k= filteredList.begin(); k!= filteredList.end(); k++ )
	    {	        
	        sign q;
		    q=*k;
            if(location.compare(signposition[q.location])==0)
            {            
                flag=true;
                cout<<q<<endl;
                break;
            }
        }
	    
	    if(!flag)
	    {
	        cout<<"Sign not found"<<endl;
	    }
	    
    }
	return 0;
}

