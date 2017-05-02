#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include <vector>
#include<stdint.h>
#include<stdlib.h>
#include "signDefinition.h"
#include <ctype.h>
using namespace std;

	
int main(){
	string name,color, shape, location;	
	vector <sign *> signList;
	vector <sign> filteredList;	
	initSigns(signList);

	while(1)
	{
	
	    cout<<"Enter the shape of the sign OR enter q to exit"<<endl;
	    cout<< "Possible values:SQUARE CIRCLE RECTANGLE_W RECTANGLE_L HEXAGON DIAMOND"<<endl;
	    cin>>shape;
	     string s;
	    int l=0;
	    while (shape[l])
            {
                s+=toupper(shape[l]);                
                l++;
            }
            
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
		    if(s.compare(signShape[t.sh])==0)
		    {		        
		       filteredList.push_back(t);
		       cout<<colorNames[t.col]<<endl;     
			
		    }
	    }
	    
	    cin>>color;
	    string c;
	     l=0;
	    while (color[l])
            {
                c+=toupper(color[l]);                
                l++;
            }
            
	   // color=toupper(color.c_str());
	    cout<<"Enter the location of the sign "<<endl;
	    cout<<"Possible values:"<<endl;
	    for(vector<sign >::iterator j= filteredList.begin(); j!= filteredList.end(); j++ )
	    {
	    
		    sign q;
		    q=*j;

		    if(!c.compare(colorNames[q.col])==0)
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
	    string lo;
	     l=0;
	    while (location[l])
            {
                lo+=tolower(location[l]);                
                l++;
            }
	    for(vector<sign >::iterator k= filteredList.begin(); k!= filteredList.end(); k++ )
	    {	        
	        sign q;
		    q=*k;
            if(lo.compare(signposition[q.location])==0)
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

