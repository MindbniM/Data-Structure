#include"graph.hpp"
int main()
{
	matrix::graph<char, int> g({'a', 'b','c','d','e','f','g','h','i'});
	g.insert_edge('a', 'b', 4);
	g.insert_edge('a', 'h', 8);
	g.insert_edge('b', 'c', 8);
	g.insert_edge('b', 'h', 11);
	g.insert_edge('c', 'i', 2);
	g.insert_edge('c', 'f', 4);
	g.insert_edge('c', 'd', 7);
	g.insert_edge('d', 'f', 14);
	g.insert_edge('d', 'e', 9);
	g.insert_edge('e', 'f', 10);
	g.insert_edge('f', 'g', 2);
	g.insert_edge('g', 'h', 1);
	g.insert_edge('g', 'i', 6);
	g.insert_edge('h', 'i', 7);
	return 0;
}