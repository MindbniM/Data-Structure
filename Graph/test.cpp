#include"graph.hpp"
int main()
{
	matrix::graph<char, int> g({'0','5','4','1','3'});
	g.inset_edge('0', '3', 3);
	g.inset_edge('5', '1', 4);
	g.inset_edge('4', '1', 1);
	g.print();
	return 0;
}