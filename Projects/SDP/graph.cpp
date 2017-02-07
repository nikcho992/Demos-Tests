#include <iostream>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <assert.h>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

template <class VT,class LT> // VT- vertex type ; LT- label type
class Graph
{
private:
	map<VT,list<pair<VT,LT>>> edges; //for each vertex the map returns a list with all the in/out edges
	string stringOfLabels(VT start,VT end,const Graph<VT,LT> g,set<VT>& visited);
public:
	void addVertex(const VT&);
	void addEdge(const VT&,const VT&,const LT&); //start/end vertex + label for the edge
	list<pair<VT,LT>> edgesFrom(const VT&) const; //returns a list IF ONLY the given vertex exists
	void print();
	bool hasCycle(const Graph<VT,LT> g);
	string stringOfLabels(VT start,VT end,const Graph<VT,LT> g);
	bool hasPath(VT start,const char* str,const Graph<VT,LT> g);
	LT getLabel(const VT& out,const VT& in);
	bool hasPathDFS(const VT& start,const VT& end,const Graph<VT,LT> g);
	bool hasPathBFS(const VT& start,const VT& end,const Graph<VT,LT> g);
};

template<class VT,class LT>
void Graph<VT,LT>::addVertex(const VT& newVertex)
{
	edges[newVertex]; //if newVertex doesn't exists,it is created immediately
}

template<class VT,class LT>
void Graph<VT,LT>::addEdge(const VT& out,const VT& in,const LT& label)
{
	addVertex(out);
	addVertex(in);
	edges[out].push_back(pair<VT,LT>(in,label)); // edges[out] --> returns a list --> push to it a pair with the new vertex and the label of the edge
}

template<class VT,class LT>
list<pair<VT,LT>> Graph<VT,LT>::edgesFrom(const VT& out) const
{
	return edges.at(out); // returns a result IF ONLY 'out' exists (specification of .at()) ; otherwise -> out_of_range exception
}

template<class VT,class LT>
void Graph<VT,LT>::print()
{
	for(const pair<VT,list<pair<VT,LT>>>& mapEl : edges)
	{
		for(const pair<VT,LT>& edge : mapEl.second)
		{
			cout<<mapEl.first<<" -> "<<"("<<edge.first<<","<<edge.second<<")"<<endl;
		}
	}
	cout<<endl;
}

template<class VT,class LT>
bool Graph<VT,LT>::hasCycle(const Graph<VT,LT> g)
{
	for(const pair<VT,list<pair<VT,LT>>>& mapEl : edges)
	{
		for(const pair<VT,LT>& edge : mapEl.second)
		{
			if(hasPathBFS(edge.first,mapEl.first,g))
			{
				return true;
			}
		}
	}
	return false;
}

template<class VT,class LT>
string Graph<VT,LT>::stringOfLabels(VT start,VT end,const Graph<VT,LT> g)
{
	set<VT> visited;
	return stringOfLabels(start,end,g,visited);
}

template<class VT,class LT>
string Graph<VT,LT>::stringOfLabels(VT start,VT end,const Graph<VT,LT> g,set<VT>& visited)
{
	if(start == end)
		return " ";

	visited.insert(start);

	for(const pair<VT,LT> edge : g.edgesFrom(start))
	{
		if(visited.count(edge.first) == 0)
		{
			string nextString = stringOfLabels(edge.first,end,g,visited);

			if(!nextString.empty())
			{
				return edge.second + nextString;
			}

			if(edge.first == end) //the first time "going up" after hitting the bottom
			{
				string result;
				result += edge.second;
				return result;
			}
		}
	}
	return " ";
}

template<class VT,class LT>
bool Graph<VT,LT>::hasPath(VT start,const char* str,const Graph<VT,LT> g)
{
	if(*str == 0)
		return true;

	for(const pair<VT,LT>& edge : g.edgesFrom(start))
	{
		if(edge.second == *str && hasPath(edge.first,str+1,g))
		{
			return true;
		}
	}
	return false;
}

template<class VT,class LT>
LT Graph<VT,LT>::getLabel(const VT& out,const VT& in)
{
	assert(edges.count(out) != 0); //we make sure that both 'in' and 'out' vertices are in our graph
	assert(edges.count(in) != 0);

	for(const pair<VT,LT>& edge : edgesFrom(out))
	{
		if(edges.first == in)
		{
			return edges.second;
		}
	}

	assert(false);
	LT dummy;
	return dummy;
}

template<class VT,class LT>
bool Graph<VT,LT>::hasPathDFS(const VT& start,const VT& end,const Graph<VT,LT> g)
{
	stack<VT> s;
	set<VT> visited;

	s.push(start);
	visited.insert(start);

	while(!s.empty() && s.top() != end)
	{
		VT v = s.top();
		s.pop();

		for(const pair<VT,LT>& edge : g.edgesFrom(v))
		{
			const VT& neigh = edge.first;

			if(visited.count(neigh) == 0)
			{
				s.push(neigh);
				visited.insert(neigh);
			}
		}
	}
	return !s.empty();
}

template<class VT,class LT>
bool Graph<VT,LT>::hasPathBFS(const VT& start,const VT& end,const Graph<VT,LT> g)
{
	queue<VT> q;
	set<VT> visited;

	q.push(start);
	visited.insert(start);

	while(!q.empty() && q.front() != end)
	{
		VT v = q.front();
		q.pop();

		for(const pair<VT,LT>& edge : g.edgesFrom(v))
		{
			const VT& neigh = edge.first;

			if(visited.count(neigh) == 0)
			{
				q.push(neigh);
				visited.insert(neigh);
			}
		}
	}
	return !q.empty();
}


int main()
{
	Graph<int,char> g;

	g.addEdge (0,1,'a');
	g.addEdge (2,0,'c');

	g.addEdge (1,4,'b');
	g.addEdge (1,2,'b');
	g.addEdge (1,3,'b');
	g.addEdge (4,3,'x');
	g.addEdge (3,4,'z');

	//g.print();
	//cout<<endl;
	//cout<<g.stringOfLabels(0,3,g);
	//cout<<g.hasPath(1,"bz",g);
	cout<<g.hasPathBFS(3,1,g);
	//cout<<g.hasCycle(g);
}
