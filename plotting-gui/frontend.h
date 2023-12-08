#pragma once
#include <vector>  
#include "backend.h"
                               //FRONT END
//functions
     // rendering functions used in main 
void RenderMainMenu(); // creates the main menu bar with all its components
void RenderBrowser(); // creates navigation tree to navigate all different items (plots graphs csv files, data files etc)
//
// Graphics (graphics are many each is defined as a class. idea is i will have many types of displays to display data including just simple numbers to fancy looking jet engine thrust  like interface)
class LinePlot {  //line plot is a normal plot 
	private:
		//general variables
		const char* Name;
		//event handling variables
		int Item_current_idx = 1;
		//associated DataStreamBacks (vector with pointers to the DatastreamBackObjects)
		std::vector<DataStreamBack*> AssociatedDataStreamBacks; 
		//Data buffer (data that is being displayed on the plot
		double  X_buffer[10000];
		double Y_buffer[10000];
		//rendering 
		void RenderViewToggle(); // renders the toggle to switch between live locked view and free view
		void RenderPlot(double _CurrentTime); //render plot
		
	public:
		//constructer
		LinePlot(const char* _Name,std::vector<DataStreamBack*>);
		//rendering 
		void RenderWindow(double _CurrentTime);
		void Renderinbrowser();
	};
// data stream class 
class DataStreamFront {    //to review : the name here should maybe be deduced from the backend 
private:
	//general variables
	const char* Name;
	DataStreamBack* PDataStreamBack;
	void RenderTable(double _CurrentTime);
public:
	DataStreamFront(const char* _Name, DataStreamBack* _PDataStreamBack);
	void RenderIntoBrowser();
	void RenderWindow(double _CurrentTime);
};

