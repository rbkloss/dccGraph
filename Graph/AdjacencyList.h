#ifndef _ADJACENCYLIST_H
#define	_ADJACENCYLIST_H

#include "Graph.h"

#include <vector>
#include <utility>

namespace graph {

  class AdjacencyList : public Graph, public std::enable_shared_from_this < AdjacencyList > {
    std::vector<std::vector<std::pair<int, float> > > list_;
    size_t nEdges = 0;
    public:
    AdjacencyList();
    AdjacencyList(const AdjacencyList& orig);
    virtual ~AdjacencyList();

    virtual std::pair<size_t, size_t> getSize() const override;

    virtual void addNode(size_t id) override;
    virtual void resize(size_t size) override;
    virtual void addEdge(size_t viId, size_t vjId, float weight) override;
    virtual void addEdge(size_t viId, size_t vjId) override;
    virtual bool hasEdge(size_t vi, size_t vj) const override;
    virtual float getEdge(size_t i, size_t j) const override;

    virtual std::vector<size_t> getNeighbours(size_t v) const override;

    virtual void load(std::string filename) override;
    virtual void save(std::string filename) const override;

    virtual void convert(std::shared_ptr<Graph> g) override;

    virtual std::string toString() override;

    private:

  };
}
#endif	/* ADJACENCYLIST_H */

