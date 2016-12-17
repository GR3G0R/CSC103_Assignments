
//Gregory Delpe
//Programming Assignment #6 - Circle Art

#include <cstdlib>
#include <chrono>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include "std_lib_facilities.h"
#include "Simple_window.h"  // get access to our window library
#include "Graph.h"  // get access to our graphics library facilities


//------------------------------------------------------------------------------
using namespace Graph_lib;  //Graphics facilities are in Graph_lib

#define PI 3.14159265  //Preprocessor directive replaces any occurrence of PI identifier

bool Inscribe(double& radius, int& gen, vector<Circle*>& circles, double& theta1, Simple_window& win) {  //Generate interior circles
	for (int k = 0; k < gen; ++k) {  //Primary loop regulates number of generations

		int innerCircles = rand() % 45;  //Variable generates 0 - 45 random circles

		for (int i = 0; i < innerCircles; ++i) {  //Interior circle generating loop
			double param = (PI/innerCircles);
			radius = (230 * sin(param)) / (1 + sin(param));  //Set radius of interior circles
			double theta = (360/(double)innerCircles);  //Scale point of reference for interior circles by degrees of separation
			double x = 250 + (230-radius)*cos(theta1*PI/180);  //Set x coordinates for interior generated circle
			double y = 250 + (230-radius)*sin(theta1*PI/180);  //Set y coordinates for interior generated circle

			Circle *r = new Circle(Point(x,y),radius);  //Dynamic allocation of heap memory for interior generated circles

			r->set_color(Color(rand()%256));  //Apply random color to interior generated
			win.attach(*r);  //Relate interior generated circles to window
			circles.push_back(r);  //Push interior generated circles onto vector or circles
			theta1 += theta;  //Re-calibrate point of reference
		}
	}
}

void DisplayWindow(Simple_window& win, vector<Circle*>& circles, int& gen) {  //Display window
	ostringstream oss;  //Create output stream object
	oss << "After " << gen << " ring generations " << circles.size() << " circles were generated";  //Print number of generations
	Text generation (Point(100,495),oss.str());  //Create Text object containing label
	win.attach(generation);  //Relate label to window

	for (int j = 0; j < circles.size(); ++j) {  //Relate circles contained in vector of circles to simple window
		win.attach(*circles[j]);
		break;
	}
	win.wait_for_button();  //Display window and content

	for (int j = 0; j < circles.size(); ++j) {
		win.detach(*circles[j]);  //Dissociate the thread represented by circles from simple window
		delete circles[j];  //Deallocate heap memory
	}
}

int main() {
	int gen;

	double radius, theta1 = 0;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();  //Seed for random number generator
	srand(seed);  //Random number generator

	while(true) {
		vector<Circle*> circles;  //Vector of circles

		cout << "Enter the round of inner circle generations: ";  //Prompt user for number of generations
		cin >> gen;  //Read user input

		if (gen < 0) return 0;  //Terminate program is user input is less than 0

		cout << endl; //Newline

		Simple_window win(Point(100,100),500,500,"Gregory Delpe: Programming Assignment #6");  //Create simple window

		Circle c(Point(250,250),230);  //Create circle with origin at the center of simple window
		c.set_color(Color(rand()%256));  //Apply random color to perimeter circle
		win.attach(c);  //Relate circle to window

		Inscribe(radius, gen, circles, theta1, win);  //Inscribe primary circle

		DisplayWindow(win,circles, gen);  //Display content
	}
}

//------------------------------------------------------------------------------
