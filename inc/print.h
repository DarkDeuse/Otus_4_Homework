#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <tuple>


/**
 * Проверка на std::tuple.
 */
template <typename> struct is_tuple: std::false_type {};

template <typename ...T> struct is_tuple<std::tuple<T...>>: std::true_type {};

template<typename Type> constexpr bool type_is_tuple()
{
  return is_tuple<Type>::value;
}

/**
* print() для неопределенных типов
*/
void print(...)
{
    std::cout << "undefined type";
}

/**
* Специализация print() для целочисленных типов
*/
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

/**
* Специализация print() для std::string
*/
template<typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type
print(const T &value)
{
  std::cout << value;
}

/**
* Специализация print() для контейнеров
*/
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
/**
 * Главная роль здесь у шаблона класса iterate_tuple.
    
 * Первый параметр шаблона класса iterate_tuple имеет тип int (index).
 * Значение этого параметра используется функцией get, 
 * которая "достает" из кортежа элемент по указанной позиции.
    
 * Мы рекурсивно сдвигаем позицию (уменьшаем index на 1) и таким образом
 * перемещаемся по кортежу.
    
 * Когда значение индекса становится равно 0, рекурсия завершается,
 * благодаря частичной специализации для индекса равного 0.
    
 * При этом есть особый случай, когда индекс равен -1. Он соответствует 
 * ситуации, когда кортеж не содержит ни одного элемента.
 */   
  template<int index, typename Callback, typename... Args>
  struct iterate_tuple 
  {
    static void next(std::tuple<Args...>& t, Callback callback) 
    {
      // Уменьшаем позицию и рекурсивно вызываем этот же метод 
      iterate_tuple<index - 1, Callback, Args...>::next(t, callback);
      std::cout << ".";
      // Вызываем обработчик и передаем ему позицию и значение элемента
      callback(index, std::get<index>(t));
    }
  };
    
  /**
  * Частичная специализация для индекса 0 (завершает рекурсию)
  */
  template<typename Callback, typename... Args>
  struct iterate_tuple<0, Callback, Args...> 
  {
    static void next(std::tuple<Args...>& t, Callback callback) 
    {
      callback(0, std::get<0>(t));
    }
  };

  /**
   * Частичная специализация для индекса -1 (пустой кортеж)
   */
  template<typename Callback, typename... Args>
  struct iterate_tuple<-1, Callback, Args...>
  {
    static void next(std::tuple<Args...>& t, Callback callback)
    {
      // ничего не делаем
    }
  };
}

/**
* print_tuple для обхода элементов кортежа (compile time!):
*/
template<typename Callback, typename... Args>
void print_tuple(std::tuple<Args...>& t, Callback callback) 
{
  // Размер кортежа
  int const t_size = std::tuple_size<std::tuple<Args...>>::value;
    
  // Запускаем рекурсивный обход элементов кортежа во время компиляции
  tpl::iterate_tuple<t_size - 1, Callback, Args...>::next(t, callback);
}


/**
* Вызывается для печати элементов кортежа
*/
struct callback
{
  template<typename T>
  void operator()(int index, T&& t) // index - это позиция элемента в кортеже
  {                                 // t - значение элемента
    print(char(t));
  }
};

/**
* Специализация print() для tuple
*/
template<typename T>
typename std::enable_if<type_is_tuple<T>(), void>::type
print(T tuple)
{
   // Обход элементов кортежа и вызвов обработчика 
   print_tuple(tuple, callback());
}

/**
* Специализация print() для Args... args
*/
template<typename... Args>
void print(Args... args)
{
   // Значения аргументов функции внутри кортежа 
   auto tuple = std::make_tuple(std::forward<Args>(args)...);
   
   // Обход элементов кортежа и вызвов обработчика 
   print_tuple(tuple, callback());
}
