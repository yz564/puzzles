#include <cstdio>
#include <vector>
#include <set>
#include <bits/stdc++.h>
using namespace std;
class mynode{
  public:
  int x, y;
  char g;
  mynode(int x, int y, char g): x(x),y(y),g(g) {}
};

mynode* find_start(int R, int C, vector<vector<char>>& G, set<mynode*>* portals[], vector<vector<mynode*>>& GG){
  int i,j;
  mynode* start = nullptr;
  for (i=0; i<R; i++){
    for (j=0;j<C;j++){
      if (G[i][j]=='S'){
        start = new mynode(i,j,G[i][j]);
        GG[i][j]=start;
      }
      else if (G[i][j]<='z' && G[i][j]>='a'){
        mynode* node = new mynode(i,j,G[i][j]);
        (*(portals[G[i][j]-'a'])).insert(node);
        GG[i][j]=node;
      }
      else if (G[i][j]=='#'){
        GG[i][j]=nullptr;
      }
      else{
        mynode* node = new mynode(i,j,G[i][j]);
        GG[i][j]=node;
      }
    }
  }
  return start;
}
int collect_next_nodes(int R, int C, vector<vector<mynode*>>& G, mynode* current_node, vector<mynode*>& next_nodes, set<mynode*>* portals[]){
  int x=current_node->x;
  int y=current_node->y;
  char g=current_node->g;
  printf("next_nodes:size=%d\n",next_nodes.size());
  
  printf("x=%d, y=%d,g=%c\n",x,y,g);
  if (g=='E'){
    return 0;
  }
  if (x+1<R && G[x+1][y]!=nullptr && (g == '.' || G[x+1][y]->g != g)){
    next_nodes.push_back(G[x+1][y]);
  }
  if (x-1>=0 && G[x-1][y]!=nullptr && (g == '.' || G[x-1][y]->g != g)){
    next_nodes.push_back(G[x-1][y]);
  }
  if (y+1<C && G[x][y+1]!=nullptr && (g == '.' || G[x][y+1]->g != g)){
    next_nodes.push_back(G[x][y+1]);
  }
  if (y-1>=0 && G[x][y-1]!=nullptr && (g == '.' || G[x][y-1]->g != g)){
    next_nodes.push_back(G[x][y-1]);
  }
  if (g <= 'z' && g >= 'a') {
    set<mynode*>* myset = portals[g - 'a'];
    if (!myset->empty()) {
      for (auto it=myset->begin(); it!=myset->end();){
	printf("next_nodes:size2=%d\n",next_nodes.size());
	printf("next_nodes: x=%d,y=%d,g=%c\n",(*it)->x,(*it)->y,(*it)->g);
	if (*it != current_node){
	  next_nodes.push_back(*it);
	  printf("next_nodes_3: x=%d,y=%d,g=%c\n",(*it)->x,(*it)->y,(*it)->g);
	}
	it++;
      }
      myset->clear();
      printf("portals length = %d\n",(*(portals[g - 'a'])).size());
    }
  }
  //delete current_node;
  G[x][y]=nullptr;
  return 1;
}
int getSecondsRequired(int R, int C, vector<vector<char>> G) {
  printf("function begin\n");
  vector<mynode*> my_current_stack;
  vector<mynode*> my_next_stack;
  my_current_stack.clear();
  my_next_stack.clear();
  set<mynode*>* portals[26];
  for (int i = 0; i < 26; i++) {
    portals[i] = new std::set<mynode*>();
  }
  vector<vector<mynode*>> GG(R, std::vector<mynode*>(C));
  mynode* start = find_start(R,C, G, portals, GG);
  int ans=0;
  ans += collect_next_nodes(R,C,GG, start, my_current_stack, portals);
  while (!my_current_stack.empty()){
    mynode* current_node = my_current_stack.back();  // Use back() to get the last element
    my_current_stack.pop_back();  // Use pop_back() to remove the last element
    int ret = collect_next_nodes(R,C,GG, current_node, my_next_stack, portals);
    if (ret == 0) return ans;
    if (my_current_stack.empty()){
      ans+=1;
      while (!my_next_stack.empty()){
        mynode* current_node2 = my_next_stack.back();  // Use back() to get the last element
	printf("current_node2: x=%d,y=%d,g=%c\n",current_node2->x,current_node2->y,current_node2->g);
        my_next_stack.pop_back();  // Use pop_back() to remove the last element
        int ret = collect_next_nodes(R,C,GG, current_node2, my_current_stack, portals);
        if (ret == 0) return ans;
      }
      ans+=1;
    }
  }
  return -1;
}

int main(int argc, char* argv[]){
  int R=3;
  int C=4;
  vector<vector<char>> G(R, std::vector<char>(C));
  /*
  G[0][0] = 'a';
  G[0][1] = 'S';
  G[0][2] = '.';
  G[0][3] = 'b';
  G[1][0] = '#';
  G[1][1] = '#';
  G[1][2] = '#';
  G[1][3] = '#';
  G[2][0] = 'E';
  G[2][1] = 'b';
  G[2][2] = '.';
  G[2][3] = 'a';
  */
  G[0][0] = 'a';
  G[0][1] = '.';
  G[0][2] = 'S';
  G[0][3] = 'a';
  G[1][0] = '#';
  G[1][1] = '#';
  G[1][2] = '#';
  G[1][3] = '#';
  G[2][0] = 'E';
  G[2][1] = 'b';
  G[2][2] = '.';
  G[2][3] = 'b';
  int ans = getSecondsRequired(R,C,G);
  printf ("the minimum steps of moving from S to E = %d\n",ans);
  return 0;
}
