
#include "../inc/print.h"



int main()
{

  //Печать адреса как char
  std::cout << "char:\t";
  print(char(-1));
  std::cout << std::endl;
  
  //Печать адреса как short
  std::cout << "short:\t";
  print(short(0));
  std::cout << std::endl;
  
  //Печать адреса как int
  std::cout << "int:\t";
  print(int(2130706433));
  std::cout << std::endl;
  
  //Печать адреса как long
  std::cout << "long:\t";
  print(long(8875824491850138409));
  std::cout << std::endl;
  
  //Печать адреса как std::string
  std::cout << "string:\t";
  print(std::string{"Hello world!"});
  std::cout << std::endl;
  
  //Печать адреса как std::vector
  std::cout << "vector:\t";
  std::vector<int> v{int(2130706433), int(2130706433), int(2130706433)};
  print(v);
  std::cout << std::endl;
  
  //Печать адреса как std::list
  std::cout << "list:\t";
  std::list<int> l{int(2130706433), int(2130706433), int(2130706433)};
  print(l);
  std::cout << std::endl;
  
  //Опционально. Печать адреса как std::tuple
  print(std::make_tuple(char(-1), short(0), int(2130706433), long(8875824491850138409)));
  std::cout << std::endl;
  print(char(-1), 42, 100000);
  std::cout << std::endl;
    
    
  // // float
  // print(1.2345);
  // std::cout << std::endl;

  return 0;
}

