#pragma once
#include <string>

using namespace std;

class Command
{
private: 
	string data;
	string src;
	string dest;

public: 

	// getter and setter
	string getData();
	string getSrc();
	string getDest();
	void setData(string data);
	void setSrc(string src);
	void setDest(string dest);

	// functions
	Command(string data, string src, string dest);
	Command();
	~Command();
};

