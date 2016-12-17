
//Gregory Delpe
//Assignment 7: Buffon's Needle

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
#include "Graph.h"
#include "GUI.h"
#include "Window.h"

using namespace Graph_lib;
using namespace std;

//------------------------------------------------------------------------------
struct Buffons_window:Graph_lib::Window{
	Buffons_window(Point xy, int w, int h, const string& title );  //Constructor
	~Buffons_window() {} //Destructor
	vector<Line*> linesCount;
    vector<Line*> linesClear;  //Vector of dropped needles
    vector<Line*> linesCrossed;  //Vector of intersecting needles
    vector<Line*> rotateClear;  //Vector of rotated needles
    vector<Line*> rotateCrossed;  //Vector of intersecting rotated needles
    vector<Line*> rotateCount;  //Vector of intersecting rotated needles
    vector<Line*> overlap;  //Vector of intersecting line segments
    vector<Line*> overlapCount;  //Vector of intersecting line segments
    vector<Text*> centerPoints;  //Vector of line segment midpoints
    vector<Text*> piText;  //Text output of resulting cross count and pi ratio
    vector<double> x_val1;  //X-cord of first point
    vector<double> y_val1;  //Y-cord of first point
    vector<double> x_val2;  //X-cord of second point
    vector<double> y_val2;  //Y-cord of second point
    vector<int> cross_x;  //vector of intersection boundaries
    int input;  //User input indicating number of needles to drop
    double pie;  //pi ratio

private:
    Button drop_button;  //Drop number of needles indicated by user input
    Button quit_button;  //End program
    In_box next_in;  //Accept user input
    Rectangle rect;  //Text background
    Menu motion_menu;  //Primary menu of subordinate actions
    Button menu_button;  //Primary menu button reveals subordinate action buttons

    //Boundary lines:
    Line vertical;
    Line vertical1;
    Line vertical2;
    Line vertical3;
    Line vertical4;
    Line vertical5;

    //Actions invoked by callbacks:
    void hide_menu() { motion_menu.hide(); menu_button.show(); }
    void count_pressed();
    void rotate_pressed();
    void unlist_pressed();
    void menu_pressed() { menu_button.hide(); motion_menu.show(); }
    void lines_clear();
    void lines1_clear();
    void cp_clear();
    void overlap_clear();
    void overlap1_clear();
    void rotate_clear();
    void rotate1_clear();
    void rotate2_clear();
    void text_clear();
    void drop();
    void quit();
    void cord_clear();

    //Callback functions:
    static void cb_count(Address, Address);
    static void cb_rotate(Address, Address);
    static void cb_unlist(Address, Address);
    static void cb_menu(Address, Address);
    static void cb_drop(Address, Address);
    static void cb_quit(Address, Address);
};

//------------------------------------------------------------------------------
//Constructor providing arguments to all sub-objects and attaching them:
Buffons_window::Buffons_window(Point xy, int w, int h, const string& title) :
    Window(xy,w,h,title),
	motion_menu(Point(x_max()-70,30),70,20,Menu::vertical,"Motion"),
	menu_button(Point(x_max()-90,30), 90, 20, "Motion Menu", cb_menu),
    drop_button(Point(x_max()-150,0), 70, 20, "Drop", cb_drop),
    quit_button(Point(x_max()-70,0), 70, 20, "Quit", cb_quit),
    next_in(Point(x_max()-210,0), 50, 20, "Enter drop count"),
	vertical(Point(100,50),Point(100,495)),
	vertical1(Point(200,50),Point(200,495)),
	vertical2(Point(300,50),Point(300,495)),
	vertical3(Point(400,50),Point(400,495)),
	vertical4(Point(500,50),Point(500,495)),
	vertical5(Point(600,50),Point(600,495)),
	rect(Point(150,200),420,20) {

	vertical.set_color(Color::dark_green);
	vertical1.set_color(Color::dark_green);
	vertical2.set_color(Color::dark_green);
	vertical3.set_color(Color::dark_green);
	vertical4.set_color(Color::dark_green);
	vertical5.set_color(Color::dark_green);
	rect.set_fill_color(Color::dark_green);
	rect.set_color(Color::invisible);

    attach(drop_button);
    attach(quit_button);
    attach(next_in);
    attach(vertical);
    attach(vertical1);
    attach(vertical2);
    attach(vertical3);
    attach(vertical4);
    attach(vertical5);

    motion_menu.attach(new Button(Point(0,0),0,0,"Count",cb_count));
    motion_menu.attach(new Button(Point(0,0),0,0,"Rotate",cb_rotate));
    motion_menu.attach(new Button(Point(0,0),0,0,"(Un)list",cb_unlist));
    attach(motion_menu);
    motion_menu.hide();
    attach(menu_button);
}

