	
#include "Graph.h"

void Graph::load(std::string filename, Representation type){
	switch(type){
		case AdjacencyMatrix:
			return AdjacencyMatrix::load(filename);
		break;
		
		case AdjacencyList:
			return AdjacencyList::load(filename);
		break;
		
		default:
		break;
	}
}