#include <string>
#include <fstream>
#include <algorithm>
#include "Mesh.h"

// Initial_Mesh data input
void Mesh::input()
{
	std::ifstream ist;
	ist.open("InitialMesh.txt");
	std::string ss;	

	// input Points
	std::getline(ist, ss);
	size_t np{ 0 }; ist >> np;
	for (size_t i = 0; i < np; i++)
	{
		static size_t n{ 0 };
		static double x{ 0.0 }, y{ 0.0 }, r{ 0.0 };
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
		ist >> n >> a >> b >> c ;
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


//setTriangle
void Triangle::setTriangle(const Points& ps)
{
	auto [xa, ya, ra] { ps[a] };
	auto [xb, yb, rb] { ps[b] };
	auto [xc, yc, rc] { ps[c] };

	//the center of gravity
	x = (xa + xb + xc) / 3.0;
	y = (ya + yb + yc) / 3.0;


	double  lag{ std::hypot(x - xa, y - ya) };
	double  lbg{ std::hypot(x - xb, y - yb) };
	double  lcg{ std::hypot(x - xc, y - yc) };
	r = (ra / lag + rb / lbg + rc / lcg) /
		(1.0 / lag + 1.0 / lbg + 1.0 / lcg);

	// circumcenter and radius of Circumcircle
	xcc = (((pow(xb, 2) - pow(xa, 2)) + (pow(yb, 2) - pow(ya, 2))) * (yc - ya)
		- ((pow(xc, 2) - pow(xa, 2)) + (pow(yc, 2) - pow(ya, 2))) * (yb - ya))
		/ (2 * ((xb - xa) * (yc - ya) - (xc - xa) * (yb - ya)));

	ycc = (((pow(xb, 2) - pow(xa, 2)) + (pow(yb, 2) - pow(ya, 2))) * (xc - xa)
		- ((pow(xc, 2) - pow(xa, 2)) + (pow(yc, 2) - pow(ya, 2))) * (xb - xa))
		/ (2 * ((xc - xa) * (yb - ya) - (xb - xa) * (yc - ya)));

	rcc = hypot(xcc - xa, ycc - ya);

	area = abs(xa * yb + xb * yc + xc * ya - xa * yc - xb * ya - xc * yb) / 2.0;
	area_bubble = pi * std::pow(r, 2);
	
	d = area_bubble / area;
}

// mesh data initialization. 
void Mesh::initialization()
{	
		
	//Triangles initialization
	for (auto& t : ts)
		t.setTriangle(ps);
	

	//Lines initialization
	for (auto& t : ts)
	{
		static size_t i = 0;
		for (auto& l : t.lts)
			ls.emplace(l, i);
		area += t.area;
		area_bubble += t.area_bubble;
		++i;
	}
	//output();	
}


void Mesh::set_ns_cavity(size_t n)
{
	auto& t{ ts[n] };
	ns_cavity.clear(); 	ns_cavity.insert(n);
	std::vector<size_t> ns_cavity_vector{ n };
	for (size_t i = 0; i < ns_cavity_vector.size(); i++)
	{
		auto& nc{ ns_cavity_vector[i] };
		auto& tc{ ts[nc] };
		for (auto& l : tc.lts)
		{
			auto [begin, end] = ls.equal_range(l);
			for (auto itl = begin; itl != end; itl++)
			{
				auto& nb = itl->second;
				if (!ns_cavity.contains(nb))
				{
					if (hypot(t.x - ts[nb].xcc, t.y - ts[nb].ycc) < ts[nb].rcc)
					{
						ns_cavity.insert(nb);
						ns_cavity_vector.push_back(nb);
					}
				}				
			}
		}
	}
}


void Mesh::set_lbs_cavity()
{
	lbs_cavity.clear();	
	for (auto n: ns_cavity)
	{
		auto& t{ ts[n] };
		for (auto& l : t.lts)
		{
			//set lbs_cavity
			auto it = lbs_cavity.find(l);
			if (it == lbs_cavity.end())
				lbs_cavity.emplace(l);
			else
				lbs_cavity.erase(it);			
		}
	}

}

void Mesh::delete_old_cavity()
{
	for (auto n : ns_cavity)
	{
		auto& t{ ts[n] };
		area_bubble -= t.area_bubble;
		for (auto& l : t.lts)
		{
			auto [begin, end] = ls.equal_range(l);
			for (auto itl = begin; itl != end;)
			{				
				auto& nb = itl->second;
				//delete cavity lines from lines
				if (nb == n)				
					itl = ls.erase(itl);				
				else
					itl++;				
			}
		}
	}
}


void  Mesh::add_new_cavity()
{
	// set triangles and cavity		
	size_t np = ps.size() - 1;	
	auto itn = ns_cavity.cbegin();
	for (auto& l : lbs_cavity)
	{
		Triangle t{ l.a,l.b, np };
		t.setTriangle(ps);
		area_bubble += t.area_bubble;

		if (itn != ns_cavity.cend())
		{
			ts[*itn] = t;
			itn++;
		}
		else
		{
			ts.emplace_back(std::move(t));
			ns_cavity.insert(ts.size() - 1);
		}
	}

	// add cavity lines to lines
	for (auto n : ns_cavity)
	{
		for (auto& l : ts[n].lts)
		{
			ls.emplace(l, n);
		}
	}
}



// delaunay triangulation. 
void Mesh::delaunay_triangulation()
{
	size_t n{ 0 };
	for (size_t i = 0; i < 1e5; i++)
	{
		// the triangle who has min relative value 
		auto itt = std::min_element(ts.begin(), ts.end(),
			[](const auto& ta, const auto& tb) { return ta.d < tb.d; });
		n = std::distance(ts.begin(), itt);

		ps.emplace_back(itt->x, itt->y, itt->r);

		set_ns_cavity(n);
		set_lbs_cavity();		
		delete_old_cavity();	
		add_new_cavity();	

		if (area_bubble >= area)
			break;

		if (i % 50 == 0)
		{
			output();
			continue;
		}
	}
}


void Mesh::output() const
{
	const std::string name{ "./Data/Mesh.txt" };

	std::ofstream ost;
	ost.open(name);

	// output Points 
	ost << "Points\n";
	ost << ps.size() << '\n';
	for (size_t i = 1; auto& p : ps)
	{	
		ost << std::scientific << i << '\t'	<< p.x << '\t' << p.y << '\t' << p.r << '\n';
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




