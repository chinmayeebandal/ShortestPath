//#ifndef GRAPH_HPP
//#define GRAPH

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include "node.hpp"

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

    void printGraph(){
      std::cout << "Graph: " << std::endl;
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
      std::priority_queue<Node, std::vector<Node>, min_pqueue> Q;
      int idx1 = getIndex(currNode.bldg);
      int idx2 = getIndex(endNode.bldg);

      if(idx1 == -1 || idx2 == -1){
        std::cout << "Error! Point does not exist." << std::endl;
        return;
      }

     Node top;
     visit[idx1] = true;
     //std::cout << currNode.bldg << std::endl;
     path.push_back(currNode);

     if(currNode.bldg != endNode.bldg){
        for(int i = 1; i < list[idx1].size(); ++i){
          if(visit[getIndex(list[idx1][i].bldg)] == false){
             list[idx1][i].newDist = currNode.newDist + list[idx1][i].dist;
             Q.push(list[idx1][i]);
             //std::cout << list[idx1][i].bldg << " pushed into priority queue" << std::endl;
           }
        }

        int saveNewDist = Q.top().newDist; // this is the actual updated newDist
        //std::cout << " savenewDist: " <<  Q.top().bldg << saveNewDist << std::endl;

        top = getNode(Q.top().bldg); // top distance is INF here
        top.newDist = saveNewDist;
        top.prev = currNode.bldg;
        currNode = top;

        dijkstra(currNode, endNode);
     }
    }

    void generatePath(std::string src, std::string tgt){
      for(int i = 0; i < list.size(); ++i){ //okay
        if(list[i][0].bldg == src) {
          list[i][0].newDist = 0;
          continue;
        }
        list[i][0].newDist = std::numeric_limits<int>::max();
      }

      Node currNode = getNode(src);
      Node endNode = getNode(tgt);

      if(currNode.bldg == "" || endNode.bldg == ""){ //Okay
        std::cout << "Error! Enter valid point." << std::endl;
        return;
      }

     dijkstra(currNode, endNode);
    }

    void printPath(std::string src, std::string tgt){
      std::cout << "Route from " << src << " to " << tgt << ": " << std::endl;

      int s, t;
      for(int i = 0; i < path.size(); ++i){
        if(path[i].bldg == src) s = i;
        if(path[i].bldg == tgt) t = i;
        continue;
      }
      for(int i = s; i<t; ++i){
        std::cout << path[i].bldg << "->";
      }
      std::cout << path[t].bldg << std::endl;
    }

  private:
    std::vector< std::vector<Node> > list;
    std::string bldgs[5] = {"Capen", "Talbert", "NSC", "Cooke", "Knox"};
    bool visit[5] = {false, false, false, false, false};
    std::vector<Node> path;
};
//#endif
