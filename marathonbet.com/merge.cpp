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
	ofstream f, g;
	f.open("../scripts/new_coeff");
	g.open("../scripts/bon_empty");
	vector <float> coeff = read_file("../scripts/coeff");
	vector <float> lines_filled = read_file("../scripts/filled");
	vector <float> lines_empty = read_file("../scripts/empty");
	int i = 0;
	int j = 0;
	int k = -1;
	while (true)
	{
		while (lines_filled[i] < lines_empty[j])
		{
			f << coeff[i] << endl;
			i++; k++;
			if (i == lines_filled.size()) { break; }
		}
		if (j >= lines_empty.size()) { break; }
		if (i >= lines_filled.size()) { break; }
		//if (k % 10 >= 6) { g << lines_empty[j] << endl; }
		while (lines_filled[i] > lines_empty[j])
		{
			f << 0.0 << endl;
			j++; k++;
			if (k % 10 >= 6) { g << lines_empty[j] << endl; }
			if (j == lines_empty.size()) { break; }
		}
	}
	while (i < lines_filled.size())
	{
		f << coeff[i] << endl;
		i++; k++;
	}
	f.close();
	g.close();
	f.open("../scripts/new_bonuses");
	vector <float> bonuses = read_file("../scripts/bonuses");
	vector <float> lin_filled = read_file("../scripts/bon_num");
	vector <float> lin_empty = read_file("../scripts/bon_empty");
	i = 0; j = 0;	
	while (true)
	{
		while (lin_filled[i] < lin_empty[j])
		{
			f << bonuses[i] << endl;
			i++;
			if (i == lin_filled.size()) { break; }
		}
		if (j >= lin_empty.size()) { break; }
		if (i >= lin_filled.size()) { break; }
		//if (k % 10 >= 6) { g << lines_empty[j] << endl; }
		while (lin_filled[i] > lin_empty[j])
		{
			f << ";" << endl;
			j++;
			if (j == lin_empty.size()) { break; }
		}
	}
	while (i < lin_filled.size())
	{
		f << bonuses[i] << endl;
		i++;
	}
	f.close();
	return 0;
}