//------------------------------------------------------------------------------
//Call back functions:
void Buffons_window::cb_quit(Address, Address pw)
{
       reference_to<Buffons_window>(pw).quit();
}

void Buffons_window::quit()
{
    hide();
}

void Buffons_window::cb_drop(Address, Address pw)
{
    reference_to<Buffons_window>(pw).drop();
}

void Buffons_window::cb_count(Address, Address pw)
{
    reference_to<Buffons_window>(pw).count_pressed();
}

void Buffons_window::cb_rotate(Address, Address pw)
{
    reference_to<Buffons_window>(pw).rotate_pressed();
}

void Buffons_window::cb_unlist(Address, Address pw)
{
    reference_to<Buffons_window>(pw).unlist_pressed();
}

void Buffons_window::cb_menu(Address, Address pw)
{
    reference_to<Buffons_window>(pw).menu_pressed();
}

//------------------------------------------------------------------------------
//Function determines line segments that cross boundary:
void Intersect(Line* line, vector<int> cross_x, vector<Line*>& overlap) {
	Point p1 = line->point(0);  //Initialize point variable representation of first point in line segment
	Point p2 = line->point(1);  //Initialize point variable representation of second point in line segment
	Line *i = new Line(p1,p2);  //Create pointer for line segment
	for (int j = 0; j < cross_x.size(); ++j) {
		if ((p1.x <= cross_x[j] && p2.x >= cross_x[j]) || (p1.x >= cross_x[j] && p2.x <= cross_x[j])) {  //Conditions of intersection
			i->set_color(Color::red);  //Set color of crossed lines to red
			overlap.push_back(i);  //Push line segment onto Line vector
		}
	}
}

//Function counts line/boundary intersections:
void IntersectCount(Line* line, vector<Line*>& overlap) {
	Point p1 = line->point(0);  //Initialize point variable representation of first point in line segment
	Point p2 = line->point(1);  //Initialize point variable representation of second point in line segment
	Line *i = new Line(p1,p2);  //Create pointer for line segment
		if ((p1.x <= 100 && p2.x >= 100) || (p1.x >= 100 && p2.x <= 100) ||
			(p1.x <= 200 && p2.x >= 200) || (p1.x >= 200 && p2.x <= 200) ||
			(p1.x <= 300 && p2.x >= 300) || (p1.x >= 300 && p2.x <= 300) ||
			(p1.x <= 400 && p2.x >= 400) || (p1.x >= 400 && p2.x <= 400) ||
			(p1.x <= 500 && p2.x >= 500) || (p1.x >= 500 && p2.x <= 500) ||
			(p1.x <= 600 && p2.x >= 600) || (p1.x >= 600 && p2.x <= 600)) {  //Conditions of intersection
			i->set_color(Color::red);  //Set color of crossed lines to red
			overlap.push_back(i);  //Push line segment onto Line vector
		}
}

//Function rotates line segments:
void Rotate(double x1, double y1, double x2, double y2, vector<Line*>& rotatedLines,vector<Text*>& centerPoints, int i,vector<int> cross_x) {  //Simple_window& win

	double theta = rand() % 360 + 1;  //Random angle
	double center_x = (x2 - x1) / 2 + x1;  //X-cord of line segment midpoint
	double center_y = (y2 - y1) / 2 + y1;  //Y-cord of line segment midpoint

	double x_new1 = center_x + 50 * cos(theta);  //X-cord of first initial point rotated theta degrees
	double y_new1 = center_y + 50 * sin(theta);  //Y-cord of first initial point rotated theta degrees
	double x_new2 = center_x - 50 * cos(theta);  //X-cord of second initial point rotated theta degrees
	double y_new2 = center_y - 50 * sin(theta);  //Y-cord of second initial point rotated theta degrees

	Line *r = new Line(Point(x_new1,y_new1),Point(x_new2,y_new2));  //Create Line pointer of rotated coordinates
	Text *p = new Text(Point(center_x + 10,center_y + 10),to_string(i+1));  //Create Text label indicating line segment sequence
	rotatedLines.push_back(r);  //Push rotated lines onto Line vector
	centerPoints.push_back(p);  //Push text objects onto vector of Text
}

