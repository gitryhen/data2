#include <numeric> // accumulate
#include <cmath>   // std::numeric_limits<double>::quiet_NaN()
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "calculate.hpp"

#define NN std::numeric_limits<double>::quiet_NaN()


template<typename T>
T stdev(const std::vector<T>& v) {
	double sum = std::accumulate(v.begin(), v.end(), 0.0);
	double mean = sum / v.size();
	std::vector<double> diff(v.size());
	std::transform(v.begin(), v.end(), diff.begin(), [mean](double x) { return x - mean; });
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
	double stdev = std::sqrt(sq_sum / v.size());
	return stdev;
}

std::string calcBaseLine(const std::vector<std::vector<std::string> > & dat, const unsigned colnbr) {
  std::vector<double> colconvert {};  // convert col to double
  for (auto e : dat) {
    colconvert.emplace_back(::atof(e[colnbr].c_str())); //std::strtof(e,NULL)). atof returns a double!
  }
  std::cout << std::accumulate(colconvert.begin(), colconvert.end(), 0.0) / colconvert.size() << " = average\n";
  std::cout << stdev(colconvert) << " = standard deviation\n";
  std::vector<double> tmp;
  tmp = colconvert;
  tmp.erase(std::remove_if(tmp.begin(), tmp.end(),
			   [](double x) {return x<1e-6; })
	    , tmp.end());
  std::cout << stdev(tmp) << " = stdev with zeros taken out\n";

  std::vector<double> colmaxs{};
  colmaxs = collectMaxInSections(colconvert);
  colmaxs.erase(std::remove_if(colmaxs.begin(), colmaxs.end(),
			       [](auto f) {return std::isnan(f); }
			       )
		, colmaxs.end());
  colmaxs.erase(std::remove_if(colmaxs.begin(), colmaxs.end(),
			       [](auto f) {return (f<1e-6); }
			       )
		, colmaxs.end());
  std::cout << colmaxs.size() << " datapoints\n";
  std::cout << std::endl;
  std::sort(colmaxs.begin(), colmaxs.end());
  //  double p50 {colmaxs[colmaxs.size()/2]};
  //  double p90 {colmaxs[colmaxs.size()*.90]};
  double p95{ colmaxs[colmaxs.size()*.95] };
  return std::to_string(p95);
}

template<typename T>
std::vector<T> collectMaxInSections(const std::vector<T> t) {
  std::vector<T> out;
  T maxval = -1.0;
  for (auto e : t) {
    if (e > maxval) maxval = e;
    if (e == 0) {
      if (maxval > 0) {
	out.emplace_back(maxval);
	maxval = -1.0;
      }
      else out.emplace_back(NN);
    }
    else out.emplace_back(NN);
  }
  return out;
}
