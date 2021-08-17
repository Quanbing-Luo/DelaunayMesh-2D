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
	constexpr size_t N{ 40 };
	constexpr double dtheta = 2.0 * pi / N;

	double theta{ 0.0 }, x{ 0.0 }, y {0.0};
	for (size_t i = 0; i < N; i++)
	{
		double theta{ i * dtheta };
		double x{ std::cos(theta) };
		double y{ std::sin(theta) };
		ps.emplace_back(x, y);
		es.emplace_back(i, i + 1, 0);
	}

	es[N - 1].b = 0;
}


// data initialization. 
void Geometry::initialization()
{
	// Points initialization (1)
	for (auto& e : es)
	{
		static size_t i = 0;
		auto& a{ e.a };  auto& b{ e.b };
		e.l = std::hypot(ps[b].x - ps[a].x, ps[b].y - ps[a].y);
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




