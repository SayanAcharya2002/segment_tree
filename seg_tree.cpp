#include <iostream>
#include "seg_tree.h"

template<class T>
seg_tree<T>::seg_tree(T* arr,int arr_size,bool laziness,T def_val_lazy):arr(arr),arr_size(arr_size),laziness(laziness),def_val_lazy(def_val_lazy)
{
  if(laziness)
  {
    la_arr=new non_std::pair<T>[4*this->arr_size+1];
    int temp_tot=4*this->arr_size+1;
    for(int i=0;i<temp_tot;++i)
    {
      la_arr[i].second=def_val_lazy;
    }
  }
  seg=new T[4*this->arr_size+1];
  // if(segmenter)
  //   build(0,this->arr_size,1);
}

template<class T>
seg_tree<T>::~seg_tree()
{
  delete[] segmenter;
  delete[] lazy_update;
  delete[] lazy_stack;
  delete[] normal_update;
  delete[] arr;
  delete[] seg;
  delete[] la_arr;
}

template<class T>
void seg_tree<T>::rebuild(T* arr,int arr_size,bool laziness,T def_val_lazy)
{
  this->arr=arr;
  this->arr_size=arr_size;
  this->laziness=laziness;
  this->def_val_lazy=def_val_lazy;
  delete[] seg;
  delete[] la_arr;
  seg=0;
  la_arr=0;
  seg=new T[4*this->arr_size+1];
  if(this->laziness)
  {
    la_arr=new non_std::pair<T>[4*this->arr_size+1];
    int temp_tot=4*this->arr_size+1;
    for(int i=0;i<temp_tot;++i)
    {
      la_arr[i].second=def_val_lazy;
    }
  }
  // if(segmenter)
  //   build(0,this->arr_size,1);
}

template<class T>
T seg_tree<T>::build(int arr_s,int arr_e,int index)const
{
  if(arr_e==-1)
    arr_e=this->arr_size;
  if(arr_s+1==arr_e)
  {
    return seg[index]=arr[arr_s];
  }
  auto arr_mid=(arr_s+arr_e)/2;
  return seg[index]=segmenter->operator()(build(arr_s,arr_mid,2*index),build(arr_mid,arr_e,2*index+1));
}

template<class T>
non_std::pair<T> seg_tree<T>::__search(int search_s,int search_e,int arr_s,int arr_e,int index)const
{
  bool update=0;
  if(arr_e==-1)
    arr_e=this->arr_size;
  if(laziness)
  {
    if(la_arr[index].first)
    {
      update=1;
      seg[index]=lazy_update->operator()(arr+arr_s,arr+arr_e,index,seg[index],la_arr[index].second);
      if(arr_s+1!=arr_e)
      {
        la_arr[2*index].second=lazy_stack->operator()(la_arr[2*index].second,la_arr[index].second);
        la_arr[2*index+1].second=lazy_stack->operator()(la_arr[2*index+1].second,la_arr[index].second);
        la_arr[2*index].first=1;
        la_arr[2*index+1].first=1;
      }
      else
      {
        arr[arr_s]=seg[index];
      }
      la_arr[index].first=0;
      la_arr[index].second=def_val_lazy;
    }
  }
  if(search_s==arr_s && search_e==arr_e)
  {
    return non_std::pair<T>(update,seg[index]);
  }
  else
  {
    auto arr_mid=(arr_s+arr_e)/2;
    if(search_e<=arr_mid)
    {
      auto t1=__search(search_s,search_e,arr_s,arr_mid,2*index);
      if(t1.first)
      {
        seg[index]=segmenter->operator()(seg[2*index],seg[2*index+1]);
      }
      return non_std::pair<T>(update|t1.first,t1.second);
    }
    else if(search_s<arr_mid && search_e<=arr_e)
    {
      auto t1=__search(search_s,arr_mid,arr_s,arr_mid,2*index);
      auto t2=__search(arr_mid,search_e,arr_mid,arr_e,2*index+1);
      if(t1.first|t2.first)
      {
        seg[index]=segmenter->operator()(seg[2*index],seg[2*index+1]);
      }
      return non_std::pair<T>(update|t1.first|t2.first,segmenter->operator()(t1.second,t2.second));
    }
    else
    {
      auto t2=__search(search_s,search_e,arr_mid,arr_e,2*index+1);
      if(t2.first)
      {
        seg[index]=segmenter->operator()(seg[2*index],seg[2*index+1]);
      }
      return non_std::pair<T>(update|t2.first,t2.second);
    }
  }
}
template<class T>
T seg_tree<T>::search(int search_s,int search_e)const
{
  return __search(search_s,search_e).second;
}

