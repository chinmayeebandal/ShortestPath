struct Node{
  std::string bldg;
  int dist;
  int newDist;
  std::string prev;

  Node() : bldg(""){}
  Node(std::string b, int d) : bldg(b), dist(d), prev(""){}
  Node(std::string b, int d, bool v) : bldg(b), dist(d), prev(""){}

};

struct min_pqueue{
  bool operator()(const Node lhs, const Node rhs){
    if(lhs.dist > rhs.dist){
      return true;
    }
    //implement equality
    else if(lhs.dist == rhs.dist){
      if(lhs.bldg > rhs.bldg){
        return true;
      }
    }
    return false;
  }
};
