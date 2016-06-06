#include <cassert>
#include <set>
#include <algorithm>

#include <boost/bind.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/ptr_container/ptr_set.hpp>

template <class T> struct ptr_cmp: public std::binary_function<T, T, bool> {

  template <class T1> bool operator()(const T1& v1, const T1& v2) const {
    return operator ()(*v1, *v2);
  }

  bool operator()(const T& v1, const T& v2) const {
    return std::less<T>()(v1, v2);
  }
};

void example_1() {
  std::set<int*, ptr_cmp<int> > s;
  s.insert(new int(1));
  s.insert(new int(0));
  s.insert(new int(2));
  s.insert(new int(4));
  s.insert(new int(3));  

  // ...
  assert(**s.begin() == 0);

  // ...
  // Deallocating resources
  // Any exception in this code will lead to
  // memory leak
  std::for_each(s.begin(), s.end(),  boost::bind(::operator delete, _1));
}

void correct_impl() {

  boost::ptr_set<int> s;
  s.insert(new int(1));
  s.insert(new int(0));

  // ...
  assert(*s.begin() == 0);

  // ...
  // resources will be deallocated by container itself
}

int main() {
  example_1();
  
  return 0;
  
}