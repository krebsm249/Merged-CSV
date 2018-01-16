#ifndef Stocks_H
#define Stocks_H
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
using namespace std;

class Stock {
private:
	string Date;
	double arr[5];
	long volume;
	double avg;
public:
	Stock();
	Stock(string date, double open, double high, double low, double close, double adj, long volume);
	string getDate();
	double*getArray();
	double getOpen();
	double getHigh();
	double getLow();
	double getClose();
	double getAdj();
	double getAvg();
	long getVolume();
	void setDate(string s);
	void setVolume(long v);
	void setOpen(double open);
	void setHigh(double high);
	void setLow(double low);
	void setClose(double close);
	void setAdj(double adj);
	void setAvg(double avg);
	bool operator < (const Stock& s)const;
	bool operator > (const Stock& s)const;
	friend istream &operator >> (istream& is, Stock& obj);
	friend ostream &operator << (ostream& os, const Stock& obj);
	Stock operator =(const Stock& obj);
	bool operator == (const Stock& obj);
};

class Container {
private:
	string name;
	vector<Stock> v;
	string yes;
public:
	Container();
	Container(string name);
	void push(Stock s);
	void push_front(Stock s);
	void pop();
	Stock getData(int i);
	void setName(string name);
	string getName();
	int getSize();
	vector<Stock> getVector();
	void runAvg();
	void yesno(bool t);
	string getYes();
};

vector<Container> getNames(string);
void files(vector<Container>&);
void readFile(Container&);
void writeFile(Container c);
void mergeFiles(vector<Container>&, int);
void getcsvAve(vector<Container>&);
void writeYes(vector<Container> &fileNames);

#endif
