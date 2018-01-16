#include "Stocks.h"

Stock::Stock() {
	Date = "";
	for (int x = 0; x < 5; x++) { arr[x] = 0; }
	volume = 0;
	avg = 0;
}
Stock::Stock(string date, double open, double high, double low, double close, double adj, long volume) {
	this->Date = date;
	arr[0] = open;
	arr[1] = high;
	arr[2] = low;
	arr[3] = close;
	arr[4] = adj;
	this->volume = volume;
}
string Stock::getDate() { return Date; }
double*Stock::getArray() { return arr; }
double Stock::getOpen() { return arr[0]; }
double Stock::getHigh() { return arr[1]; }
double Stock::getLow() { return arr[2]; }
double Stock::getClose() { return arr[3]; }
double Stock::getAdj() { return arr[4]; }
double Stock::getAvg() { return avg; }
long Stock::getVolume() { return volume; }
void Stock::setDate(string s) { this->Date = s; }
void Stock::setVolume(long v) { this->volume = v; }
void Stock::setOpen(double open) { arr[0] = open; }
void Stock::setHigh(double high) { arr[1] = high; }
void Stock::setLow(double low) { arr[2] = low; }
void Stock::setClose(double close) { arr[3] = close; }
void Stock::setAdj(double adj) { arr[4] = adj; }
void Stock::setAvg(double avg) { this->avg = avg; }
bool Stock::operator < (const Stock& s)const { return (Date > s.Date); }
bool Stock::operator > (const Stock& s)const { return (Date < s.Date); }
istream &operator >> (istream& is, Stock& obj) { return is; }
ostream &operator << (ostream& os, const Stock& obj) {
	os << obj.Date << ",";
	for (int x = 0; x < 5; x++) { os << obj.arr[x] << ","; }
	os << obj.volume << ",";
	os << obj.avg << endl;
	return os;
}
Stock Stock::operator =(const Stock& obj) {
	this->Date = obj.Date;
	for (int x = 0; x < 5; x++) { this->arr[x] = obj.arr[x]; }
	this->volume = obj.volume;
	this->avg = obj.avg;
	return obj;
}
bool Stock::operator == (const Stock& obj) { return (obj.Date == this->Date); }

Container::Container() { name = ""; yes = "null"; }
Container::Container(string name) { this->name = name; }
void Container::push(Stock s) { v.push_back(s); }
void Container::push_front(Stock s) { v.insert(v.end(), s); }
void Container::pop() { v.pop_back(); }
void Container::yesno(bool t) {
	if (t == true) { yes = "Yes";}
	else { yes = "No"; }
}
string Container::getYes() { return yes; }
Stock Container::getData(int i) { return v[i]; }
void Container::setName(string name) { this->name = name; }
string Container::getName() { return name; }
int Container::getSize() { return v.size(); }
vector<Stock> Container::getVector() { return v; }
void Container::runAvg()
{
	double avgRunning = 0;
	for (int x = v.size() - 1; x >= 0; x--) {
		avgRunning += v[x].getAdj();
		if (x < (v.size() - 9)) {
			v[x].setAvg(avgRunning / 10);
			avgRunning -= v[x + 9].getAdj();
		}
	}
}


vector<Container> getNames(string fileName) {
	string line;
	ifstream myfile(fileName);
	vector<Container> fileVector;
	Container c;

	while (!myfile.eof()) {
		getline(myfile, line);
		fileVector.push_back(Container(line));
		fileVector.push_back(Container(line + " (1)"));
		fileVector.push_back(Container(line + "-final"));
	}

	return fileVector;
}
void files(vector<Container>& fileNames) {
	string checkFileName;
	vector<Stock> cont;
	for (int x = 0; x < fileNames.size(); x += 3) {
		readFile(fileNames[x]);
		readFile(fileNames[x + 1]);
		mergeFiles(fileNames, x);
	}
}
void mergeFiles(vector<Container>& fileNames, int index) {
	set<Stock> s;

	for (int x = 0; x < fileNames[index].getSize(); x++) {
		s.insert(fileNames[index].getData(x));
	}

	for (int x = 0; x < fileNames[index + 1].getSize(); x++) {
		s.insert(fileNames[index + 1].getData(x));
	}

	set<Stock>::const_iterator si;
	si = s.cbegin();
	while (si != s.cend()) {
		Stock stocks = *si;
		fileNames[index + 2].push(stocks);
		si++;
	}
	if (fileNames[index + 2].getData(0).getAvg() > fileNames[index + 2].getData(0).getAdj()) 
		fileNames[index + 2].yesno(true);
	else
		fileNames[index + 2].yesno(false);
}
void readFile(Container& fileNames) {
	string line;
	string addCSV;
	ifstream myFile;
	addCSV = fileNames.getName() + ".csv";
	myFile.open(addCSV);

	getline(myFile, line);
	Stock s;

	while (getline(myFile, line, ',')) {
		s.setDate(line);
		getline(myFile, line, ',');
		s.setOpen(stod(line));
		getline(myFile, line, ',');
		s.setHigh(stod(line));
		getline(myFile, line, ',');
		s.setLow(stod(line));
		getline(myFile, line, ',');
		s.setClose(stod(line));
		getline(myFile, line, ',');
		s.setAdj(stod(line));
		getline(myFile, line);
		s.setVolume(stol(line));
		fileNames.push_front(s);
		Stock s;
	}
	myFile.close();
}
void writeFile(Container C) {
	ofstream myfile;
	myfile.open(C.getName() + ".csv");

	myfile << "Date,Open,High,Low,Close,Adj Close,Volume,Average" << endl;

	for (int i = 0; i < C.getSize(); i++) {
		Stock s = C.getData(i);
		myfile << s;
	}
	myfile.close();
}
void getcsvAve(vector<Container> &fileNames)
{
	for (int i = 0; i < fileNames.size(); i++)
	{
		fileNames[i].runAvg();
	}
}

void writeYes(vector<Container> &fileNames) {
	ofstream myfile;
	myfile.open("status.csv");

	for (int x = 0; x < fileNames.size(); x+=3)
		myfile << fileNames[x].getName() << "," << fileNames[x+2].getYes() << endl;

	myfile.close();	
}
