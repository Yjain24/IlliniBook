#include "illini_book.hpp"

#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include "utilities.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream ifs_person{people_fpath};
  std::ifstream ifs_relation{relations_fpath};

  std::string line;
  while (std::getline(ifs_person, line)) {
    int person_id = std::stoi(line);
    impmap_.emplace(person_id, std::list<std::pair<int, std::string>>{});
    line = "";
  }
  while (std::getline(ifs_relation, line)) {
    std::vector<std::string> each_line = utilities::Split(line, ',');
    int p1 = std::stoi(each_line.at(0));
    int p2 = std::stoi(each_line.at(1));
    std::string re = each_line.at(2);
    impmap_.find(p1)->second.emplace_back(p2, re);
    impmap_.find(p2)->second.emplace_back(p1, re);
    impset_.insert(re);
    line = "";
  }
}


IlliniBook::~IlliniBook() {
  std::map<int, std::list<std::pair<int, std::string>>> map;
  map = std::map<int, std::list<std::pair<int, std::string>>>();
  std::set<std::string> set;
  set = std::set<std::string>();
};

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  std::queue<int> queue;
  std::set<int> set;
  queue.push(uin_1);
  set.insert(uin_1);
  for (std::queue<int>::size_type i = 0; i < queue.size(); i++) {
    int curr = queue.front();
    queue.pop();
    std::list<std::pair<int, std::string>> list = impmap_.find(curr)->second;
    auto it = list.begin();
    while (it != list.end()) {
      auto const& element = *it;
      if (element.first == uin_2) {
        return true;
      } 
      if (set.find(element.first) == set.end()) {
        queue.push(element.first);
        set.insert(element.first);
      }
      ++it;
    }
  }
  return false;
}
 



bool IlliniBook::RelationshipExists(const std::string& relationship) const {
  return impset_.find(relationship) != impset_.end();
}
std::list<std::pair<int, std::string>> IlliniBook::GetNeighborsWithRelationship(int uin, const std::string& relationship) const {
  std::list<std::pair<int, std::string>> neighbors;
  if (impmap_.find(uin) != impmap_.end()) {
    for (auto const& neighbor : impmap_.find(uin)->second) {
      if (neighbor.second == relationship) {
        neighbors.push_back(neighbor);
      }
    }
  }
  return neighbors;
}
bool IlliniBook::BfsHasRelationship(int uin_1, int uin_2, const std::string& relationship) const {
  std::queue<int> queue;
  std::set<int> visited;
  queue.push(uin_1);
  visited.insert(uin_1);
  while (!queue.empty()) {
    int curr = queue.front();
    queue.pop();

    auto neighbors = GetNeighborsWithRelationship(curr, relationship);
    for (auto const& neighbor : neighbors) {
      if (visited.find(neighbor.first) == visited.end()) {
        if (neighbor.first == uin_2) return true;
        queue.push(neighbor.first);
        visited.insert(neighbor.first);
      }
    }
  }

  return false;
}
bool IlliniBook::AreRelated(int uin_1, int uin_2, const std::string& relationship) const {
  if (!RelationshipExists(relationship)) return false;
  return BfsHasRelationship(uin_1, uin_2, relationship);
}


int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  std::queue<int> queue;
  std::set<int> set;
  std::map<int, int> num;
  InitializeNum(num); 
  queue.push(uin_1);
  set.insert(uin_1);

  while (!queue.empty()) {
    int curr = queue.front();
    queue.pop();
    std::list<std::pair<int, std::string>> list = impmap_.find(curr)->second;
    for (auto const& element : list) {
      if (set.find(element.first) == set.end()) {
        UpdateNum(num, curr, element.first); 
        queue.push(element.first);
        set.insert(element.first);
        if (element.first == uin_2) return num.find(uin_2)->second;
      }
    }
  }

  return -1;
}

void IlliniBook::InitializeNum(std::map<int, int>& num) const {
  for (auto const& item : impmap_) {
    num.insert(std::pair<int, int>(item.first, 0));
  }
}

void IlliniBook::UpdateNum(std::map<int, int>& num, int curr, int next) const {
  num.find(next)->second = num.find(curr)->second + 1;
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  if (impset_.find(relationship) == impset_.end()) return -1;
  std::queue<int> queue;
  std::set<int> set;
  std::map<int, int> num;
  InitializeNum(num);  
  queue.push(uin_1);
  set.insert(uin_1);

  while (!queue.empty()) {
    int curr = queue.front();
    queue.pop();
    std::list<std::pair<int, std::string>> list = impmap_.find(curr)->second;
    for (auto const& element : list) {
      if (IsRelated(element, relationship) && IsUnvisited(element, set)) {
        UpdateNum(num, curr, element.first);  
        AddToQueue(element.first, queue, set);      
        if (IsTargetUser(element, uin_2)) return GetNum(num, uin_2);  
      }
    }
  }

  return -1;
}

void IlliniBook::InitializeNu(std::map<int, int>& num) const {
  for (auto const& item : impmap_) {
    num.insert(std::pair<int, int>(item.first, 0));
  }
}

bool IlliniBook::IsRelated(const std::pair<int, std::string>& p, const std::string& relationship) const {
  return p.second == relationship;
}

bool IlliniBook::IsUnvisited(const std::pair<int, std::string>& p, const std::set<int>& s) const {
  return s.find(p.first) == s.end();
}

void IlliniBook::UpdatNum(std::map<int, int>& num, int curr, int next) const {
  num.find(next)->second = num.find(curr)->second + 1;
}

void IlliniBook::AddToQueue(int uin, std::queue<int>& queue, std::set<int>& set) const {
  queue.push(uin);
  set.insert(uin);
}

bool IlliniBook::IsTargetUser(const std::pair<int, std::string>& p, int uin) const {
  return p.first == uin;
}

