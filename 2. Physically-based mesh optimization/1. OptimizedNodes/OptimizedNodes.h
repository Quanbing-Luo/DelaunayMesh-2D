#pragma once
#include <vector>
//#include <array>
#include <algorithm>
#include <functional>
#include <utility>
//#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

// Point 
struct Point
{
	Point() = default;

	Point(double xx, double yy, double rr) 
		:x{ xx }, y{ yy }, r{rr} {}

	double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };
	double dx{ 0.0 }, dy{ 0.0 }, dr{ 0.0 };
	bool isatboundary{ false };

	//Neighbouring Points
	std::unordered_set<size_t> aps;

	//Around Points
	std::unordered_set<size_t> aaps;
};
using Points = std::vector<Point>;


//Triangle 
struct Triangle
{
	Triangle() = default;
	//Triangle constructor
	Triangle(size_t aa, size_t bb, size_t cc)
		: a{ aa }, b{ bb }, c{ cc }
	{}

	size_t a{ 0 }, b{ 0 }, c{ 0 };
};
using Triangles = std::vector<Triangle>;


//Edge   
struct Edge
{
	Edge() = default;
	//Edge constructor
	Edge(size_t aa, size_t bb, size_t ID) : a{ aa }, b{ bb }, id{ ID }{}
	size_t a{ 0 }, b{ 0 };
	size_t id{ 0 };	
};
using Edges = std::vector<Edge>;


class OptimizedNodes {
public:

	// mesh data input 
	void input();

	//initialization
	void initialization();

	//optimization
	void optimization();

	//mesh output 
	void output() const;
	

private:

	Points ps;	Edges es;  Triangles ts;   


	//radii calculation
	void radii_calculation();

	//new positions calculation
	void new_positions_calculation();

};

