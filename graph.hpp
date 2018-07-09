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

  Node() : bldg(""){}
  Node(std::string b, int d) : bldg(b), dist(d), visit(false), prev(""){}
  Node(std::string b, int d, bool v) : bldg(b), dist(d), visit(v), prev(""){}

  void setVisit(bool set){ visit = set; }
  void setNewDist(int d) { newDist = d; }
  void setPrev(std::string p){ prev = p; }
};

struct min_pqueue{
  bool operator()(const Node lhs, const Node rhs){
    if(lhs.dist > rhs.dist){
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
        v.push_back(Node(bldgs[i], 0, false));
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
      int idx1 = getIndex(currNode.bldg);
      int idx2 = getIndex(endNode.bldg);

      if(idx1 == -1 || idx2 == -1){
        std::cout << "Error! Point does not exist." << std::endl;
        return;
      }
      if (currNode.bldg == endNode.bldg) return;

      //std::cout << currNode.bldg << " " << currNode.newDist << ", " << endNode.bldg << " " << endNode.newDist << std::endl;

     if(currNode.bldg != endNode.bldg){
         std::priority_queue<Node, std::vector<Node>, min_pqueue> Q;

        for(int i = 1; i < list[idx1].size(); ++i){
           list[idx1][i].newDist = currNode.dist + list[idx1][i].dist;
           //std::cout << list[idx1][i].bldg << " " << list[idx1][i].newDist << std::endl;
           Q.push(list[idx1][i]);
           //std::cout << list[idx1][i].bldg << " pushed into priority queue" << std::endl;
        }

        Node top = getNode(Q.top().bldg);
        if(top.visit == true){
          Q.pop();
          //std::cout << "popped" << std::endl;
          top = getNode(Q.top().bldg);
          //std::cout << "Top element: " << top.bldg << std::endl;
        }
        //std::cout << top.visit << std::endl;
        top.prev = currNode.bldg; //set prev node
        currNode.visit = true;
        //std::cout << top.bldg << top.visit << std::endl;
     }
     //std::cout << currNode.bldg << std::endl;
    }

    void generatePath(std::string src, std::string tgt){
      for(int i = 0; i < list.size(); ++i){ //okay
        if(list[i][0].bldg == src) {
          list[i][0].newDist = 0;
          continue;
        }
        list[i][0].newDist = std::numeric_limits<int>::max();
      }

      /*for(int i=0; i<list.size(); ++i){
        std::cout << list[i][0].bldg << " " << list[i][0].newDist << std::endl;
      }*/

      Node currNode = getNode(src);
      Node endNode = getNode(tgt);

      if(currNode.bldg == "" || endNode.bldg == ""){ //Okay
        std::cout << "Error! Enter valid point." << std::endl;
        return;
      }
    //  std::cout << "Okay" << std::endl;


     dijkstra(currNode, endNode);

    /*  std::stack<std::string> stck;
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
      */

    }

  private:
    //int size = 4;
    std::vector< std::vector<Node> > list;
    std::string bldgs[5] = {"Capen", "Talbert", "NSC", "Cooke", "Knox"};
};
//#endif
