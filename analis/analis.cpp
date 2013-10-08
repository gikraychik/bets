#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <dirent.h>
#include <string.h>

using namespace std;

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
				games.push_back(Match(ent->d_name));
			}
		}
	}
	
	vector<Match> games;
};
int main(int argc, char **argv)
{
	if (argc > 2) { return 1; }
	const char *path = argv[1];
	Analis analis(path);
	return 0;
}
