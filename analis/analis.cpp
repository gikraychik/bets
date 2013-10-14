#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <dirent.h>
#include <string.h>
#include <cstdlib>
#include <map>

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
	Result(int arr[2][2]) : res1(NULL), res2(NULL)
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
	bool operator <(Date d)
	{
		if (y < d.y) { return true; }
		else if (m < d.m) { return true; }
		else return this->d < d.d;
	}
	bool operator ==(Date d)
	{
		return ((y == d.y) && (m == d.m) && (this->d == d.d));
	}
	bool operator <=(Date d) { return operator <(d) || operator ==(d); }
	bool operator >(Date d) { return !operator<=(d); }
	bool operator >=(Date d) { return !operator<(d); }
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
	StaticInfo(Date &d, Time &t, Commands &c, Result &r) : resdate(d), restime(t), cmds(c), res(r) {}
	StaticInfo(void) : resdate(Date()), restime(Time()), cmds(Commands()), res(Result()) {}
	void init(Date &d, Time &t, Commands &c, Result &r)
	{
		resdate = d;
		restime = t;
		cmds = c;
		res = r;
	}
	Date resdate;
	Time restime;
	Commands cmds;
	Result res;
};
//typedef pair<Date, Time> Moment;
class Moment
{
public:
    Moment(Date &d, Time &t) : date(d), time(t) {}
    bool operator <(Moment &moment)
    {
        if (date < moment.date) { return true; }
        else if (date > moment.date) { return false; }
        else
        {
            if (time < moment.time) { return true; }
            else (time > moment.time) { return false; }
        }
    }
    Date date;
    Time time;
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
	Match(void) : stinf(StaticInfo()), lines(vector<Line>()), delts(10, 0) {}
	Match(const char *path)
	{
		string ln;
		ifstream file(path);
		if (file.is_open())
		{
			int d, m, y;
			readDate(file, d, m, y);
			int hours, minutes;
			readTime(file, hours, minutes);
			getline(file, ln);
			const char *com1 = ln.data();
			getline(file, ln);
			const char *com2 = ln.data();
			int arr[2][2];
			for (int i=0,j=0; i<2,j<2; i++,j++)
			{
				getline(file, ln);
				arr[i][j] = atoi(ln.data());
			}
			Date date(d, m, y);
			Time time(hours, minutes);
			Commands cmds(com1, com2);
			Result result(arr);
			stinf.init(date, time, cmds, result);  //initialization of StaticInfo field
			while (1)
			{
				int isOk = readDate(file, d, m, y);
				if (!isOk) { break; }  //testing if end of file
				readTime(file, hours, minutes);
				vector<double> coeff(10, 0);
				for (int i = 0; i < 10; i++)
				{
					getline(file, ln);
					coeff[i] = atof(ln.data());
				}
				vector<double> bonuses(10, 0);
				for (int i = 0; i < 4; i++)
				{
					getline(file, ln);
					bonuses[i] = atof(ln.data());
				}
				Date date(d, m, y);
				Time time(hours, minutes);
				Line line(date, time, coeff, bonuses);
				lines.push_back(line);
			}
			file.close();
		}
		Result res = stinf.res;
	}
	bool bet_won(int kind)
	{
		Result res = stinf.res;
		vector <double> bonuses(lines[0].bonuses);  // предположили, что бонусы не изменяются на протяжении всей игры. Нужно проверить!
		if (kind == 0) { return res.v[0][0] > res.v[0][1]; }
		else if (kind == 1) { return res.v[0][0] == res.v[0][1]; }
		else if (kind == 2) { return res.v[0][0] < res.v[0][1]; }
		else if (kind == 3) { return res.v[0][0] >= res.v[0][1]; }
		else if (kind == 4) { return res.v[0][0] != res.v[0][1]; }
		else if (kind == 5) { return res.v[0][0] <= res.v[0][1]; }
		else if (kind == 6) { return (res.v[0][0] + bonuses[0]) == res.v[0][1]; }
		else if (kind == 7) { return res.v[0][0] == (res.v[0][1] - bonuses[1]); }
		else if (kind == 8) { return (res.v[0][0] + res.v[0][1]) < bonuses[2]; }
		else if (kind == 9) { return (res.v[0][0] + res.v[0][1]) > bonuses[3]; }
		else return -1;
	}
	vector <double> get_coeff(int kind) const  //возвращает все коэффиценты на матч типа номер kind; 0<=kind<=9
	{
		vector <double> v;
		for (int i = 0; i < lines.size(); i++)
		{
			v.push_back(lines[i].coeff[kind]);
		}
		return v;
	}
	double max(vector<double> &v) const
	{
		double max = -1000;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i] > max) { max = v[i]; }
		}
		return max;
	}
	double min(vector<double> &v) const
	{
		double min = 1000;
		for (int i = 0; i < v.size(); i++)
		{
			if (v[i] < min) { min = v[i]; }
		}
		return min;
	}
	double Mcoeff(int kind)
	{
		vector<double> v = get_coeff(kind);
		double sum = 0.0;
		for (int i = 0; i < v.size(); i++)
		{
			sum += v[i];
		}
		if (v.size() == 0) { return -1; }
		return sum / v.size();
	}
	StaticInfo stinf;
	vector<Line> lines;
	vector<int> delts;
private:
	int readDate(ifstream &file, int &d, int &m, int &y) const
	{
		string ln;
		if (!getline(file, ln)) { return 0; }  //end of file
		d = atoi(ln.data());
		getline(file, ln);
		m = atoi(ln.data());
		getline(file, ln);
		y = atoi(ln.data());
		return 1;  //correct
	}
	int readTime(ifstream &file, int &hours, int &minutes) const
	{
		string ln;
		if (!getline(file, ln)) { return 0; }  //end of file
		hours = atoi(ln.data());
		getline(file, ln);
		minutes = atoi(ln.data());
		return 1;  //correct
	}
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
		closedir(dir);
	}
	/*void analis1(int mode) const
	{
		for (int j = 0; j < games.size(); j++)
		{
			Match match = games[j];
			for (int i = 0; i < match.lines.size(); i++)
			{
				Line line = match.lines[i];
				for (int k = 0; k < 10; k++)
				{
					
				}
			}			
		}
	}*/
	void analis2(int kind) const  //анализирует коэффиценты типа kind 
	{
		cout << "Вывод всех коэффицентов типа kind = " << kind << ":" << endl;
		for (int i = 0; i < games.size(); i++)
		{
			vector <double> coeff = games[i].get_coeff(kind);
			print(coeff);
			cout << "Максимумумом является коэффицент: " << games[i].max(coeff) << endl;
			cout << "Минимумом является коэффицент: " << games[i].min(coeff) << endl;
		}
		bool all_bonuses_eq = true;
		for (int i = 0; i < games.size(); i++)
		{
			Match m = games[i];
			for (int k = 0; k < m.lines.size(); k++)
			{
				//lol
			}
		}
	}
	vector<Match> games;
	map<double, int> Pk;
private:
	void print(vector<double> &v) const
	{
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i] << " ";
		}
		cout << endl;
	}
};
int main(int argc, char **argv)
{
	if (argc > 2) { return 1; }
	const char *path = argv[1];

	return 0;
}
