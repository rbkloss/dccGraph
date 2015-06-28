#ifndef GRAFO_H
#define	GRAFO_H

#include <memory>
#include <vector>

enum Representation { AdjacencyMatrix, AdjacencyList };

namespace graph {

   class Graph {
    public:
		virtual std::pair<size_t, size_t> getSize() const = 0;//|V| |E|

		
		virtual void addNode(size_t id) = 0;
		virtual void resize(size_t size) = 0;
		virtual bool hasEdge(size_t vi, size_t vj) const = 0;
		virtual float getEdge(size_t i, size_t j) const = 0;
        virtual void addEdge(size_t viId, size_t vjId) = 0;
        virtual void addEdge(size_t viId, size_t vjId, float weight) = 0;
		virtual std::vector<size_t> getNeighbours(size_t v) const = 0;
		
		virtual void convert(std::shared_ptr<Graph> g) = 0;

        virtual void load(std::string filename) = 0;
        virtual void save(std::string filename) const = 0;

		virtual std::string toString() = 0;
    private:

    };
}
#endif	/* GRAFO_H */