// #error did you think clearly?
template<class T>
void seg_tree<T>::update(int up_s,int up_e,const T& update_val,int arr_s,int arr_e,int index)const
{
  if(arr_e==-1)
    arr_e=this->arr_size;
  if(laziness)
  {
    if(up_s==arr_s && up_e==arr_e)
    {
      //std::cout<<up_s<<" "<<up_e<<" "<<arr_s<<" "<<arr_e<<"\n";
      auto temp_val=lazy_stack->operator()(la_arr[index].second,update_val);
      la_arr[index].second=temp_val;
      la_arr[index].first=1;
      // seg[index]=la_arr[]
      // return ;
    //   seg[index]=lazy_update->operator()(arr+arr_s,arr+arr_e,index,seg[index],temp_val);
    //   if(up_s+1!=up_e)
    //   {
    //     la_arr[2*index].second=lazy_stack->operator()(temp_val,la_arr[2*index].second);
    //     la_arr[2*index+1].second=lazy_stack->operator()(temp_val,la_arr[2*index+1].second);
    //     la_arr[2*index].first=1;
    //     la_arr[2*index+1].first=1;
    //   }
    //   //somehow update the arr at the end
    //   else
    //   {
    //     arr[arr_s]=seg[index];
    //   }
    //   return ;
    //   // return seg[index];
    }
    if(la_arr[index].first)
    {
      seg[index]=lazy_update->operator()(arr+arr_s,arr+arr_e,index,seg[index],la_arr[index].second);
      if(arr_s+1!=arr_e)
      {
        la_arr[2*index].second=lazy_stack->operator()(la_arr[2*index].second,la_arr[index].second);
        la_arr[2*index+1].second=lazy_stack->operator()(la_arr[2*index+1].second,la_arr[index].second);
        la_arr[2*index].first=1;
        la_arr[2*index+1].first=1;

      }
      la_arr[index].first=0;
      la_arr[index].second=def_val_lazy;
      if(arr_s+1==arr_e)
      {
        arr[arr_s]=seg[index];
        return;
      }
      if(up_s==arr_s && up_e==arr_e)
      {
        return;
      }
    }
    // if(up_s==arr_s && up_e==arr_e)
    // {
    //   //std::cout<<up_s<<" "<<up_e<<" "<<arr_s<<" "<<arr_e<<"\n";
    //   auto temp_val=lazy_stack->operator()(la_arr[index].second,update_val);
    //   // la_arr[index].second=temp_val;
    //   // la_arr[index].first=1;
    //   seg[index]=lazy_update->operator()(arr+arr_s,arr+arr_e,index,seg[index],temp_val);
    //   if(up_s+1!=up_e)
    //   {
    //     la_arr[2*index].second=lazy_stack->operator()(temp_val,la_arr[2*index].second);
    //     la_arr[2*index+1].second=lazy_stack->operator()(temp_val,la_arr[2*index+1].second);
    //     la_arr[2*index].first=1;
    //     la_arr[2*index+1].first=1;
    //   }
    //   //somehow update the arr at the end
    //   else
    //   {
    //     arr[arr_s]=seg[index];
    //   }
    //   return ;
    //   // return seg[index];
    // }
  }
  // else
  // {
    if(arr_s+1==arr_e)
    {
      seg[index]=normal_update->operator()(seg[index],update_val);
      arr[arr_s]=seg[index];
      return;
    }
    auto arr_mid=(arr_s+arr_e)/2;
    if(up_e<=arr_mid)
    {
       update(up_s,up_e,update_val,arr_s,arr_mid,2*index);
    }
    else if(up_s<arr_mid && up_e<=arr_e)
    {
      update(up_s,arr_mid,update_val,arr_s,arr_mid,2*index);
      update(arr_mid,up_e,update_val,arr_mid,arr_e,2*index+1);
    }
    else
    {
      update(up_s,up_e,update_val,arr_mid,arr_e,2*index+1);
    }
    seg[index]=segmenter->operator()(seg[2*index],seg[2*index+1]);
  // }
}

