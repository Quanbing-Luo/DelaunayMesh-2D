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
	ps.emplace_back(1820.0, 2162.0); // 1
	ps.emplace_back(1924.0, 2102.0);
	ps.emplace_back(1999.0, 1990.0);
	ps.emplace_back(2027.0, 1867.0);
	ps.emplace_back(2051.0, 1778.0); // 5
	ps.emplace_back(2060.0, 1633.0);
	ps.emplace_back(2088.0, 1515.0);
	ps.emplace_back(2140.0, 1393.0);
	ps.emplace_back(2182.0, 1276.0);
	ps.emplace_back(2201.0, 1163.0); //10
	ps.emplace_back(2197.0, 1041.0); 
	ps.emplace_back(2178.0, 919.0);
	ps.emplace_back(2121.0, 811.0);
	ps.emplace_back(2065.0, 707.0);
	ps.emplace_back(1989.0, 612.0); // 15
	ps.emplace_back(1910.0, 533.0); 
	ps.emplace_back(1807.0, 482.0);
	ps.emplace_back(1670.0, 426.0);
	ps.emplace_back(1532.0, 402.0);
	ps.emplace_back(1405.0, 400.0); //20
	ps.emplace_back(1269.0, 380.0);
	ps.emplace_back(1139.0, 403.0);
	ps.emplace_back(1036.0, 435.0);
	ps.emplace_back(932.0, 541.0);
	ps.emplace_back(905.0, 646.0); //25
	ps.emplace_back(1036.0, 725.0);
	ps.emplace_back(1142.0, 732.0);
	ps.emplace_back(1269.0, 724.0);
	ps.emplace_back(1403.0, 721.0);
	ps.emplace_back(1511.0, 745.0); // 30
	ps.emplace_back(1591.0, 829.0);
	ps.emplace_back(1619.0, 914.0);
	ps.emplace_back(1620.0, 1024.0);
	ps.emplace_back(1568.0, 1123.0);
	ps.emplace_back(1389.0, 1252.0); //35
	ps.emplace_back(1266.0, 1285.0);
	ps.emplace_back(1130.0, 1284.0);
	ps.emplace_back(1016.0, 1288.0);
	ps.emplace_back(884.0, 1289.0);
	ps.emplace_back(966.0, 1202.0); // 40
	ps.emplace_back(1093.0, 1154.0);
	ps.emplace_back(1229.0, 1116.0);
	ps.emplace_back(1304.0, 1064.0);
	ps.emplace_back(1276.0, 933.0);
	ps.emplace_back(1167.0, 882.0); // 45
	ps.emplace_back(1064.0, 885.0);
	ps.emplace_back(950.0, 939.0);
	ps.emplace_back(831.0, 937.0);
	ps.emplace_back(736.0, 961.0);
	ps.emplace_back(604.0, 994.0); // 50
	ps.emplace_back(487.0, 1044.0); 
	ps.emplace_back(412.0, 1135.0);
	ps.emplace_back(358.0, 1221.0);
	ps.emplace_back(332.0, 1294.0);
	ps.emplace_back(333.0, 1421.0); // 55
	ps.emplace_back(337.0, 1562.0);
	ps.emplace_back(390.0, 1691.0);
	ps.emplace_back(464.0, 1798.0);
	ps.emplace_back(571.0, 1851.0);
	ps.emplace_back(676.0, 1931.0); // 60
	ps.emplace_back(757.0, 2037.0);
	ps.emplace_back(860.0, 2091.0);
	ps.emplace_back(1004.0, 2088.0);
	ps.emplace_back(1102.0, 2055.0);
	ps.emplace_back(1247.0, 2115.0); // 65
	ps.emplace_back(1391.0, 2136.0);
	ps.emplace_back(1525.0, 2159.0);
	ps.emplace_back(1656.0, 2182.0);
	ps.emplace_back(806.0, 1764.0);
	ps.emplace_back(750.0, 1680.0); //70
	ps.emplace_back(647.0, 1609.0);
	ps.emplace_back(590.0, 1506.0);
	ps.emplace_back(642.0, 1426.0);
	ps.emplace_back(750.0, 1398.0);
	ps.emplace_back(830.0, 1449.0); // 75
	ps.emplace_back(908.0, 1520.0); 
	ps.emplace_back(938.0, 1606.0);
	ps.emplace_back(881.0, 1708.0);
	ps.emplace_back(1459.0, 1708.0);
	ps.emplace_back(1303.0, 1708.0); //80
	ps.emplace_back(1309.0, 1590.0);
	ps.emplace_back(1386.0, 1492.0);
	ps.emplace_back(1488.0, 1414.0);
	ps.emplace_back(1624.0, 1360.0);
	ps.emplace_back(1760.0, 1332.0); //85
	ps.emplace_back(1886.0, 1335.0);
	ps.emplace_back(1889.0, 1466.0);
	ps.emplace_back(1813.0, 1569.0);
	ps.emplace_back(1708.0, 1603.0);
	ps.emplace_back(1586.0, 1680.0); //90

	for (auto& p:ps)
	{
		p.y = 2518 - p.y;		
	}
	
	constexpr size_t N1{ 90 };
	for (size_t i = 0; i < N1; i++)
	{

		es.emplace_back(i, i + 1, 1);
	}
	es[67].b = 0;
	es[77].b = 68;
	es[89].b = 78;
	
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




