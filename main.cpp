#include <iostream>
#include <vector>
#include "graph.hpp"

int main(){
  graphR grp;
  grp.addRoute("Capen", "Talbert", 5);
  grp.addRoute("Capen", "Knox", 2);
  grp.addRoute("Capen", "Cooke", 8);
  grp.addRoute("Talbert", "Cooke", 3);
  grp.addRoute("NSC", "Cooke", 4);
  grp.addRoute("NSC", "Talbert", 1);
  grp.addRoute("Cooke", "Knox", 10);
  grp.printRoute();
  grp.generatePath("Capen", "O'Brian");

  return 0;
}