//------------------------------------------------------------------------------
//Detach functions:
void Buffons_window::lines_clear()
{
	for (int i = 0, len = linesClear.size(); i < len; ++i) {
		detach(*linesClear[i]);
		delete linesClear[i];
	}
	linesClear.clear();
}

void Buffons_window::lines1_clear()
{
	for (int i = 0, len = linesCrossed.size(); i < len; ++i){
		detach(*linesCrossed[i]);
		delete linesCrossed[i];
	}
	linesCrossed.clear();
}

void Buffons_window::overlap_clear()
{
	for (int i = 0, len = overlap.size(); i < len; ++i){
		detach(*overlap[i]);
	}
}

void Buffons_window::overlap1_clear()
{
	for (int i = 0, len = overlapCount.size(); i < len; ++i){
		detach(*overlapCount[i]);
		delete overlapCount[i];
	}
	overlapCount.clear();
}

void Buffons_window::rotate_clear()
{
	for (int i = 0, len = rotateClear.size(); i < len; ++i) {
		detach(*rotateClear[i]);
		delete rotateClear[i];
	}
	rotateClear.clear();
}

void Buffons_window::rotate1_clear()
{
	for (int i = 0, len = rotateCrossed.size(); i < len; ++i) {
		detach(*rotateCrossed[i]);
	}
}

void Buffons_window::rotate2_clear()
{
	for (int i = 0, len = rotateCount.size(); i < len; ++i) {
		detach(*rotateCount[i]);
		delete rotateCount[i];
	}
	rotateCount.clear();
}

void Buffons_window::text_clear()
{
	for(int i = 0, len = piText.size(); i < len; ++i) {
		detach(*piText[i]);
		delete piText[i];
	}
	piText.clear();
	detach(rect);
}

void Buffons_window::cord_clear()
{
	x_val1.clear();
	y_val1.clear();
	x_val2.clear();
	y_val2.clear();
}

void Buffons_window::cp_clear()
{
	for (int i = 0, len = centerPoints.size(); i < len; ++i) {
		detach(*centerPoints[i]);
		delete centerPoints[i];
	}
	centerPoints.clear();
}

//------------------------------------------------------------------------------
//Define drop button actions:
void Buffons_window::drop()
{
	//Sanitize dependencies:
	text_clear();
	lines_clear();
	lines1_clear();
	cp_clear();
	rotate_clear();
	rotate1_clear();
	rotate2_clear();
	overlap_clear();
	overlap1_clear();
	cord_clear();
	rotateCrossed.clear();
	overlap.clear();

	//Declare Line variable
	double theta;
	double x1;
	double y1;
	double x2;
	double y2;

	//Push boundaries onto Line vector:
	cross_x.push_back(100);
	cross_x.push_back(200);
	cross_x.push_back(300);
	cross_x.push_back(400);
	cross_x.push_back(500);
	cross_x.push_back(600);
	input = next_in.get_int();  //Assign read in user input to member variable

	for (int i = 0, len = input; i < len; ++i) {
		theta = rand() % 360 + 1;  //Random angle
		x1 = rand() % 650 + 50;  //Initial X-cord of first point
		y1 = rand() % 500 + 1;  //Initial Y-cord of first point
		x2 = x1 + 100 * cos(theta);  //Initial X-cord of second point
	    y2 = y1 + 100 * sin(theta);  //Initial Y-cord of second point
	    x_val1.push_back(x1);  //Push coordinate onto dedicated vector of first point X coordinates
	    y_val1.push_back(y1);  //Push coordinate onto dedicated vector of first point Y coordinates
	    x_val2.push_back(x2);  //Push coordinate onto dedicated vector of second point X coordinates
	    y_val2.push_back(y2);  //Push coordinate onto dedicated vector of second point Y coordinatesTest
	    Line *l = new Line(Point(x1,y1),Point(x2,y2));  //Create Line segment pointer of initial coordinates
	    Line *o = new Line(Point(x1,y1),Point(x2,y2));  //Create Line segment pointer of initial coordinates
	    attach(*l);  //Attach line segment
	    linesClear.push_back(l);  //Push line segment onto Line vector
	    linesCrossed.push_back(o);  //Push line segment onto Line vector
	    Rotate(x1,y1,x2,y2,rotateClear,centerPoints,i,cross_x);  //Rotate line segment
		for (int i = 0, len = linesCrossed.size(); i < len; ++i) {
			Intersect(linesCrossed[i],cross_x,overlap);  //Identify line segment/boundary intersections
		}
	}
	redraw();  //Draw window
}

