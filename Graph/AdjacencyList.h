#ifndef _ADJACENCYLIST_H
#define	_ADJACENCYLIST_H

#include "Graph.h"

#include <vector>
#include <utility>

namespace graph {

    class AdjacencyList : public Graph, public std::enable_shared_from_this<AdjacencyList> {
        std::vector<std::vector<std::pair<int, float> > > list_;
    public:
        AdjacencyList();
        AdjacencyList(const AdjacencyList& orig);
        virtual ~AdjacencyList();
		
		virtual size_t getSize() const;
		
		virtual void addNode(size_t id);
		virtual void resize(size_t size);
        virtual void addEdge(size_t viId, size_t vjId, float weight);
        virtual void addEdge(size_t viId, size_t vjId);
        virtual bool hasEdge(size_t vi, size_t vj) const;
		virtual float getEdge(size_t i, size_t j) const;
		
        virtual std::vector<size_t> getNeighbours(size_t v) const;
		
        virtual void load(std::string filename);
        virtual void save(std::string filename) const;
		
		virtual void convert(std::shared_ptr<Graph> g);

		virtual std::string toString();

    private:

    };
}
#endif	/* ADJACENCYLIST_H */

