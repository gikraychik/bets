#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

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

int main(int argc, char **argv)
{
	ofstream f;
	f.open("scripts/new_coeff");
	vector <float> coeff = read_file("scripts/coeff");
	vector <float> lines_filled = read_file("scripts/filled");
	vector <float> lines_empty = read_file("scripts/empty");
	int i = 0;
	int j = 0;
	while (true)
	{
		while (lines_filled[i] < lines_empty[j])
		{
			f << coeff[i] << endl;
			i++;
			if (i == lines_filled.size()) { break; }
		}
		if (j >= lines_empty.size()) { break; }
		if (i >= lines_filled.size()) { break; }
		while (lines_filled[i] > lines_empty[j])
		{
			f << 0.0 << endl;
			j++;
			if (j == lines_empty.size()) { break; }
		}
	}
	while (i < lines_filled.size())
	{
		f << coeff[i] << endl;
		i++;
	}
	f.close();
	return 0;
}
