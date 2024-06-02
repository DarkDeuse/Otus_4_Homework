#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>


template <typename> struct is_tuple: std::false_type {};

template <typename ...T> struct is_tuple<std::tuple<T...>>: std::true_type {};

template<typename Type> constexpr bool type_is_tuple()
{
  return is_tuple<Type>::value;
}

void print(...)
{
    std::cout << "undefined type";
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print(T value)
{
  size_t size = sizeof(T);
  while(size)
  {
    size--;
    std::cout << ((value >> size*8) & 0xFF);
    if (size) std::cout << ".";
  }
}


template<typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print(const T &value)
{
  std::cout << value;
}

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<typename T::value_type>>::value ||
                        std::is_same<T, std::list<typename T::value_type>>::value, void>::type
print(T container)
{
  std::string split = "";
  for(auto value : container)
  {
    std::cout << split;
    print(char(value));
    split = ".";
  }
}

namespace tpl
{
  template<int index, typename Callback, typename... Args>
  struct iterate_tuple 
  {
    static void next(std::tuple<Args...>& t, Callback callback) 
    {
      iterate_tuple<index - 1, Callback, Args...>::next(t, callback);
      std::cout << ".";
      callback(index, std::get<index>(t));
    }
  };
  template<typename Callback, typename... Args>
  struct iterate_tuple<0, Callback, Args...> 
  {
    static void next(std::tuple<Args...>& t, Callback callback) 
    {
      callback(0, std::get<0>(t));
    }
  };

  template<typename Callback, typename... Args>
  struct iterate_tuple<-1, Callback, Args...>
  {
    static void next(std::tuple<Args...>& t, Callback callback)
    { }
  };
}

template<typename Callback, typename... Args>
void print_tuple(std::tuple<Args...>& t, Callback callback) 
{
  int const t_size = std::tuple_size<std::tuple<Args...>>::value;
  tpl::iterate_tuple<t_size - 1, Callback, Args...>::next(t, callback);
}


struct callback
{
  template<typename T>
  void operator()(int index, T&& t) 
  {                                 
    print(char(t));
  }
};

template<typename T>
typename std::enable_if<type_is_tuple<T>(), void>::type
print(T tuple)
{
   print_tuple(tuple, callback());
}

template<typename... Args>
void print(Args... args)
{

   auto tuple = std::make_tuple(std::forward<Args>(args)...);

   print_tuple(tuple, callback());
}
