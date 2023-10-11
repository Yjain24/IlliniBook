#include "illini_book.hpp"
#include <iostream>
int main() {
  IlliniBook ib("./example/persons.csv", "./example/relations.csv");
  // std::cout << "set IlliniBook successfully" << std::endl;
  // std::cout << ib.AreRelated(1, 2) << std::endl;         // true
  // std::cout << ib.AreRelated(3, 2) << std::endl;         // true
  // std::cout << ib.AreRelated(1, 9) << std::endl;         // false
  // std::cout << ib.AreRelated(1, 2, "128") << std::endl;  // true
  // std::cout << ib.AreRelated(1, 2, "124") << std::endl;  // false
  // std::cout << ib.AreRelated(1, 6, "128") << std::endl;  // true
  // std::cout << ib.AreRelated(1, 6, "124") << std::endl;  // true
  // std::cout << ib.GetRelated(1, 2) << std::endl;         // 1
  // std::cout << ib.GetRelated(3, 2) << std::endl;         // 2
  // std::cout << ib.GetRelated(1, 9) << std::endl;         //-1
  // std::cout << ib.GetRelated(1, 2, "128") << std::endl;  // 1
  // std::cout << ib.GetRelated(1, 2, "124") << std::endl;  //-1
  // std::cout << ib.GetRelated(1, 6, "128") << std::endl;  // 2
  // std::cout << ib.GetRelated(1, 6, "124") << std::endl;  // 1
  // std::cout << ib.CountGroups() << std::endl;
  // std::cout << ib.CountGroups("128") << std::endl;
  // std::cout << ib.CountGroups("124") << std::endl;
  // std::cout << ib.CountGroups("173") << std::endl;
  // std::cout << ib.CountGroups(std::vector<std::string>{ "124", "173"}) << std::endl;
  // std::cout << ib.CountGroups(std::vector<std::string>{ "124", "173", "128"}) << std::endl;

  std::vector<int> op = ib.GetSteps(1, 1);
  // for (const auto& element: op) std::cout << element << std::endl;
  // op = ib.GetSteps(1, 2);
  // for (const auto& element: op) std::cout << element << std::endl;
  // op = ib.GetSteps(1, 3);
  // for (const auto& element: op) std::cout << element << std::endl;
  // op = ib.GetSteps(9, 1);
  // for (const auto& element: op) std::cout << element << std::endl;
}
