#include <bits/stdc++.h>
using namespace std;
// Write any include statements here
int get_single_step_time(int s, int e, int N){
  int t1 = (e-s)>0 ? e-s : s-e;
  int t2 = N-t1;
  return (t2<t1)? t2:t1;
}
class locks_status{
public:
  int lock1;
  int lock2;
  int code_ptr;
  // Default constructor
    locks_status() : lock1(0), lock2(0), code_ptr(0) {}

    // Copy constructor
    locks_status(const locks_status& other) : lock1(other.lock1), lock2(other.lock2), code_ptr(other.code_ptr) {}

    // Assignment operator
    locks_status& operator=(const locks_status& other) {
        if (this != &other) { // Check for self-assignment
            lock1 = other.lock1;
            lock2 = other.lock2;
            code_ptr = other.code_ptr;
        }
        return *this;
    }
    // Comparison operators
    bool operator<(const locks_status& other) const {
        if (lock1 != other.lock1)
            return lock1 < other.lock1;
        if (lock2 != other.lock2)
            return lock2 < other.lock2;
        return code_ptr < other.code_ptr;
    }
    bool operator==(const locks_status& other) const {
        return lock1 == other.lock1 && lock2 == other.lock2 && code_ptr == other.code_ptr;
    }
};

static map<locks_status,long long> my_record;

long long get_time(locks_status s, vector<int>* C, int N, int M, int used_time){
  if (s.code_ptr == M){
    return used_time;
  }
  if (my_record.find(s) != my_record.end()){
    return my_record[s];
  }
  //choice 1: rotate lock1
  int t1 = get_single_step_time(s.lock1,(*C)[s.code_ptr],N);
  locks_status next_s1 = s;
  next_s1.lock1=(*C)[s.code_ptr];
  next_s1.code_ptr+=1;
  long long T1 = get_time(next_s1, C, N, M, used_time+t1);
  my_record[next_s1]=T1;
  
  //choice 2: rotate lock2
  int t2 = get_single_step_time(s.lock2,(*C)[s.code_ptr],N);
  locks_status next_s2 = s;
  next_s2.lock2=(*C)[s.code_ptr];
  next_s2.code_ptr+=1;
  long long T2 = get_time(next_s2, C,  N, M, used_time+t2);
  my_record[next_s2]=T2;
  
  return (T1<T2)? T1:T2;
}
long long getMinCodeEntryTime(int N, int M, vector<int> C) {
  locks_status s;
  s.lock1=1;
  s.lock2=1;
  s.code_ptr = 0;
  int used_time = 0;
  int ans = get_time(s,&C, N, M, used_time);
  return ans;
}

int main (){
  int N=10;
  int M=4;
  vector<int> C;
  C.push_back(9);
  C.push_back(4);
  C.push_back(4);
  C.push_back(8);
  long long t = getMinCodeEntryTime(N,M,C);
  printf("time used: %lld\n", t);
}