int IlliniBook::GetNum(const std::map<int, int>& num, int uin) const {
  return num.find(uin)->second;
}


void IlliniBook::InitializeDistanceMap(std::map<int, int>& num,
                           const std::map<int, std::list<std::pair<int, std::string>>>& adj) const{
  for (auto const& item : adj) {
    num.insert(std::make_pair(item.first, 0));
  }
}
bool IlliniBook::VisitNode(int curr, int next, std::set<int>& visited, std::map<int, int>& num) const {
  if (visited.find(next) == visited.end()) {
    num[next] = num[curr] + 1;
    visited.insert(next);
    return true;
  }
  return false;
}

std::vector<int> IlliniBook::BFS(int start, int n, const std::map<int, std::list<std::pair<int, std::string>>>& adj) const {
  std::vector<int> step;
  std::queue<int> queue;
  std::set<int> visited;
  std::map<int, int> num;
  InitializeDistanceMap(num, adj);
  queue.push(start);
  visited.insert(start);

  while (!queue.empty()) {
    int curr = queue.front();
    queue.pop();
    for (auto const& [next, label] : adj.at(curr)) {
      VisitNode(curr, next, visited, num) ? (num[next] == n ? step.push_back(next) : num[next] < n ? queue.push(next) : void()) : void();
    }
  }
  return step;
}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  return BFS(uin, n, impmap_);
}


// Checks if an element is in the set
bool IlliniBook::IsElementInSet(int element, const std::set<int>& set) const {
  return (set.find(element) != set.end());
}

// Performs a breadth-first search starting from a given element
void IlliniBook::BFS(int start, std::set<int>& set, const std::map<int, std::list<std::pair<int, std::string>>>& impmap_) const {
  std::queue<int> queue;
  queue.push(start);
  set.insert(start);

  while (!queue.empty()) {
    int curr = queue.front();
    queue.pop();
    std::list<std::pair<int, std::string>> list = impmap_.find(curr)->second;
    for (auto const& element : list) {
      if (!IsElementInSet(element.first, set)) {
        queue.push(element.first);
        set.insert(element.first);
      }
    }
  }
}

size_t IlliniBook::CountGroupsHelper(const std::map<int, std::list<std::pair<int, std::string>>>& impmap_) const {
  size_t count = 0;
  std::set<int> set;

  for (auto const& element : impmap_) {
    if (!IsElementInSet(element.first, set)) {
      BFS(element.first, set, impmap_);
      count++;
    }
  }

  return count;
}


size_t IlliniBook::CountGroups() const {
  return CountGroupsHelper(impmap_);
}







bool IlliniBook::IsElement(int element, const std::set<int>& set) const {
  return (set.find(element) != set.end());
}


void IlliniBook::BFS(int start, std::set<int>& set, const std::map<int, std::list<std::pair<int, std::string>>>& impmap_, const std::string& relationship) const {
  std::queue<int> queue;
  queue.push(start);
  set.insert(start);

  while (!queue.empty()) {
    int curr = queue.front();
    queue.pop();
    std::list<std::pair<int, std::string>> list = impmap_.find(curr)->second;
    for (auto const& element : list) {
      if (!IsElementInSet(element.first, set) && element.second == relationship) {
        queue.push(element.first);
        set.insert(element.first);
      }
    }
  }
}

size_t IlliniBook::CountGroupsHelper(const std::map<int, std::list<std::pair<int, std::string>>>& impmap_, const std::string& relationship) const {
  if (impmap_.empty()) return 0;

  if (impmap_.begin()->second.empty() || impmap_.begin()->second.front().second != relationship) {
    return 1;
  }

  size_t count = 0;
  std::set<int> set;

  for (auto const& element : impmap_) {
    if (!IsElementInSet(element.first, set)) {
      BFS(element.first, set, impmap_, relationship);
      count++;
    }
  }

  return count;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  if (impset_.find(relationship) == impset_.end()) {
    return impmap_.size();
  }
  return CountGroupsHelper(impmap_, relationship);
}



bool IlliniBook::HasRelationship(const std::string& relationship) const {
  return impset_.find(relationship) != impset_.end() ? true : false;
}

bool IlliniBook::IsVisited(int id, const std::set<int>& visited) const {
  return visited.find(id) != visited.end() ? true : false;
}

void IlliniBook::AddToVisited(int id, std::set<int>& visited) const {
  visited.insert(id);
}

std::vector<std::string> IlliniBook::GetRelationshipsToCheck(
    const std::vector<std::string>& relationships) const {
  std::vector<std::string> result;
  if (relationships.empty()) {
    for (const auto& r : impset_) {
      result.push_back(r);
    }
  } else {
    for (const auto& r : relationships) {
      HasRelationship(r) ? result.push_back(r) : void();
    }
  }
  return result;
}

size_t IlliniBook::CountGroups(const std::vector<std::string>& relationships) const {
  size_t count = 0;
  std::set<int> visited;
  std::vector<std::string> rels = GetRelationshipsToCheck(relationships);

  for (auto const& person : impmap_) {
    if (!IsVisited(person.first, visited)) {
      std::queue<int> queue;
      queue.push(person.first);
      AddToVisited(person.first, visited);

      while (!queue.empty()) {
        int curr = queue.front();
        queue.pop();
        std::list<std::pair<int, std::string>> friends =
            impmap_.find(curr)->second;

        for (const auto& friend_pair : friends) {
          int friend_id = friend_pair.first;
          const std::string& relationship = friend_pair.second;

          if (!IsVisited(friend_id, visited)) {
            for (const auto& r : rels) {
              relationship == r ? (queue.push(friend_id), AddToVisited(friend_id, visited)) : void();
            }
          }
        }
      }
      count++;
    }
  }

  return count;
}


