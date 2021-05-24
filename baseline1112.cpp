/*
  BaseLine.cpp
  17 augustus 2018
  Henry Kelderman
  read csv file in vector of vector of strings.
  convert one specific vector (col) to float/double
  do calculations on that column
  and add extra column with baseline data.
*/

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream> // needed for std::istringstream
#include <algorithm> // std::sort
#include "stringsplit.hpp"
#include "data.hpp"
// #define DELIMITER ','
#define DELIMITERS ";,"

void printUsageMessage();

#define MAIN 1
#ifdef MAIN
int main(int argc, char* argv[])
{
  if (argc == 1)
    {
      printUsageMessage();
      return 0;
    }
  else
    {
      for (int i = 1; i <= argc; ++i)
	{
	  std::cout << argv[i] << '\n';
	  data D((std::string)argv[i]);
	  D.writefile((std::string)argv[i]);
	  std::cout << std::endl;
	}
    }
  return 0;
}

void printUsageMessage()
{
  std::cout << "Determines baseline of columns and returns a new file.\n\n";
  std::cout << "Usage:\n";
  std::cout << "baseline file1.csv file2.csv ... filen.csv\n";
  std::cout << "columns are specified in file1.ini, file2.ini .. filen.ini\n";
  std::cout << "one column per line. output file is p95_file1.csv, etc.\n";
}

#endif

