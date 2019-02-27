#include "data.hpp"
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "stringsplit.hpp"
#include "calculate.hpp"


void data::readcsvfile(const std::string &f)
{
  std::ifstream file( f );
  std::string singleline {};
  getline(file, m_header);
  m_headersplit = chilisplit(m_header, ";,");
  m_delimiter = determineDelimiter(m_header);
  //  char delimiter {determineDelimiter(m_header)};
  while (std::getline(file, singleline))
    {
      m_linebyline.emplace_back(singleline);
    }
  for (std::string s : m_linebyline)
    {
      m_dat.emplace_back(chilisplit(s, ";,"));
    }
  file.close();
}

data::data(const std::string& csvfilename){
  readcsvfile(csvfilename);
  // construct ini filename
  std::string iniFileName{ csvfilename };
  iniFileName = iniFileName.substr(0, iniFileName.size() - 4) + ".ini";
  readinifile(iniFileName);
  m_delimiter = determineDelimiter(m_header); // mainly determined for output
  if (verifyColumnNumbers())
    {
      std::cout << "ERROR: CSV file malformed.\nHeader contains more or less items than data on the second line.\n";
    }
  calculate();
}

void data::readinifile(const std::string &f)
{
  std::ifstream file(f);
  std::string line;
  while (std::getline(file, line))
    {
      m_whichcols.emplace_back(line);
    }
  file.close();
  }

char data::determineDelimiter(const std::string& singleline)
{
  char outputDelimiter {};
  std::vector<std::string> commavector{split(singleline, ',')};
  std::vector<std::string> semicolumnvector{ split(singleline, ';') };
  if (commavector.size() > semicolumnvector.size())
    {
      outputDelimiter = ',';
    }
  else
    {
      outputDelimiter = ';';
    }
  return outputDelimiter;
}

std::list<unsigned> data::lstcols()
{
  std::list<unsigned> out;
  // unsigned counter = 0;
  // for(std::string s : m_headersplit)
  //   {
  //      for (std::string sc : m_whichcols) //FIXME, once found can be removed
  // 	{
  // 	  if (sc == s) out.push_back(counter);
  // 	}
  //      counter++;
  //   }
  for (std::string s : m_whichcols)
    {
      auto it = std::find(m_headersplit.begin(), m_headersplit.end(), s);
      if (it == m_headersplit.end())
	{std::cout << "Data suggested in ini file was not found in csv file\n";}
      else
	{out.push_back(std::distance(m_headersplit.begin(), it));}
    }
  return out;
}

bool data::verifyColumnNumbers()
{
  return (CompareElementsInTwoStrings( m_linebyline[0], m_header) );
}


bool data::CompareElementsInTwoStrings(std::string s1, std::string s2)
{
  return (chilisplit(s1, ";,").size()!=chilisplit(s2, ";,").size());
}

void data::calculate()
{
  	  std::vector<double> col;
	  std::string p95temp;
	  std::string newfilename{};
	  //	  std::list<unsigned> listcolsofinterest {lstcols()};
	  //	  std::cout << "\nCALC\n";
	  for (unsigned colnbr : lstcols()) {
	    std::cout << m_headersplit[colnbr] << std::endl;
	    p95temp = calcBaseLine(m_dat, colnbr);    //p95temp is a temporaray placeholder for the calculated baseline
	    std::cout << m_headersplit[colnbr] << "-" << p95temp << '\n';
	    // add p95 to data
	    //	    remove newline chars only last character needs to be remove TODO
	    m_header.erase(std::remove(m_header.begin(), m_header.end(), '\n'), m_header.end());
	    m_header = m_header + m_delimiter + "p95" + m_headersplit[colnbr] + '\n';
	    //	    std::cout << m_header;
	    for (auto & e : m_linebyline)
	      {
		e.erase( std::remove( e.begin(), e.end(), '\n' ), e.end() ); // remove newline chars
		e = e + m_delimiter + p95temp + '\n'; // FIXED DELIMITER
	      }
	  }
}

void data::writefile(const std::string& filename)
{
  std::string newfilename = "p95_" + filename;
  std::ofstream outfile(newfilename);
  outfile << m_header;
  for (auto const & e : m_linebyline)
    {
      outfile << e;
    }
  outfile.close();
}
