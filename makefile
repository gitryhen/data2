fast:
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O0 baseline.cpp -o baseline.exe
	g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O0 makeplotscriptforallgraphs4.cpp -o mpl.exe
baseline:
	clang++ -std=c++17 -c -O3 stringsplit.cpp -o stringsplit.o
	clang++ -std=c++17 -c -O3 calculate.cpp -o calculate.o
	clang++ -std=c++17 -c -O3 data.cpp -o data.o
	clang++ -std=c++17 -O3 baseline1112.cpp data.o stringsplit.o calculate.o -o baseline1112.exe
# baseline:
# 	g++ -std=c++17 -O3 -c stringsplit.cpp -o stringsplit.o
# 	g++ -std=c++17 -O3 -c calculate.cpp -o calculate.o
# 	g++ -std=c++17 -O3 baseline.cpp stringsplit.o calculate.o -o baseline.exe
mpl:
	g++ -std=c++17 -O3 makeplotscriptforallgraphs6.cpp -o mpl6.exe
	clang++ -std=c++17 -O3 makeplotscriptforallgraphs6.cpp -o mpl_clang6.exe
debug:
	g++ -std=c++17 -c stringsplit.cpp -o stringsplit.o
	g++ -std=c++17 -ggdb -c calculate.cpp -o calculate.o -Wall -Wextra -Wpedantic
	g++ -std=c++17 -c data.cpp -o data.o -Wall -Wextra -Wpedantic
	g++ -std=c++17 -ggdb baseline816.cpp data.o stringsplit.o calculate.o -o baseline816.exe -Wall -Wextra -Wpedantic
linuxbaselineclang:
	clang++ -std=c++17 -c -O3 stringsplit.cpp -o stringsplit.o
	clang++ -std=c++17 -c -O3 calculate.cpp -o calculate.o
	clang++ -std=c++17 -c -O3 data.cpp -o data.o
	clang++ -std=c++17 -O3 baseline816.cpp data.o stringsplit.o calculate.o -o baseline_clang
linuxbaseline:
	g++ -std=c++17 -c -O3 stringsplit.cpp -o stringsplit.o
	g++ -std=c++17 -c -O3 calculate.cpp -o calculate.o
	g++ -std=c++17 -c -O3 data.cpp -o data.o
	g++ -std=c++17 -O3 baseline816.cpp data.o stringsplit.o calculate.o -o baseline
