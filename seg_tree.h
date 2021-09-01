#ifndef SEG_TREE_H
#define SEG_TREE_H


namespace non_std{
template<class T>
struct pair
{
  bool first=0;
  T second=T();
  pair()
  {

  }
  pair(const bool& b,const T& t):first(b),second(t)
  {

  }
  pair(const pair<T>& p):first(p.first),second(p.second)
  {

  }
  pair& operator=(const pair<T>& p)
  {
    this.first=p.first;
    this.second=p.second;
    return *this;
  }
};
};
// template<class T>
// class segmenter_min
// {
//   operator()(const T& a,const T& b)const
//   {
//     return 
//   }
// };
//updater(T* start,T* end,int index,T cur_val,T update_val)

#include "dummy_seg_class.hpp"


template<class T>
class seg_tree{
private:
  //place some static asserts to make sure that the () is const otherwise wont work 
  // or make the segmenter and lazy mutable
  segmenter_class<T>* segmenter=0;
  lazy_update_class<T>* lazy_update=0;
  lazy_stack_class<T>* lazy_stack=0;
  normal_update_class<T>* normal_update=0;
  T* arr=0,*seg=0;
  non_std::pair<T>*la_arr=0;
  int arr_size=0;
  bool laziness=0;
  bool clear_lazy(int arr_s,int arr_e,int index);
  T def_val_lazy=T();
  non_std::pair<T> __search(int search_s,int search_e,int arr_s=0,int arr_e=-1,int index=1)const;
public:
  seg_tree(T* arr,int arr_size,bool laziness=0,T def_val_lazy=T());
  ~seg_tree();
  void rebuild(T* arr,int arr_size,bool laziness=0,T def_val_lazy=T());
  T build(int arr_s=0,int arr_e=-1,int index=1)const;
  //if problem arises delete the const modifier
  bool all_set()const;
  T search(int search_s,int search_e)const ;
  void update(int up_s,int up_e,const T& update_val,int arr_s=0,int arr_e=-1,int index=1)const;
  bool is_lazy()const;
  void toggle_lazy(const T& def_val_lazy=T());
  void set_def_val_lazy(const T& def_val_lazy)const;
  
  template<class S>
  void set_segmenter_class();

  template<class S>
  void set_lazy_update_class();

  template<class S>
  void set_lazy_stack_class();

  template<class S>
  void set_normal_update_class();

  bool is_set_segmenter_class()const;
  bool is_set_lazy_update_class()const;
  bool is_set_lazy_stack_class()const;
  bool is_set_normal_update_class()const;
};

#include "seg_tree.cpp"
#endif //SEG_TREE_H