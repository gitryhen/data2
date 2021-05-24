/*
make a gnuplot script to plot all columns in a csv file
combine if present p95 column to with normal variable
do not print p95 column separately.
*/

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> // needed for std::istringstream
#include <algorithm> // std::transform (walk over two ranges)
#include <cmath>     // std::round
#define MAIN 1

std::vector<std::string> split(const std::string& s, char delimiter);

struct lut{std::string s; int i;};
std::vector<lut> createnumberedlut(std::vector<std::string> vs);
int findcolnumber(std::string s, const std::vector<lut> vl);
void boilerplate();
void makeplotscript(std::string s, const std::string & outputfilename, const std::string & datafilename, const int colnumber);
void makeplotscriptwithbaseline(std::string s, const std::string & outputfilename, const std::string & datafilename, const int colnumber, const int datcolnumber, const std::string baselinenumber);
  

#ifdef MAIN
int main(int argc, char* argv[])
{
  if (argc == 1)
    {
      std::cout << "Returns column headers if non-empty\n";
      std::cout << "Usage:\n";
      std::cout << "mpl file1.csv file2.csv ... file3.csv\n";
      return 1; // what is de juiste error code voor geen args?
    }
  else
    {
      for (int i = 1; i <= argc; ++i){
	// open file that is named as the first argument
	std::string datafilename = argv[i];
	std::ifstream file(argv[i]);
	std::string line;
	std::string line2;
	// read first line in the file
	std::getline(file, line);
	// split first line
	std::vector<std::string> vspl;
	vspl = split(line, ',');
	//	// remove temporaryMaintenance as it seems to have no data and does not have comma
	// std::vector<std::string> tmpvspl;
	// for (auto e : vspl) {
	//   if (e != "temporaryMaintenance") tmpvspl.emplace_back(e);
	// }
	// vspl = tmpvspl;
	// make a copy of the filename to remove the extension
	// later used in the filename of the picture/plot
	std::string filename = argv[i];
	//remove extension from filename.
	filename.erase(filename.end()-4, filename.end());
	/* create lookuptable for colnumber
	   since empty columns are to be ignored,
	   and need the absolute column number for gnplot.
	*/

	// redirect std::cout to outputfile
	std::ofstream out(filename+".plt");
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

	boilerplate();
	
	auto mylut = createnumberedlut(vspl);
	// read the second line to determine if column is empty
	std::getline(file, line2);
	file.close();
	std::vector<std::string> line2split;
	std::vector<std::string> resvec;
	// split second line
	line2split = split(line2, ',');
	/* if column on second line contained a space
	   then replace the columnheader with the a space.
	   this allows to remove the spaces from the columnheaders
	*/
	std::transform(vspl.begin(), vspl.end(), line2split.begin(), std::back_inserter(resvec),
		       [](std::string s1, std::string s2) {return s2 != " " ? s1 : s2;});
	// remove spaces thus removing empty columns (empty col contains no data in second line)
	resvec.erase(std::remove(resvec.begin(), resvec.end(), " "),
		     resvec.end());
	/* remove Sensor and Timestamp; col 1 and 2
	   it makes no sense to print time vs timestamp
	   nor does time versus sensor */
	resvec.erase(resvec.begin());
	resvec.erase(resvec.begin());
	// output the gnuplot code.
	for (auto el : resvec){
	  if (el.substr(0,3) != "p95") {
	    makeplotscript(el,filename, datafilename, findcolnumber(el, mylut));}
	  else {
	    // float currentbaseline = ::atof(line2split[findcolnumber(el,mylut)-1].c_str());
	    // currentbaseline = std::round(currentbaseline*1000)/1000;
	    std::string dat = el;
	    dat.erase(dat.begin(), dat.begin()+3); // remove p95 from string to obtain original data since el contains the baseline col
	    makeplotscriptwithbaseline(el,filename, datafilename, findcolnumber(el, mylut), findcolnumber(dat, mylut),
				       line2split[findcolnumber(el,mylut)-1]);
	    // std::cout << "--" << findcolnumber(el,mylut) << "= " << std::to_string(currentbaseline) << "|" << '\n';
	    // int cnt = 1;
	    // for (auto e : line2split) {std::cout << cnt++ << "-" << e << ", ";}
	    // std::cout << '\n';
	    // cnt = 1;
	    // for (auto e : vspl) {std::cout << cnt++ << "-" << e << ", ";}
	    // std::cout << '\n';
	    // cnt = 1;
	    // for (auto e : resvec) {std::cout << cnt++ << "-" << e << ", ";}
	    // std::cout << '\n';
	    
	  }
	  //(nGV_Mon_Jul_02_13_47_51_UTC_2018.csv)39. TemperatureGradient
	}
	std::cout << "\nset output\n"; // closes the last file so it can be opened.
	// reset redirection out to std::cout
	std::cout.rdbuf(coutbuf); //reset to standard output again
	return 0;
      }
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

void boilerplate(){
  std::cout <<
    "set key autotitle columnhead\n" <<
    "set datafile separator \",\"\n" <<
    "set timefmt \"%Y-%m-%d %H:%M:%S\"\n" <<
    "set xdata time\n" <<
    "set format x \"%Y%m%d\"\n" <<
    "# set yrange[0:1]\n" <<
    "# set xlabel \"Date\"\n" <<
    "set terminal png size 1400,560 enhanced font \"Arial\" 15\n" <<
    "# fixes the axis position, so plots align from one plot to the next\n" <<
    "set lmargin 10\n" <<
    "set rmargin 3\n" <<
    "set key opaque\n" <<
    "set style textbox opaque margins 2,1.5 fc \"grey75\"\n";
}

 void makeplotscript(std::string s, const std::string & outputfilename, const std::string & datafilename, const int colnumber){
  std::cout
      	  << "set output \"" << outputfilename << "_" << s << ".png\"" << '\n'
      	  << "plot "
      	  << '\'' << datafilename << '\''
      	  << " using 2:" << colnumber
      	  << " with lines linecolor rgb \"blue\" lw 2" << '\n';}

void makeplotscriptwithbaseline(std::string s, const std::string & outputfilename, const std::string & datafilename,
				const int colnumber, const int datcolnumber, const std::string baselinenumber){
  // set number
  // set style textbox opaque margins 6,1.5 fc "grey75" border lc black
  // set style textbox opaque margins 6,1.5 fc "grey75" border lc black
  std::cout
      	  << "set output \"" << outputfilename << "_" << s << ".png\"" << '\n'
 	  << "set label 1\"" << baselinenumber << "\" at graph -0.01, first " << baselinenumber << " right boxed tc rgb \"red\"\n"
     	  << "plot "
      	  << '\'' << datafilename << '\''
      	  << " using 2:" << datcolnumber
      	  << " with lines linecolor rgb \"blue\" lw 2, \\" << '\n'
	  << "\'\'  using 2:" << colnumber << " with lines linecolor rgbcolor \"0x88FF0101\" lw 2\n";
}
