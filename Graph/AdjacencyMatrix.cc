/*
 * File:   AdjacencyMatrix.cc
 * Author: ricardo
 *
 * Created on March 12, 2015, 8:50 PM
 */

#include "AdjacencyMatrix.h"
#include <fstream>
#include <algorithm>

namespace graph {

	AdjacencyMatrix::AdjacencyMatrix() {}

	AdjacencyMatrix::AdjacencyMatrix(size_t numberOfVertix) {
		mat_.resize(numberOfVertix);
		for (size_t i = 0; i < mat_.size(); ++i)
			mat_[static_cast<int>(i)].resize(numberOfVertix);
	}

	AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix& orig) {}

	AdjacencyMatrix::~AdjacencyMatrix() {}

  std::pair<size_t, size_t> AdjacencyMatrix::getSize() const {
    return std::make_pair(mat_.size(), nEdges);
	}

	void AdjacencyMatrix::resize(size_t size) {
		mat_.resize(size);
		for (size_t i = 0; i < mat_.size(); ++i)
			mat_[static_cast<int>(i)].resize(size);
	}

	void AdjacencyMatrix::addEdge(size_t startNodeId, size_t endNodeId) {
		addEdge(startNodeId, endNodeId, 1);
	}

	void AdjacencyMatrix::addEdge(size_t viId, size_t vjId, float weight) {
		mat_[viId][vjId] = weight;
    if (!hasEdge(vjId, viId)) {
      ++nEdges;
    }
	}
	float AdjacencyMatrix::getEdge(size_t i, size_t j) const {
		return mat_[i][j];
	}

	void AdjacencyMatrix::addNode(size_t id) {}

	std::vector<size_t> AdjacencyMatrix::getNeighbours(size_t v) const {
		std::vector<size_t> ans;
		auto size = mat_.size();
		for (size_t i = 0; i < size; ++i) {
			if ((mat_[v][static_cast<int>(i)] != 0))
				ans.push_back(i);
		}
		return ans;
	}

	bool AdjacencyMatrix::hasEdge(size_t vi, size_t vj) const {
		return (mat_[vi][vj] != 0);
	}

	void AdjacencyMatrix::load(std::string filename) {
		std::ifstream inpFile(filename);

		int size = 0;
		inpFile >> size;
		mat_.clear();
		mat_.resize(size);
		for (size_t i = 0; i < mat_.size(); ++i) {
			mat_[static_cast<int>(i)].resize(size);
			for (size_t j = 0; j < mat_.size(); ++j) {
				inpFile >> mat_[static_cast<int>(i)][static_cast<int>(j)];
			}
		}
		inpFile.close();
	}

	void AdjacencyMatrix::save(std::string filename) const {
		std::ofstream outFile(filename);
		outFile << mat_.size();
		for (size_t i = 0; i < mat_.size(); ++i) {

			for (size_t j = 0; j < mat_.size(); ++j) {
				outFile << mat_[i][j] << " ";
			}
			outFile << std::endl;
		}
		outFile.close();
	}

	void AdjacencyMatrix::convert(std::shared_ptr<Graph> g) {
		auto size = g->getSize().first;
		resize(size);
		auto ptr = this->shared_from_this();
		for (size_t i = 0; i < size; ++i) {
			auto neighbours = g->getNeighbours(i);
			std::for_each(neighbours.begin(), neighbours.end(), [i, ptr](const size_t& j) {
				ptr->addEdge(i, j);
			});
		}
	}

std::string AdjacencyMatrix::toString(){
  return {};
}


}
