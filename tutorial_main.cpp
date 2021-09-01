#include <bits/stdc++.h>
#include "seg_tree.h"
// #include "seg_tree.cpp"
using namespace std;



void show(int* arr,int n)
{
  for(int i=0;i<n;++i)
  {
    cout<<arr[i]<<" ";
  }
  cout<<"\n";
}




int main()
{
  
  srand(time(0));
  int n=10;
  int* arr=new int[n];
  for(int i=0;i<n;++i)
  {
    arr[i]=rand()%100;
  }
  show(arr,n);

  seg_tree<int>s(arr,n);
  s.set_segmenter_class<segmenter_min<int>>();
  s.set_normal_update_class<normal_update_add<int>>();
  s.set_lazy_stack_class<lazy_stack_add<int>>();
  s.set_lazy_update_class<lazy_update_add<int>>();
  s.build();
  s.toggle_lazy();//toggles the laziness
  cout<<s.is_lazy()<<endl;
  s.update(4,n,100);
  show(arr,n);
  s.update(0,n/2,200);
  show(arr,n);
  auto val=s.search(0,n/2);
  cout<<val<<"\n";
  val=s.search(0,n);
  cout<<val<<"\n";
  s.toggle_lazy();
  show(arr,n);

  return 0;
}