template<class T>
bool seg_tree<T>::is_lazy()const
{
  return laziness;
}

template<class T>
void seg_tree<T>::toggle_lazy(const T& def_val_lazy)
{
  if(laziness)
  {
    clear_lazy(0,arr_size,1);
    laziness=0;
  }
  else
  {
    laziness=1;
    delete[] la_arr;
    la_arr=new non_std::pair<T>[4*arr_size+1];
    int temp_tot=4*this->arr_size+1;
    for(int i=0;i<temp_tot;++i)
    {
      la_arr[i].second=def_val_lazy;
    }
  }
}
template<class T>
bool seg_tree<T>::clear_lazy(int arr_s,int arr_e,int index)
{
  bool update=0;
  if(la_arr[index].first)
  {
    update=1;
    seg[index]=lazy_update->operator()(arr+arr_s,arr+arr_e,index,seg[index],la_arr[index].second);
    if(arr_s+1!=arr_e)
    {
      la_arr[2*index].second=lazy_stack->operator()(la_arr[2*index].second,la_arr[index].second);
      la_arr[2*index+1].second=lazy_stack->operator()(la_arr[2*index+1].second,la_arr[index].second);
      la_arr[2*index].first=1;
      la_arr[2*index+1].first=1;
    }
    else
    {
      arr[arr_s]=seg[index];
    }
    la_arr[index].first=0;
    la_arr[index].second=def_val_lazy;
  }
  if(arr_s+1==arr_e)
    return update;
  auto arr_mid=(arr_s+arr_e)/2;
  auto b1=clear_lazy(arr_s,arr_mid,2*index);
  auto b2=clear_lazy(arr_mid,arr_e,2*index+1);
  if(b1|b2)
    seg[index]=segmenter->operator()(seg[2*index],seg[2*index+1]);
  return update|b1|b2;
}

template<class T>
void seg_tree<T>::set_def_val_lazy(const T& def_val_lazy)const
{
  this->def_val_lazy=def_val_lazy;
  int temp_tot=4*this->arr_size+1;
  for(int i=0;i<temp_tot;++i)
  {
    la_arr[i].second=def_val_lazy;
  }
}
template<class T>template<class S>
void seg_tree<T>::set_segmenter_class()
{
  delete[] segmenter;
  segmenter=new S();
}
template<class T>template<class S>
void seg_tree<T>::set_lazy_update_class()
{
  delete[] lazy_update;
  lazy_update=new S();
}
template<class T>template<class S>
void seg_tree<T>::set_lazy_stack_class()
{
  delete[] lazy_stack;
  lazy_stack=new S();
}
template<class T>template<class S>
void seg_tree<T>::set_normal_update_class()
{
  delete[] normal_update;
  normal_update=new S();
}

template<class T>
bool seg_tree<T>::is_set_segmenter_class()const
{
  return (segmenter!=nullptr);
}
template<class T>
bool seg_tree<T>::is_set_lazy_update_class()const
{
  return (lazy_update!=nullptr);
}
template<class T>
bool seg_tree<T>::is_set_lazy_stack_class()const
{
  return (lazy_stack!=nullptr);
}
template<class T>
bool seg_tree<T>::is_set_normal_update_class()const
{
  return (normal_update!=nullptr);
}

template<class T>
bool seg_tree<T>::all_set()const
{
  if(!laziness)
  {
    return !((!segmenter)|(!normal_update));
  }
  else{
    return !((!segmenter)|(!normal_update)|(!lazy_update)|(!lazy_stack));
  }
}

