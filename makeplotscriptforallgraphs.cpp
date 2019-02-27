#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> // needed for std::istringstream
#include <algorithm> // std::transform (walk over two ranges)
#define MAIN 1

std::vector<std::string> split(const std::string& s, char delimiter);

struct lut{std::string s; int i;};

std::vector<lut> createnumberedlut(std::vector<std::string> vs);

int findcolnumber(std::string s, const std::vector<lut> vl);
  

#ifdef MAIN
int main(int argc, char* argv[])
{
  if (argc > 0){
    for (int i = 1; i <= argc; ++i){
      std::ifstream file(argv[i]);
      std::string line;
      std::getline(file, line);
      std::vector<std::string> vspl;
      vspl = split(line, ',');
      // create lookuptable for colnumber from
      auto mylut = createnumberedlut(vspl);
      // for (auto e : mylut)
      // 	{
      // 	  std::cout << e.s << " | " << e.i << '\n';
      // 	};
      // std::cout << findcolnumber("aap", mylut) << " testje\n";
      // unsigned counter =1;
      std::string line2;
      std::getline(file, line2);
      std::vector<std::string> line2split;
      std::vector<std::string> resvec;
      line2split = split(line2, ',');
      std::transform(vspl.begin(), vspl.end(), line2split.begin(), std::back_inserter(resvec),
		     [](std::string s1, std::string s2) {return s2 != " " ? s1 : s2;});
      auto it = std::remove(resvec.begin(), resvec.end(), " ");
      resvec.erase(it, resvec.end());
      for (auto el : resvec){ std::cout
      	  << "set output \"" << argv[i] << "_" << el << ".png\"" << '\n'
      	  << "plot "
      	  << '\'' << argv[i] << '\''
      	  << " using 2:" << findcolnumber(el, mylut)
      	  << " with lines linecolor rgb \"blue\" lw 2" << '\n'; }
      //(nGV_Mon_Jul_02_13_47_51_UTC_2018.csv)39. TemperatureGradient
    }
    return 0;
  }
  else{
    std::cout << "Returns column headers if non-empty\n";
    std::cout << "Usage:\n";
    std::cout << "mpl file1.csv file2.csv ... file3.csv\n";
    return 0; // what is de juiste error code voor geen args?
  }
}
#endif


std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

std::vector<lut> createnumberedlut(std::vector<std::string> vs)
{
  int counter = 0;
  std::vector<lut> agg;
  lut l;
  for (auto e : vs)
    {
      counter++;
      l.s = e;
      l.i = counter;
      agg.push_back(l);
    };
  return agg;
}

int findcolnumber(std::string s, const std::vector<lut> vl)
{
  auto ans =0;
  for (auto e : vl)
    {
      if (e.s == s) ans = e.i;
    };
  return ans;
}
