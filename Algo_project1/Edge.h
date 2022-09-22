#pragma once
#include <iostream>
using std::ostream;
class Edge
{
private:
    int _srcVertex;
    int _destVertex;
    int _weight;
    Edge* oppstDirectionEdge = nullptr;
public:
    Edge(int srcV, int dstV, int weight):_srcVertex(srcV),_destVertex(dstV),_weight(weight){}
    Edge() { }

    void setSrc(int s){ _srcVertex = s;}
    int getSrc()const {return _srcVertex;}
    void setDest(int d){_destVertex = d;}
    int getDest()const {return _destVertex;}
    void setWeight(int w){_weight = w;}
    int getWeight()const {return _weight;}
    void setOppositeDirectionEdge(Edge* ed) { oppstDirectionEdge = ed; }
    Edge* getOppositeDirectionEdge() const { return oppstDirectionEdge; }
    friend ostream& operator<<(ostream& os, const Edge& item) {
        os << item._weight << ':' << item._srcVertex << "->" << item._destVertex;
        return os;
    }
    bool operator==(const Edge& other) const {
        if (oppstDirectionEdge == nullptr)
            return _srcVertex == other._srcVertex && _destVertex == other._destVertex;
        else
            return (_srcVertex == other._srcVertex && _destVertex == other._destVertex
                || oppstDirectionEdge->_srcVertex == other._srcVertex && oppstDirectionEdge->_destVertex == other._destVertex);
    }
};

