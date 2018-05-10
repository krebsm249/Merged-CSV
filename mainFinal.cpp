#include "Stocks.h"

//Test Commit

int main()
{
	vector<Container> fileNames;
	fileNames=getNames("names.csv");

	for (int x = 0; x < fileNames.size(); x++) {
		cout << fileNames[x].getName() << endl;
	}

	files(fileNames);
	getcsvAve(fileNames);

	for (int x = 0; x < fileNames.size(); x += 3) {
		writeFile(fileNames[x + 2]);
	}

	writeYes(fileNames);

	system("pause");
	return 0;
}
