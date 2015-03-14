/*
 * File:   AdjacencyList.cc
 * Author: ricardo
 *
 * Created on March 12, 2015, 10:24 PM
 */

#include "AdjacencyList.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace graph {

	AdjacencyList::AdjacencyList() {}

	AdjacencyList::AdjacencyList(const AdjacencyList& orig) {}

	AdjacencyList::~AdjacencyList() {}

	size_t AdjacencyList::getSize()const {
		return list_.size();
	}

	void AdjacencyList::resize(size_t size) {
		list_.resize(size);
	}

	void AdjacencyList::addEdge(size_t viId, size_t vjId, float weight) {
		//TODO: node existance verification
		list_[viId].push_back(std::pair<int, float>(vjId, weight));
	}

	void AdjacencyList::addEdge(size_t viId, size_t vjId) {
		addEdge(viId, vjId, 1);
	}
	float AdjacencyList::getEdge(size_t i, size_t j) const {
		if (!hasEdge(i, j)) {
			throw std::exception("Edge not found!");
		}
		auto weight = 0.0f;
		for (auto p : list_[i]) {
			if (p.first == j) {
				weight = p.second;
			}
		}
		return weight;
	}

	void AdjacencyList::addNode(size_t id) {
		list_.push_back(std::vector<std::pair<int, float> >());
	}

	std::vector<size_t> AdjacencyList::getNeighbours(size_t v) const {
		std::vector<size_t> ans;
		std::for_each(list_[v].begin(), list_[v].end(), [&ans](const std::pair<int, float> &p) {
			ans.push_back((size_t)p.first);
		});
		return ans;
	}

	bool AdjacencyList::hasEdge(size_t vi, size_t vj) const {
		for (size_t i = 0; i < list_[vi].size(); ++i) {
			std::pair<int, float> el = (list_[vi][(int)i]);
			if (el.first == vj) return true;
		}
		return false;
	}

	void AdjacencyList::load(std::string filename) {
		std::ifstream inpFile(filename);
		
		list_.clear();
		int size = 0;
		while (!inpFile.eof()) {
			std::string line;
			std::getline(inpFile, line);
			std::stringstream ss(line);
			int i = 0;
			ss >> i;
			list_.resize(++size);
			while (!ss.eof()) {
				float weight;
				ss >> i;
				ss >> weight;
				list_[size - 1].push_back(std::pair<int, float>(i, weight));
			}
		}
		inpFile.close();
	}

	void AdjacencyList::save(std::string filename) const {
		std::ofstream outFile(filename);
		for (size_t i = 0; i < list_.size(); ++i) {
			outFile << i << " ";
			for (size_t j = 0; j < list_[i].size(); ++j) {
				outFile << list_[i][j].first << " " << list_[i][j].second<<" ";
			}
			outFile << std::endl;
		}
		outFile.close();
	}

	void AdjacencyList::convert(std::shared_ptr<Graph> g) {
		auto size = g->getSize();
		auto ptr = this->shared_from_this();

		for (size_t i = 0; i < size; ++i) {
			auto neighbours = g-> getNeighbours(i);
			addNode(i);
			
			for_each(neighbours.begin(), neighbours.end(), [i, ptr, &g](const size_t& j) {
				auto weight = g->getEdge(i, j);
				ptr->addEdge(i, j, weight);
			});

		}
	}
}