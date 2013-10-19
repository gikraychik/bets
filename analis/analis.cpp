#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <dirent.h>
#include <string.h>
#include <cstdlib>
#include <map>
#include <cmath>
//#include <tgmath.h>

using namespace std;
class Result
{
public:
	Result(void) : res1(NULL), res2(NULL)
	{
		v[0][0] = 0; v[0][1] = 0; v[1][0] = 0; v[1][1] = 0;
	}
	Result(int x11, int x12, int x21, int x22) : res1(NULL), res2(NULL)
	{
		v[0][0] = x11; v[0][1] = x12; v[1][0] = x21; v[1][1] = x22;
	}
	Result(int arr[2][2]) : res1(NULL), res2(NULL)
	{
		v[0][0] = arr[0][0]; v[0][1] = arr[0][1]; v[1][0] = arr[1][0]; v[1][1] = arr[1][1];
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
        if (y < d.y) { return true; } else if (y > d.y) { return false; }
        if (m < d.m) { return true; } else if (m > d.m) { return false; }
        if (this->d < d.d) { return true; } else if (this->d > d.d) { return false; }
        return false;
    }
    bool operator ==(Date d)
	{
		return ((y == d.y) && (m == d.m) && (this->d == d.d));
	}
	bool operator <=(Date d) { return operator <(d) || operator ==(d); }
	bool operator >(Date d) { return !operator<=(d); }
	bool operator >=(Date d) { return !operator<(d); }
    int days() const
    {
        int month[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        return (y - 2013) * 365 + month[m-1] + (d-1);
    }
    static Date toDate(int x)
    {        
        
        int month[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        int year = x / 365;
        x -= year * 365;
        int mon = -1;
        for (int i = 0; i < 12; i++)
        {
            if (month[i] > x) { mon = i - 1; break; }
        }
        if (mon == -1) { mon = 11; }
        x -= month[mon];
        return Date(x+1, mon + 1, 2013 + year);
    }
    int operator +(Date date) const
    {
        return date.days() + days();
    }
    int operator -(Date date) const
    {
        int d1 = days();
        int d2 = date.days();
        if (d1 < d2) { return -1; }
        return d1 - d2;
    }
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
    int seconds(void) const
    {
        return 3600 * h + 60 * m + s;
    }
    inline static Time toTime(int sec)
    {
        int x = sec - (sec / (24 * 3600)) * 24 * 3600;
        return Time(x / 3600, (x % 3600) / 60, x % 60);
    }
    inline bool operator <(Time t) const
    {
        return seconds() < t.seconds();
    }
    bool operator ==(Time t) { return seconds() == t.seconds(); }
    bool operator <=(Time t) { return operator <(t) || operator ==(t); }
    bool operator >(Time t) { return ! operator <=(t); }
    bool operator >=(Time t) { return ! operator <(t); }
    Time operator +(Time t)
    {
        return Time::toTime(t.seconds() + seconds());
    }
    Time operator -(Time t)
    {
        int t1 = seconds();
        int t2 = t.seconds();
        if (t1 < t2) { t1 += 24 * 3600; }
        int res = t1 - t2;
        return Time::toTime(res);
    }
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
    Moment(Date d, Time t) : date(d), time(t) {}
    bool operator <(Moment m)
    {
        if (date < m.date) { return true; }
        else if (date > m.date) { return false; }
        else
        {
            if (time < m.time) { return true; }
            else { return false; }
        }
    }
    bool operator ==(Moment m) { return (date == m.date) && (time == m.time); }
    bool operator <= (Moment m) { return operator <(m) || operator ==(m); }
    bool operator >(Moment m) { return ! operator <=(m); }
    bool operator >=(Moment m) { return ! operator <(m); }
    double operator -(Moment moment)  //in hours
    {
        if ((*this) < moment) { return -1; }
        int days = 0;
        if (time < moment.time)
        {
            days = date.toDate(date - moment.date) - Date(2, 1, 2013);
        }
        else { days = date - moment.date; }
        double t = (double)(time - moment.time).seconds();
        return 24*((double)days) + t / (3600);     
    }
    double hours(void)
    {
        return operator-(Moment(Date(1, 1, 2013), Time(0, 0, 0)));
    }
    static Moment toMoment(double hours)
    {
        int days = floor(hours / 24);
        Date dt = Date::toDate(days);
        hours -= days * 24;
        int sec = round(hours * 3600);
        Time tm = Time::toTime(sec);
        return Moment(dt, tm);
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
	Match(void) : stinf(StaticInfo()), lines(vector<Line>()) {}
	Match(const char *path)
	{
		string ln;
		ifstream file(path);
		if (file.is_open())
		{
			int d, m, y;
			readDate(file, d, m, y);
			int hours, minutes, seconds;
			readTime(file, hours, minutes);
			getline(file, ln);
			const char *com1 = strdup(ln.data());
			getline(file, ln);
			const char *com2 = strdup(ln.data());
			int arr[2][2];
			for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
				    getline(file, ln);
				    arr[i][j] = atoi(ln.data());
                }
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
				readTime(file, hours, minutes, seconds);
				vector<double> coeff(10, 0);
				for (int i = 0; i < 10; i++)
				{
					getline(file, ln);
					coeff[i] = atof(ln.data());
				}
				vector<double> bonuses(4, 0);
				for (int i = 0; i < 4; i++)
				{
					getline(file, ln);
					bonuses[i] = atof(ln.data());
				}
				Date date(d, m, y);
				Time time(hours, minutes, seconds);
				Line line(date, time, coeff, bonuses);
				lines.push_back(line);
			}
			file.close();
		}
	}
	bool bet_won(int kind) const
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
    bool bonuses_eq(void) const  //это нужно для анализа 2
    {
        double b0 = lines[0].bonuses[0];
        double b1 = lines[0].bonuses[1];
        double b2 = lines[0].bonuses[2];
        double b3 = lines[0].bonuses[3];
        for (int i = 1; i < lines.size(); i++)
        {
            if (!((lines[i].bonuses[0] == b0) && (lines[i].bonuses[1] == b1) && (lines[i].bonuses[2] == b2) && (lines[i].bonuses[3] == b3))) { return false; }
        }
        return true;
    }
	StaticInfo stinf;
	vector<Line> lines;
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
    int readTime(ifstream &file, int &hours, int &minutes, int &seconds)
    {
        string ln;
		if (!getline(file, ln)) { return 0; }  //end of file
		hours = atoi(ln.data());
		getline(file, ln);
		minutes = atoi(ln.data());
        getline(file, ln);
        seconds = atoi(ln.data());
		return 1;  //correct
    }
};
class Analis
{
public:
	Analis(void) : games(vector<Match>()) {}
	Analis(vector<Match > &games) : games(games) {}
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
	void analis2(int kind) const  //анализирует коэффиценты типа kind 
	{
		cout << "Вывод всех коэффицентов типа kind = " << kind << ":" << endl;
        double delta = -1000.0;
		for (int i = 0; i < games.size(); i++)
		{
            cout << "*********************************" << endl;
			vector <double> coeff = games[i].get_coeff(kind);
            cout << "Матч: " << games[i].stinf.resdate.d << "-" << games[i].stinf.resdate.m << "-" << games[i].stinf.resdate.y << " ";
            cout << games[i].stinf.restime.h << ":" << games[i].stinf.restime.m << endl;
            cout << games[i].stinf.cmds.first << "-" << games[i].stinf.cmds.second << endl;
			print(coeff);
            double min = games[i].min(coeff);
            double max = games[i].max(coeff);
			cout << "Максимумумом является коэффицент: " << max << endl;
			cout << "Минимумом является коэффицент: " << min << endl;
            if ((max - min) > delta) { delta = max - min; }
            //cout << "*********************************" << endl;
            cout << "" << endl;
        }
        cout << "" << endl;
        cout << "Наибольшая дельта (max - min): " << delta << endl;
		/*bool all_bonuses_eq = true;
		for (int i = 0; i < games.size(); i++)
		{
           // if (!games[i].bonuses_eq()) { all_bonuses_eq = false; }
           cout << games[i].bonuses_eq() << endl;
		}
        cout << "Для каждого матча бонусы являются постоянными: " << all_bonuses_eq << endl;*/
        cout << "" << endl;
	}
    void analis3(int kind) const  //анализирует бонусы
    {
        bool all_bonuses_eq = true;
        for (int i = 0; i < games.size(); i++)
        {
            if (!games[i].bonuses_eq())
            {
                all_bonuses_eq = false;
                for (int j = 0; j < games[i].lines.size(); j++)
                {
                    for (int k = 0; k < 4; k++) { cout.width(6); cout << games[i].lines[j].bonuses[k]; }
                    cout << endl;
                }
                cout << "*******************************" << endl;
            }
        }
    }
    void analis4(int kind, double t0, int accuracy) const  //выявление положительного матожидания, построенного в момент времени t0
    {
        map<double, double> P;
        map<double, double> E;
        map<double, bool> Pos;
        map<double, int> All;
        int all = 0;
        for (int i = 0; i < games.size(); i++)
        {
            Moment start(games[i].stinf.resdate, games[i].stinf.restime);
            double time_start = start.hours();
            double ts = time_start - t0;
            if (ts < 0) { break; }
            Moment moment = Moment::toMoment(ts);
            for (int j = 0; j < games[i].lines.size(); j++)
            {
                Line line = games[i].lines[j];
                Moment curMoment(line.date, line.time);
                double delta = (curMoment < moment) ? moment - curMoment : curMoment - moment;
                if (delta > 0.5) { continue; }
                double k = Analis::rnd(line.coeff[kind], accuracy);
                P[k] += games[i].bet_won(kind); All[k] += 1;
                all++;
            }
        }
        cout << "Вывод вероятностей всех коэффицентов с шагом E" << accuracy << " для kind = " << kind << ":" << endl;
        for (map<double, double>::iterator i = P.begin(); i != P.end(); i++)
        {
            double first = (*i).first;
            //cout << first << "->" << (*i).second << " ";
            P[first] /= All[first];
            //cout << P[first] << " " << All[first] << endl;
        }
        cout << "***************************************************" << endl;
        for (map<double, double>::iterator i = P.begin(); i != P.end(); i++)
        {
            double k = (*i).first;
            E[k] = k * (*i).second - 1;  //E[k] = p * k
            Pos[k] = E[k] > 0;
            const int indent = 10;
            cout.width(indent); cout << k;
            //cout << k << P[k] << All[k] << E[k] << Pos[k] << endl;
            cout.width(indent); cout << P[k];
            cout.width(indent); cout << All[k];
            cout.width(indent); cout << E[k];
            cout.width(indent); cout << Pos[k] << endl;
        }
        cout << "Количество матчей, по которым проводились расчеты: " << all << endl;
    }
	vector<Match> games;
	map<double, int> Pk;
private:
	void print(vector<double> &v, int amount = 10) const
	{
		for (int i = 1; i < v.size()+1; i++)
		{
            if (i % amount == 0) { cout << endl; }
            cout.width(5);
			cout << v[i-1];
		}
		cout << endl;
	}
public:
    static double rnd(double x, int k)
    {
        double p = pow(10, k);
        return round(x * p) / p;
    }
};
int main(int argc, char **argv)
{
	if (argc > 2) { return 1; }
	const char *path = argv[1];
    int kind = 0;
    //kind = atoi(path);
    path = "Matches/";
    /*Match m(path);
    Line l = m.lines[1];
    cout << l.time.s << endl;
    cout << "Size: " << l.bonuses.size() << endl;
    for (int i = 0; i < l.bonuses.size(); i++)
    {
        cout << l.bonuses[i] << " " << endl;
    }*/
    Analis anal(path);
    anal.analis4(kind, 12.0, 1);
    Date d1(14, 05, 2014);
    Date d2(2, 01, 2014);
    Time t1(2, 43, 21);
    Time t2(19, 8, 52);
    //cout << t1.days() << endl;
    //cout << t2.days() << endl;
    //Date t3 = t1.toDate(t1.days());
    Moment m1(d1, t1);
    Moment m2(d2, t2);
    //cout << m1.hours() << endl;
    //Moment m = Moment::toMoment((double)(m1.hours()));
    //cout << m.date.d << ":" <<m.date.m<< ":" << m.date.y << " " << m.time.h << ":" << m.time.m << ":" << m.time.s << endl;
    //double delta = m1 - m2;
    //cout << delta << endl;
    //cout << t3.d << ":" << t3.m << ":" << t3.y << endl;
    return 0;
}
