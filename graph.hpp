//#ifndef GRAPH_HPP
//#define GRAPH

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <stack>

struct Node{
  std::string bldg;
  int dist;
  bool visit;
  int newDist;
  std::string prev;

  Node(){}
  Node(std::string b, int d) : bldg(b), dist(d), visit(false), prev(""){}

  void setVisit(bool set){ visit = set; }
  void setNewDist(int d) { newDist = d; }
  void setPrev(std::string p){ prev = p; }
};

struct min_pqueue{
  bool operator()(const Node lhs, const Node rhs){
    if(lhs.dist < rhs.dist){
      return true;
    }
    //implement equality
  /*  else if(lhs.dist == rhs.dist){
      if(word1->first > word2->first){
                  return true;
                }
              }*/
    return false;
  }
};


class graphR{

  public:
    graphR(){
      for(int i = 0; i < (sizeof(bldgs)/sizeof(*bldgs)); ++i){
        std::vector<Node> v;
        v.push_back(Node(bldgs[i], 0));
        list.push_back(v);
      }
    }

    int getSize() const{ return list.size();}

    int getIndex(std::string var){
      for(int i = 0; i < list.size(); ++i){
        if(var == list[i][0].bldg) return i;
      }
      return -1;
    }

    Node getNode(std::string str){
      Node n;
      for(int i = 0; i < list.size(); ++i){
        if(str == list[i][0].bldg)
          return (list[i][0]);
      }
      return n; //don't forget to check for null Node wherever getNode is used
    }

    void printRoute(){
      for(int i=0; i < list.size(); ++i){
        for(auto x : list[i]){
          std::cout << x.bldg << x.dist << "->";
        }
        std::cout << std::endl;
      }
    }

    void addRoute(std::string src, std::string tgt, int dist){
      int idxFrom, idxTo = 0;
      for(int i = 0; i < list.size(); ++i){
        if(list[i][0].bldg == src) idxFrom = i;
        if(list[i][0].bldg == tgt) idxTo = i;
        continue;
      }
      list[idxFrom].push_back(Node(tgt, dist));
      list[idxTo].push_back(Node(src, dist));
    }

    void dijkstra(Node currNode, Node endNode){
      if (currNode.bldg == endNode.bldg) return;

      std::priority_queue<Node, std::vector<Node>, min_pqueue> Queue;

      //set similar nodes to true
      int idx = getIndex(currNode.bldg);
      for(int i = 1; i<list.size(); ++i){ //skip 1st elem
        if(list[idx][0].visit == false){
          list[idx][i].newDist = currNode.newDist + list[idx][i].dist;
          Queue.push(list[idx][i]);
        }
      }
      Node temp = Queue.top();
      temp.prev = currNode.bldg;
      currNode.visit = true;
      currNode = temp;

      dijkstra(currNode, endNode);
    }
    void generatePath(std::string src, std::string tgt){
      int idxSrc = getIndex(src);

      for(int i = 0; i < list.size(); ++i){
        if(i != idxSrc) {
          list[i][0].setNewDist(std::numeric_limits<int>::max());
        }
        list[i][0].setNewDist(0);
      }

      Node currNode = getNode(src);
      Node endNode = getNode(tgt);

      dijkstra(currNode, endNode);

      std::stack<std::string> stck;
      while(endNode.bldg == ""){
        std::string str = endNode.prev;
        stck.push(str);
        endNode = getNode(str);
      }

      while(!stck.empty()){
        std::cout << stck.top() << " -> ";
        stck.pop();
      }
      std::cout << tgt;
      std::cout << std::endl;

    }

  private:
    //int size = 4;
    std::vector< std::vector<Node> > list;
    std::string bldgs[5] = {"Capen", "Talbert", "NSC", "Cooke", "Knox"};
};
//#endif
