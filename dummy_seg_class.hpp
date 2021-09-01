#ifndef DUMMY_SEG_CLASS_HPP
#define DUMMY_SEG_CLASS_HPP

//these are the 4 flag holder classes
//inherit them and implement the pure virtual operator () s to design the working
//algorithm of the seg_tree

template<class T>
class segmenter_class{
public:
  virtual T operator()(const T& a,const T& b)const=0;
};
template<class T>
class lazy_update_class
{
public:
  virtual T operator()(T* const& arr_s,T* const& arr_e,const int& index,const T& cur_val,const T& update_val)const=0;
};
template<class T>
class lazy_stack_class
{
public:
  virtual T operator()(const T& a,const T& b)const=0;
};
template<class T>
class normal_update_class
{
public:
  virtual T operator()(const T& a,const T& b)const=0;
};
// flag holder classes end

//ready_made classes start

//segmenter min
template<class T>
class segmenter_min:public segmenter_class<T>
{
public:
  T operator()(const T& a,const T& b)const
  {
    return std::min(a,b);
    // return (a<b)?a:b;
  }
};

//segmenter max
template<class T>
struct segmenter_max: segmenter_class<T>{
  T operator()(const T& a,const T& b)const
  {
    return std::max(a,b);
    // return (a>b)?a:b;
  }
};

//lazy_updater_add
template<class T>
class lazy_update_add:public lazy_update_class<T>
{
public:
  T operator()(T* const & arr_s,T* const& arr_e,const int& index,const T& cur_val,const T& update_val)const
  {
    return cur_val+update_val;
  }
};

//lazy_updater_multiply
template<class T>
class lazy_update_multiply:public lazy_update_class<T>
{
public:
  T operator()(T* const & arr_s,T* const& arr_e,const int& index,const T& cur_val,const T& update_val)const
  {
    return cur_val*update_val;
  }
};

//lazy_stack_add
template<class T>
class lazy_stack_add:public lazy_stack_class<T>
{
public:
  T operator()(const T& a,const T& b)const
  {
    return a+b;
  }
};

//lazy_stack_multiply
template<class T>
class lazy_stack_multiply:public lazy_stack_class<T>
{
public:
  T operator()(const T& a,const T& b)const
  {
    return a*b;
  }
};

//normal_update_add
template<class T>
class normal_update_add:public normal_update_class<T>
{
public:
  T operator()(const T& a,const T& b)const
  {
    return a+b;
  }
};

//normal_update_multiply
template<class T>
class normal_update_multiply:public normal_update_class<T>
{
public:
  T operator()(const T& a,const T& b)const
  {
    return a*b;
  }
};












#endif // DUMMY_SEG_CLASS_HPP