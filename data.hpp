#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
// #include <fstream>
// #include <sstream>
// #include <iostream>
// #include "stringsplit.hpp"
// #include "calculate.hpp"
// #include <string>
#include <list>
// #include <algorithm>

class data
{
public:
  data(const std::string& csvfilename);
  void writefile(const std::string& infilename);
private:
  void readcsvfile(const std::string &s );
  std::list<unsigned> lstcols();
  void readinifile(const std::string &s);
  bool verifyColumnNumbers();
  void calculate();
  char determineDelimiter(const std::string& singleline);
  std::vector<std::string> m_linebyline;
  std::vector<std::vector< std::string> > m_dat;
  std::string m_header;
  std::vector<std::string> m_headersplit;
  std::vector<std::string> m_whichcols; // columns of which p95 will be calculated
  bool CompareElementsInTwoStrings(std::string s1, std::string s2);
  char m_delimiter;
};

#endif
