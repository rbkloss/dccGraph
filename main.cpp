/* 
 * File:   main.cpp
 * Author: ricardo
 *
 * Created on March 12, 2015, 7:59 PM
 */

#include <cstdlib>

#include "dccGraph.h"
#include <memory>
#include <iostream>
#include <sstream>
/*
 * 
 */
int main(int argc, char** argv) {

	
	auto adjMat = std::make_shared<graph::AdjacencyMatrix>();
	adjMat->load("inpTest.txt");
	auto adjList = std::make_shared<graph::AdjacencyList>();
	adjList->convert(adjMat);
	adjList->save("adjList.txt");

    return 0;
}

