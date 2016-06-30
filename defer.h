//
// defer.h
// ~~~~~~~
//
// GuangZhu Wu (GuangZhuWu@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef __defer_h
#define __defer_h

#include <utility> //std::move

namespace defer_detail {
  template<class F>
  struct defer_impl {
    defer_impl(defer_impl&& o):func_{std::forward<F>(o.func_)}{
      o.moved_=true;
    }
    defer_impl(F&& func):func_{std::forward<F>(func)}{
    }
    ~defer_impl(){
      if(!moved_) func_();
    }
    void operator=(const defer_impl&) = delete;
    void operator=(defer_impl&&) = delete;
  private:
    F func_;
    bool moved_{false};
  };
  
  static struct defer_factory {
    template<class F>
     typename std::enable_if_t<std::is_constructible<std::function<void()>,F>::value,defer_impl<F>> operator + (F&& func){
      return defer_impl<F>(std::forward<F>(func));
    }
  }defer_factory;
}

#define __DEFER_CAT(a,b) a##b
#define DEFER_CAT(a,b) __DEFER_CAT(a,b)
#ifndef _MSC_VER
# define defer auto DEFER_CAT(__defer_impl,__LINE__) = defer_detail::defer_factory+
#else
# define defer auto DEFER_CAT(__defer_impl,__COUNTER__) = defer_detail::defer_factory+
#endif

/*
 void test()
 {
    const size_t buf_len;
    char* p=new char[buf_len];
    defer [=](){delete[] p;};
    memset(p,0,buf_len);
 }
*/

#endif//__defer_h
