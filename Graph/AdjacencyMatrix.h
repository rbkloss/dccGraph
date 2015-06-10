#ifndef ADJACENCYMATRIX_H
#define	ADJACENCYMATRIX_H

#include "Graph.h"

namespace graph {

  class AdjacencyMatrix : public Graph, public std::enable_shared_from_this < AdjacencyMatrix > {
    std::vector<std::vector<float> > mat_;
    public:
    AdjacencyMatrix(size_t numberOfVertix);
    AdjacencyMatrix();
    AdjacencyMatrix(const AdjacencyMatrix& orig);
    virtual ~AdjacencyMatrix();

    virtual size_t getSize() const override;

    virtual void resize(size_t size) override;
    virtual void addNode(size_t id) override;
    virtual void addEdge(size_t startNodeId, size_t endNodeId) override;
    virtual void addEdge(size_t viId, size_t vjId, float weight) override;
    virtual bool hasEdge(size_t vi, size_t vj) const override;
    virtual float getEdge(size_t i, size_t j) const override;

    virtual std::vector<size_t> getNeighbours(size_t v) const override;

    virtual void load(std::string filename) override;
    virtual void save(std::string filename) const override;

    virtual void convert(std::shared_ptr<Graph> g) override;

    virtual std::string toString() override;
  };
}

#endif	/* ADJACENCYMATRIX_H */

