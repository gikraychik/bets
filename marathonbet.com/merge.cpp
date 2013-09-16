#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using namespace std;

vector<float> read_file(const char *path)
{
	vector<float> v;
	string line;
	ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			v.push_back(atof(line.data()));
		}
		myfile.close();
	}
	return v;
}
bool hasElem(float f, vector <float> &v)
{
	float e = 0.0001;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == f) { return true; }
	}
	return false;
}
int main(int argc, char **argv)
{
	ofstream f, g;
	f.open("../scripts/new_coeff");
	vector <float> coeff = read_file("../scripts/coeff");
	vector <float> lines_filled = read_file("../scripts/filled");
	vector <float> lines_empty = read_file("../scripts/empty");
	vector <float> merged;
	vector <float> bon_empty;
	int i = 0;
	int j = 0;
	while (true)
	{
		if ((i >= lines_filled.size()) || (j >= lines_empty.size())) { break; }
		if (lines_filled[i] < lines_empty[j])
		{
			merged.push_back(lines_filled[i]);
			f << coeff[i] << endl;
			i++;
		}
		else
		{
			merged.push_back(lines_empty[j]);
			f << 0.0 << endl;
			j++;
		}
	}
	for (int k = i; k < lines_filled.size(); k++)
	{
		merged.push_back(lines_filled[k]);
		f << coeff[k] << endl;
	}
	for (int k = j; k < lines_empty.size(); k++)
	{
		merged.push_back(lines_empty[k]);
		f << 0.0 << endl;
	}
	// merged now
	//cout << merged.size() << endl;
	for (int k = 0; k < merged.size(); k++)
	{
		if (k % 10 >= 6)
		{
			//cout << k << endl;
			if (hasElem(merged[k], lines_empty)) { bon_empty.push_back(merged[k]); }
		}
	}
	//proceeding bon_num && bin_empty
	vector <float> bon_num = read_file("../scripts/bon_num");
	vector <float> bonuses = read_file("../scripts/bonuses");
	g.open("../scripts/new_bonuses");
	i = 0;
	j = 0;
	while (true)
	{
		if ((i >= bon_num.size()) || (j >= bon_empty.size())) { break; }
		if (bon_num[i] < bon_empty[j])
		{
			g << bonuses[i] << endl;
			i++;
		}
		else
		{
			g << ";" << endl;
			j++;
		}
	}
	for (int k = i; k < bon_num.size(); k++)
	{
		g << bonuses[k] << endl;
	}
	for (int k = j; k < bon_empty.size(); k++)
	{
		g << ";" << endl;
	}
	f.close();
	g.close();
	return 0;
}
