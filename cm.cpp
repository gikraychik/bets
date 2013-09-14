#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

vector<const char *> read_file(const char *path)
{
	vector<const char *> v;
	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			v.push_back(line.data());
		}
		myfile.close();
	}
	return v;
}
void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* записываем знак */
         n = -n;          /* делаем n положительным числом */
     i = 0;
     do {       /* генерируем цифры в обратном порядке */
         s[i++] = n % 10 + '0';   /* берем следующую цифру */
     } while ((n /= 10) > 0);     /* удаляем */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
int main(int argc, char **argv)
{
	//if (argc != 2) { return 1; }
	string s("");
	ofstream f;
	string path = s + string("commands");
	vector <const char *> commands = read_file(path.data());
	path = s + string("dates");
	vector <const char *> dates = read_file(path.data());
	path = s + string("coeffs");
	vector <const char *> coeff = read_file(path.data());
	for (int i = 0; i < dates.size(); i++)
	{
		char *tmp = (char *)malloc(10);
		itoa(i, tmp);
		path = s + string(tmp);
		int j = 2 * i;
		int k = 10 * i;
		int p = 4 * i;
		f.open(path.data());
		f << commands[j] << endl << commands[j+1] << endl << dates[i] << endl;
		for (int q = k; q < k + 10; q++)
		{
			f << coeff[q] << endl;
		}
		free(tmp);
		f.close();
	}
	return 0;
}
