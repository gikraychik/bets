#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

struct Date
{
public:
	Date (const char *date)
	{
		this->date = string(date);
	}
	int h, m;
	string date;
};
struct Time
{
public:
	Time(const char *time)
	{
		this->time = string(time);
	}
	int h, m, s;
	string time;
};
struct Commands
{
public:
	Commands(const char *first, const char *second)
	{
		this->first = string(first);
		this->second = string(second);
	}
	string first;
	string second;
};
class Match
{
public:
	Match(const char *path)
	{
		
	}
	double coeff[10];
	Date date();
	Commands cmd();	
};
int main()
{
	
	return 0;
}
