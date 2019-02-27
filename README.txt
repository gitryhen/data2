Manual to make plots from csv file with mpl.exe and baseline.exe

8 august 2018
Henry Kelderman

mpl.exe prepares a plotscript for use in gnuplot with the same name as
the datafile, just with the extension plt.
baseline.exe determines the baseline for columns in a csv file that
are defined in an ini file with the same name.

Restrictions:
1. csv file delimiter should be comma,
2. sometimes temporaryMaintenance is set as a feed, and can be found as a header,
but there is no data in the column! If empty columns are used in csv file
output will be garbled.

Step-by-step plotting graphs from csv file:
1. to make the plots we run mpl2 on csv file:

mpl p95test.csv

2. open gnuplot
3. open p95test.plt in gnuplot
png files will be created in the folder where plot.plt is placed.

Step-by-step with BASELINE:
1. download csv file,
2. open cmd (windows-key, type cmd<ENTER>),
3. copy mpl.exe and baseline.exe to folder where csv file is found*,
4. make a empty text file named exactly as the csv file, but with the
extention ini
	e.g. test.csv -> test.ini
5. open ini file and add the name of the feeds that a baseline needs
to be calculated of. The ini file should have one feed per line and is
case-sensitive, e.g. it should read:

A1Res
B2Res

6. run baseline.exe to add a column with the baseline added as a column to a new csv file
that will called p95test.csv if the initial csv file is test.csv
7. to make the plots we run mpl2 on the new csv file:

mpl2.exe p95test.csv

8. open gnuplot
9. open p95test.plt in gnuplot
10. png files will be created in the folder where plot.plt is placed.


Remarks
*) the two executables may also be put in one of the folders set in the PATH variable,
so that they can be run from anywhere.
If a baseline is calculated for a feed, there will be plot with just the data of the feed
AND a plot with the data of the feed and the baseline called p95Feed

Todo
1. check for empty columns -> the validity of the csv file is the
responsibility of the user!
