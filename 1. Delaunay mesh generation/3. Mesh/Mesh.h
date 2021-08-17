#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <cmath>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <numbers>
using std::numbers::pi;

// Point and Points
struct Point;
using Points = std::vector<Point>;

//Triangle and Triangles 
struct Triangle;
using Triangles = std::vector<Triangle>;

//Edge and Edges  
struct Edge;
using Edges = std::vector<Edge>;

class Mesh;

//Line 
struct Line
{
	Line() = default;
	//Line constructor
	Line(size_t aa, size_t bb)
	{
		if (aa < bb) { a = aa; b = bb; }
		else { a = bb; b = aa; }
	}
	size_t a{ 0 }, b{ 0 };
};

namespace std
{
	template<>
	struct hash<Line>
	{
		size_t operator()(const Line& l) const
		{
			return hash<size_t>{}(l.a) ^ hash<size_t>{}(l.b);
		}
	};

	template<>
	struct equal_to<Line> {
		bool operator()(const Line& l1, const Line& l2) const
		{
			return (l1.a == l2.a) && (l1.b == l2.b);
		}
	};
}
using Lines = std::unordered_multimap<Line, size_t>;


// Point 
struct Point
{
	//Point() = default;
	Point(double xx, double yy) :x{ xx }, y{ yy } {};
	Point(double xx, double yy, double rr) 
		:x{ xx }, y{ yy }, r{ rr } {};
	double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };
};


//Triangle 
struct Triangle
{
	Triangle() = default;

	//Triangle constructor
	Triangle(size_t aa, size_t bb, size_t cc) 
		: a{ aa }, b{ bb }, c{ cc }, 
		lts{ Line{aa, bb}, Line{bb, cc}, Line{cc, aa} }  {}

	//setTriangle
	void setTriangle(const Points& ps);

	size_t a{ 0 }, b{ 0 }, c{ 0 };

	//lines of triangles
	std::array<Line, 3> lts;

	// the center of gravity 
	double x{ 0.0 }, y{ 0.0 }, r{0.0};

	// circumcenter and radius of Circumcircle
	double xcc{ 0.0 }, ycc{ 0.0 }, rcc{ 0.0 };

	// area and area_bubble
	double area{ 0.0 }, area_bubble{ 0.0 };

	//mesh density
	double d{ 0.0 };
};


//Edge   
struct Edge
{
	Edge() = default;
	//Edge constructor
	Edge(size_t aa, size_t bb, size_t ID)
		: a{ aa }, b{ bb }, id{ ID } 	{ 	}
	size_t a{ 0 }, b{ 0 }, id{ 0 };
};



class Mesh {
public:
	
	// Initial_Mesh data input
	void input();	
	
	// mesh data initialization. 
	void initialization();

	// delaunay triangulation. 
	void delaunay_triangulation();

	//mesh output 
	void output() const;
	

private:	
	
	Points ps;	Edges es;  Triangles ts; Lines ls;

	double area { 0.0 };
	double area_bubble{ 0.0 };

	std::unordered_set<size_t> ns_cavity;
	std::unordered_set<Line> lbs_cavity;

	//set ns_cavity
	void set_ns_cavity(size_t n);

	//set lbs_cavity
	void set_lbs_cavity();

	//delete old cavity
	void delete_old_cavity();

	//add new cavity
	void add_new_cavity();
};

