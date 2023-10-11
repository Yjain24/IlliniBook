#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <utility>

class IlliniBook {
public:
  IlliniBook(const std::string &people_fpath, const std::string &relations_fpath);
  IlliniBook(const IlliniBook &rhs) = delete;
  IlliniBook &operator=(const IlliniBook &rhs) = delete;
  ~IlliniBook();
  bool AreRelated(int uin_1, int uin_2) const;
  bool AreRelated(int uin_1, int uin_2, const std::string &relationship) const;
  int GetRelated(int uin_1, int uin_2) const;
  int GetRelated(int uin_1, int uin_2, const std::string &relationship) const;
  std::vector<int> GetSteps(int uin, int n) const;
  size_t CountGroups() const;
  size_t CountGroups(const std::string &relationship) const;
  size_t CountGroups(const std::vector<std::string> &relationships) const;
//   std::map<std::pair<int, int>, std::string> graph_;
//   std::vector<int> uins_;
  bool RelationshipExists(const std::string& relationship) const;
  std::list<std::pair<int, std::string>> GetNeighborsWithRelationship(int uin, const std::string& relationship) const;
  bool BfsHasRelationship(int uin_1, int uin_2, const std::string& relationship) const;
  void InitializeNum(std::map<int, int>& num) const;
  void UpdateNum(std::map<int, int>& num, int curr, int next) const;
  
  void InitializeNu(std::map<int, int>& num) const;

  bool IsRelated(const std::pair<int, std::string>& p, const std::string& relationship) const;

  bool IsUnvisited(const std::pair<int, std::string>& p, const std::set<int>& s) const;

  void UpdatNum(std::map<int, int>& num, int curr, int next) const;

  void AddToQueue(int uin, std::queue<int>& queue, std::set<int>& set) const;

  bool IsTargetUser(const std::pair<int, std::string>& p, int uin) const;

  int GetNum(const std::map<int, int>& num, int uin) const; 
  
  void InitializeDistanceMap(std::map<int, int>& num,
                           const std::map<int, std::list<std::pair<int, std::string>>>& adj) const;
  bool VisitNode(int curr, int next, std::set<int>& visited, std::map<int, int>& num) const;

  std::vector<int> BFS(int start, int n, const std::map<int, std::list<std::pair<int, std::string>>>& adj) const;      

  bool IsElementInSet(int element, const std::set<int>& set) const;
  void BFS(int start, std::set<int>& set, const std::map<int, std::list<std::pair<int, std::string>>>& impmap) const;
  size_t CountGroupsHelper(const std::map<int, std::list<std::pair<int, std::string>>>& impmap) const;
  bool IsElement(int element, const std::set<int>& set) const;
  void BFS(int start, std::set<int>& set, const std::map<int, std::list<std::pair<int, std::string>>>& impmap, const std::string& relationship) const;
  size_t CountGroupsHelper(const std::map<int, std::list<std::pair<int, std::string>>>& impmap, const std::string& relationship) const;
  bool HasRelationship(const std::string& relationship) const;
  bool IsVisited(int id, const std::set<int>& visited) const;
  void AddToVisited(int id, std::set<int>& visited) const;
  std::vector<std::string> GetRelationshipsToCheck(
    const std::vector<std::string>& relationships) const;
  private:
  std::map<int, std::list<std::pair<int, std::string>>> impmap_;
  std::set<std::string> impset_;
};


#endif
