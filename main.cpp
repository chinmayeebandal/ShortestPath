#include <iostream>
#include <vector>
#include "graph.hpp"

int main(){
  graphR grp;
  grp.addRoute("Capen", "NSC", 10);
  grp.addRoute("Capen", "Knox", 5);
  grp.addRoute("NSC", "Knox", 4);
  grp.addRoute("Knox", "O'Brian", 8);
  grp.addRoute("NSC", "O'Brian", 15);
  grp.printRoute();
  grp.generatePath("Capen", "O'Brian");

  return 0;
}
