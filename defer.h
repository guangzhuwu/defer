#ifndef __defer_h
#define __defer_h

namespace defer_detail {
  template<class F>
  struct defer_impl {
    defer_impl(defer_impl&& o):func_{std::move(o.func_)}{
      o.moved_=true;
    }
    defer_impl(F&& func):func_{func}{
    }
    ~defer_impl(){
      if(!moved_)
        func_();
    }
    
    defer_impl(const defer_impl&)=delete;
    void operator=(const defer_impl&)=delete;
    void operator=(defer_impl&&)=delete;
  private:
    F func_;
    mutable bool moved_{false};
  };
  
  struct defer_factory {
    template<class F>
    defer_impl<F> operator += (F&& func){
      return defer_impl<F>(std::move(func));
    }
  };
}


#define __DEFER_CAT(a,b) a##b
#define DEFER_CAT(a,b) __DEFER_CAT(a,b)
#ifndef _MSC_VER
# define defer auto DEFER_CAT(__defer_impl,__LINE__) = defer_detail::defer_factory()+=
#else
# define defer auto DEFER_CAT(__defer_impl,__COUNTER__) = defer_detail::defer_factory() +=
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
