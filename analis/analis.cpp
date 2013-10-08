#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <dirent.h>
#include <string.h>
#include <cstdlib>

using namespace std;
class Result
{
public:
	Result(void) : res1(NULL), res2(NULL)
	{
		for (int i = 0, j = 0; i<2,j<2; i++,j++) { v[i][j] = 0; }
	}
	Result(int x11, int x12, int x21, int x22) : res1(NULL), res2(NULL)
	{
		v[0][0] = x11; v[0][1] = x12; v[1][0] = x21; v[1][1] = x22;
	}
	Result(int **arr) : res1(NULL), res2(NULL)
	{
		for (int i=0, j=0; i < 2,j < 2; i++, j++) { v[i][j] = arr[i][j]; }
	}
	int v[2][2];
	const char *res1;
	const char *res2;
private:
	void transform(void);
};
class Date
{
public:
	Date (const char *date) : d(0), m(0), y(0), date(string(date)) {}
	Date (int d, int m, int y) : d(d), m(m), y(y), date(string("")) {}
	Date() : d(0), m(0), y(0), date(string("")) {}
	int d, m, y;
	string date;
private:
	void transform(void);
};
class Time
{
public:
	Time (const char *time) : h(0), m(0), s(0), time(string(time)) {}
	Time (int h, int m, int s) : h(h), m(m), s(s), time(string("")) {}
	Time (int h, int m) : h(h), m(m), s(0), time(string("")) {}
	Time (void) : h(0), m(0), s(0), time(string("")) {}
	int h, m, s;
	string time;
private:
	void transform(void);
};
class Commands
{
public:
	Commands(const char *first, const char *second) : first(string(first)), second(string(second)){}
	Commands(void) : first(string("")), second(string("")) {}
	string first;
	string second;
};
class StaticInfo
{
public:
	StaticInfo(Date &d, Time &t, Commands &c) : resdate(d), restime(t), cmds(c) {}
	StaticInfo(void) : resdate(Date()), restime(Time()), cmds(Commands()) {}
	Date resdate;
	Time restime;
	Commands cmds;
};
class Line
{
public:
	Line(void) : date(Date()), time(Time()), coeff(10, 0), bonuses(4, 0) {}
	Line(Date &date, Time &time, vector<double> &coeff, vector<double> &bonuses)
		: date(date), time(time), coeff(coeff), bonuses(bonuses) {}
	Date date;
	Time time;
	vector<double> coeff;
	vector<double> bonuses;
};
class Match
{
public:
	Match(void) : stinf(StaticInfo()), lines(vector<Line>()) {}
	Match(const char *path)
	{
		string ln;
		ifstream file(path);
		if (file.is_open())
		{
			while (1)
			{
				getline(file, ln);
				int d = atoi(ln.data());
				getline(file, ln);
				int m = atoi(ln.data());
				getline(file, ln);
				int y = atoi(ln.data());
				getline(file, ln);
				int hours = atoi(ln.data());
				getline(file, ln);
				int minutes = atoi(ln.data());
				getline(file, ln);
				const char *com1 = ln.data();
				getline(file, ln);
				const char *com2 = ln.data();
				Date date(d, m, y);
				Time time(hours, minutes);
				Commands cmds(com1, com2);
				StaticInfo staticinfo(date, time, cmds);
				int arr[2][2];
				for (int i=0,j=0; i<2,j<2; i++,j++)
				{
					getline(file, ln);
					arr[i][j] = atoi(ln.data());
				}							
			}
			file.close();
		}
	}
	StaticInfo stinf;
	vector<Line> lines;
};
class Analis
{
public:
	Analis(void) : games(vector<Match>()) {}
	Analis(vector<Match> &games) : games(games) {}
	Analis(const char *path)
	{
		DIR *dir;
		dirent *ent;
		dir = opendir(path);
		while ((ent=readdir(dir)) != NULL)
		{
			if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
			{
				games.push_back(Match((string("Matches/")+string(ent->d_name)).data()));
			}
		}
	}
	
	vector<Match> games;
};
int main(int argc, char **argv)
{
	if (argc > 2) { return 1; }
	const char *path = argv[1];
	Match m(path);
	return 0;
}
