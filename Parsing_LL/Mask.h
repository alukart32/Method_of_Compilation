#pragma once

using namespace std;

#include <string>

class Mask
{
	string alpha = "";
	string A = "";
	string beta = "";
public:
	void setAlpha(string new_alpha)
	{
		alpha = new_alpha;
	};
	void setA(string new_A)
	{
		A = new_A;
	};
	void setBeta(string new_beta)
	{
		beta = new_beta;
	};

	string getA()
	{
		return A;
	};

	string getBeta()
	{
		return beta;
	};
};