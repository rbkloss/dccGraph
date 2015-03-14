#ifndef ADJACENCYMATRIX_H
#define	ADJACENCYMATRIX_H

#include "Graph.h"

namespace graph {

	class AdjacencyMatrix : public Graph, public std::enable_shared_from_this<AdjacencyMatrix> {
        std::vector<std::vector<float> > mat_;
    public:
        AdjacencyMatrix(size_t numberOfVertix);
		AdjacencyMatrix();
        AdjacencyMatrix(const AdjacencyMatrix& orig);
        virtual ~AdjacencyMatrix();
		
		virtual size_t getSize() const;

		virtual void resize(size_t size);
        virtual void addNode(size_t id);
        virtual void addEdge(size_t startNodeId, size_t endNodeId);
        virtual void addEdge(size_t viId, size_t vjId, float weight);
		virtual bool hasEdge(size_t vi, size_t vj) const;
        virtual float getEdge(size_t i, size_t j) const;

        virtual std::vector<size_t> getNeighbours(size_t v) const;

        virtual void load(std::string filename);
        virtual void save(std::string filename) const;
		
		virtual void convert(std::shared_ptr<Graph> g);

		virtual std::string toString();
    };
}

#endif	/* ADJACENCYMATRIX_H */

