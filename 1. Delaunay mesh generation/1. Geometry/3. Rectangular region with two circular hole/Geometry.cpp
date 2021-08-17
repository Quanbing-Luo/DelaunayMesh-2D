#include<algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <set>

#include <numbers>
#include "Geometry.h"

using std::numbers::pi;

void Geometry::create()
{	
	constexpr size_t N1{ 20 };
	for (size_t i = 0; i < N1; i++)
	{	
		static const double xa{ -4.0 }, ya{ -2.0 }, xb{ 4.0 }, yb{ -2.0 };		
		static const double dx{ (xb - xa) / N1 }, dy{ (yb - ya) / N1 };		
		double x{ xa+dx*i };
		double y{ ya+dy*i };
		ps.emplace_back(x, y);
		const size_t sz{ ps.size() };
		es.emplace_back(sz-1, sz, 1);
	}

	constexpr size_t N2{ 10 };
	for (size_t i = 0; i < N2; i++)
	{
		static const double xa{ 4.0 }, ya{ -2.0 }, xb{ 4.0 }, yb{ 2.0 };
		static const double dx{ (xb - xa) / N2 }, dy{ (yb - ya) / N2 };
		double x{ xa + dx * i };
		double y{ ya + dy * i };
		ps.emplace_back(x, y);
		const size_t sz{ ps.size() };
		es.emplace_back(sz - 1, sz, 2);
	}

	constexpr size_t N3{ 20 };
	for (size_t i = 0; i < N3; i++)
	{
		static const double xa{ 4.0 }, ya{ 2.0 }, xb{ -4.0 }, yb{ 2.0 };
		static const double dx{ (xb - xa) / N3 }, dy{ (yb - ya) / N3 };
		double x{ xa + dx * i };
		double y{ ya + dy * i };
		ps.emplace_back(x, y);
		const size_t sz{ ps.size() };
		es.emplace_back(sz - 1, sz, 3);
	}

	constexpr size_t N4{ 10 };
	for (size_t i = 0; i < N4; i++)
	{
		static const double xa{ -4.0 }, ya{ 2.0 }, xb{ -4.0 }, yb{ -2.0 };
		static const double dx{ (xb - xa) / N4 }, dy{ (yb - ya) / N4 };
		double x{ xa + dx * i };
		double y{ ya + dy * i };
		ps.emplace_back(x, y);
		const size_t sz{ ps.size() };
		es.emplace_back(sz - 1, sz, 4);
	}
	
	size_t sz1{ ps.size() };	
	es[sz1 - 1].b = 0;

	constexpr size_t N5{ 50 };
	for (size_t i = 0; i < N5; i++)
	{
		static const double dtheta = 2.0 * pi / N5;		
		double theta{ -(i * dtheta) };
		double x{ -2.0 +std::cos(theta) };
		double y{ std::sin(theta) };
		ps.emplace_back(x, y);

		const size_t sz{ ps.size() };
		es.emplace_back(sz-1, sz, 5);
	}
	size_t sz2{ ps.size() };
	es[sz2-1].b = sz1;
	
	constexpr size_t N6{ 50 };
	for (size_t i = 0; i < N6; i++)
	{
		static const double dtheta = 2.0 * pi / N6;
		double theta{ -(i * dtheta) };
		double x{ 2.0 + std::cos(theta) };
		double y{ std::sin(theta) };
		ps.emplace_back(x, y);

		const size_t sz{ ps.size() };
		es.emplace_back(sz - 1, sz, 5);
	}
	size_t sz3{ ps.size() };
	es[sz3 - 1].b = sz2;

}



// data initialization. 
void Geometry::initialization()
{
	// Points initialization (1)
	for (auto& e : es)
	{
		static size_t i = 0;
		auto& a{ e.a };  auto& b{ e.b };		
		e.l= std::hypot(ps[b].x - ps[a].x, ps[b].y - ps[a].y) ;
		ps[a].aps.push_back(i);
		ps[b].aps.push_back(i);
		i++;
	}

	// Points initialization (2)
	for (auto& p : ps)
	{
		auto& aps{ p.aps };		
		if (p.aps.size() == 2)
		{
			p.r = std::sqrt(std::sqrt(3) / (8 * pi)) *
				std::hypot(es[aps[0]].l, es[aps[1]].l);
		}
	}
}




//Initial mesh output 
void Geometry::output() const
{
	//	const std::string name{ "mesh.txt" };
	const std::string name{ "./Data/Geometry.txt" };

	std::ofstream ost;
	ost.open(name);

	// output Points 
	ost << "Points\n";
	ost << ps.size() << '\n';
	for (auto& p : ps)
	{
		static size_t i = 1;
		ost << std::scientific << i << '\t'
			<< p.x << '\t' << p.y << '\t' << p.r << '\n';
		i++;
	}

	// output Edges 
	ost << "Edges\n";
	ost << es.size() << '\n';
	for (auto& e : es)
	{
		static size_t i = 1;
		ost << std::scientific << i << '\t'
			<< e.a << '\t' << e.b << '\t' << e.id << '\t' << '\n';
		i++;
	}

	ost.close();
}