//------------------------------------------------------------------------------
//Function returns number of intersections:
int crossCount(vector<Line*> overlap,vector<Line*> overlapCount,vector<Line*> rotateCount) {
	if (overlap.size() > 0)  return overlapCount.size();
	if (overlap.size() <= 0) return rotateCount.size();
}

//Define count button functionality:
void Buffons_window::count_pressed()
{
	//Sanitize dependencies:
	overlap_clear();
	overlap1_clear();
	lines_clear();
	text_clear();
	rotate1_clear();
	rotate2_clear();
	cord_clear();

	if (overlap.size() > 0) {
		for (int i = 0, len = linesCrossed.size(); i < len; ++i) {
			attach(*linesCrossed[i]);  //Attach line segments
		}
		for (int i = 0, len = overlap.size(); i < len; ++i) {
			attach(*overlap[i]);  //Attach intersecting segment
		}
	}
	if (overlap.size() <= 0) {
		for (int i = 0, len = rotateClear.size(); i < len; ++i) {
			attach(*rotateClear[i]);  //Attach rotated line segments
		}
		for (int i = 0, len = rotateCrossed.size(); i < len; ++i) {
			attach(*rotateCrossed[i]);  //Attach intersecting rotated line segments
		}
	}

	for (int i = 0, len = linesCrossed.size(); i < len; ++i) {
			IntersectCount(linesCrossed[i],overlapCount);
	}
	for (int i = 0, len = rotateClear.size(); i < len; ++i) {
			IntersectCount(rotateClear[i],rotateCount);
	}

	attach(rect);
	pie = 2 * ((double)input/crossCount(overlap,overlapCount,rotateCount));  //Define pi ratio
	stringstream oss;  //Declare string stream object
	oss << "Found " << crossCount(overlap,overlapCount,rotateCount) << " crossed needles, and estimated pi is " //crossCount(overlap,overlap1)  //String output
			<< pie;
	Text *t = new Text(Point(160,215),oss.str());  //Text pointer
	t->set_font_size(15);  //Text formatting

	t->set_color(Color::white);  //Set text color
	attach(*t);  //Attach Text object
	piText.push_back(t);  //Push text object onto Text vector
	redraw();  //Draw window
}

//------------------------------------------------------------------------------
//Define rotate button actions:
void Buffons_window::rotate_pressed()
{
	//Sanitize dependencies:
	lines1_clear();
	overlap_clear();
	rotate_clear();
	rotate1_clear();
	text_clear();
	cp_clear();
	cord_clear();
	overlap.clear();
	rotateCrossed.clear();

	for (int i = 0, len = input; i < len; ++i) {
		Rotate(x_val1[i],y_val1[i],x_val2[i],y_val2[i],rotateClear,centerPoints,i,cross_x);  //Rotate line segments
	}
	for(int i = 0, len = rotateClear.size(); i < len; ++i) {
		Intersect(rotateClear[i],cross_x,rotateCrossed);  //Identify line/boundary intersections
	}
	for (int j = 0, len = rotateClear.size(); j < len; ++j) {
		attach(*rotateClear[j]); //Attach rotated lines
	}
	redraw();  //Draw window
	lines_clear();  //Clear initial line vector
}

//------------------------------------------------------------------------------
//Define unlist button actions:
void Buffons_window::unlist_pressed()
{
	//cp_clear();  //Sanitize dependencies
	for (int i = 0, len = centerPoints.size(); i < len; ++i) {
		attach(*centerPoints[i]);  //Attach line segment sequence labels
	}
	redraw();  //Draw window
}

//------------------------------------------------------------------------------
int main()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();  //Seed for random number generator
	srand(seed);  //Random number generator

	Buffons_window win(Point(100,100),700,500,"Gregory Delpe: Programing Assignment #7");  //Declare Buffons_window object 700,400
	return gui_main();  //Execute program
}

//------------------------------------------------------------------------------
