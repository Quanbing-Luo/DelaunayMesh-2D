#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include "OptimizedNodes.h"
//#include <numbers>
//using std::numbers::pi;

// mesh data input 
void OptimizedNodes::input()
{
	std::ifstream ist;
	ist.open("Mesh.txt");
	std::string ss;	

	// input Points
	std::getline(ist, ss);
	size_t np{ 0 }; ist >> np;
	for (size_t i = 0; i < np; i++)
	{
		static size_t n{ 0 }; 	 
		static double x{ 0.0 }, y{ 0.0 }, r{0.0};
		ist >> n >> x >> y >> r;
		ps.emplace_back(x, y, r);
	}
	ist >> std::ws;


	// input Triangles 
	std::getline(ist, ss);
	size_t nt{ 0 }; ist >> nt;	
	for (size_t i = 0; i < nt; i++)
	{
		static size_t n{ 0 };
		static size_t a{ 0 }, b{ 0 }, c{ 0 };
		ist >> n >> a >> b >> c;
		ts.emplace_back(a, b, c);
	}
	ist >> std::ws;

	// input Edges
	std::getline(ist, ss);
	size_t ne{ 0 }; ist >> ne;	
	for (size_t i = 0; i < ne; i++)
	{
		static size_t n{ 0 };
		static size_t aa{ 0 }, bb{ 0 }, id{ 0 };		
		ist >> n >> aa >> bb >> id;
		es.emplace_back(aa, bb, id);
	}
	ist >> std::ws;
	ist.close();
}


//data_initialization
void OptimizedNodes::initialization()
{	
	//Points initialization (set isatboundary) 
	for (const auto& e : es)
	{
		ps[e.a].isatboundary = true;
		ps[e.b].isatboundary = true;
	}

	//Points initialization (set radii) 
	for (auto& p : ps)	
		p.r *= 1.7;	

		
	//Points initialization (set aps)
	for (const auto& [a,b,c] : ts)
	{
		auto& pa{ ps[a] }; auto& pb{ ps[b] }; auto& pc{ ps[c] };
		
		pa.aps.insert(b); pb.aps.insert(a);
		pa.aps.insert(c); pc.aps.insert(a);
		pb.aps.insert(c); pc.aps.insert(b);
	}


	//Points initialization (set aaps) 
	for (auto& p:ps)	
		p.aaps = p.aps;	

	size_t LEVEL{ 3 }; // Give 3 or 4
	for (size_t i = 1; i < LEVEL; i++)
	{
		for (auto& p : ps)
		{			
			auto& aaps{ p.aaps }; auto aaps_temp{ aaps };
			for (auto aa:aaps_temp)
			{		
				for (auto& a : ps[aa].aps)					
					aaps.insert(a);
			}		
		}
	}

	for (size_t i = 0; auto& p : ps)
	{
		auto& aaps{ p.aaps };	
		aaps.erase(i);		
		i++;
	}
}


//new positions calculation
void OptimizedNodes::new_positions_calculation()
{
	for (auto& p : ps)
	{
		if (p.isatboundary == false)
		{
			auto& dx = p.dx; dx = 0.0;
			auto& dy = p.dy; dy = 0.0;
			for (auto& a : p.aaps)
			{
				auto& pa{ ps[a] };
				double length = std::hypot(pa.x - p.x, pa.y - p.y);
				double r = p.r + pa.r;
				
				double f = (length > r) ? 0.0 : (length - r);
				double nx = (pa.x - p.x) / length;
				double ny = (pa.y - p.y) / length;
				dx += 0.1 * f * nx;
				dy += 0.1 * f * ny;
			}			
		}
	}

	for (auto& p : ps)
	{
		if (p.isatboundary == false)
		{
			p.x += p.dx;
			p.y += p.dy;
		}		
	}
}


//radii calculation
void OptimizedNodes::radii_calculation()
{
	for (auto&& p : ps)
	{
		if (p.isatboundary == false)
		{		
			double sum_r{ 0.0 }, sum{ 0.0 };
			for (auto& a : p.aaps)
			{
				auto& pa{ ps[a] };
				auto length = std::hypot(pa.x - p.x, pa.y - p.y);
				double r = p.r + pa.r;
				if (length < r)
				{
					sum_r += pa.r / length;
					sum += 1.0 / length;
				}
			}

			p.dr= sum_r / sum - p.r;
		}
	}

	for (auto&& p : ps)
	{
		if (p.isatboundary==false)			
		p.r+= p.dr;
	}
}




void OptimizedNodes::optimization()
{
	//double r_max{ 0.0 };

	size_t NN {10 * static_cast<size_t> (std::sqrt(ps.size())) };

	for (size_t i = 0; i < NN; i++)
	{
		for (size_t j = 0; j < 20; j++)
			new_positions_calculation();

		radii_calculation();		
		
		if (i % (10) == 0)
		{
			output();
			continue;
		}

	}
}




void OptimizedNodes::output() const
{
	const std::string name{ "./Data/OptimizedNodes.txt" };	
	std::ofstream ost;
	ost.open(name);
	// output Points 
	ost << "Points\n";
	ost << ps.size() << '\n';
	for (size_t i = 1; auto& p : ps)
	{		
		ost << std::scientific << i << '\t'
			<< p.x << '\t' << p.y << '\t' << p.r << '\n';
		i++;
	}

	// output Triangles 
	ost << "Triangles\n";
	ost << ts.size() << '\n';
	for (size_t i = 1; auto& t : ts)
	{	
		ost << std::scientific << i << '\t'
			<< t.a << '\t' << t.b << '\t' << t.c << '\t' << '\n';
		i++;
	}

	// output Edges 
	ost << "Edges\n";
	ost << es.size() << '\n';
	for (size_t i = 1; auto& e : es)
	{		
		ost << std::scientific << i << '\t'
			<< e.a << '\t' << e.b << '\t' << e.id << '\t' << '\n';
		i++;
	}
	ost.close();
}





