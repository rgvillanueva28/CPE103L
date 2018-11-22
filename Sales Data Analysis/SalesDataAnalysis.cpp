#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int NO_OF_SALES_PERSON = 6;

struct salesPersonRec
{
	string ID;
	string name;
	double saleByQuarter[4];
	double totalSale;
	double aveSaleByPerson;
};

void initialize(ifstream& indata, salesPersonRec list[], int listSize)
{
	for (int i= 0; i<listSize; i++)
	{
		indata >> list[i].ID;
		for (int quarter = 0; quarter < 4; quarter++)
		{
			list[i].saleByQuarter[quarter] = 0.0;
		}
		list[i].totalSale = 0.0;
	} 
};

void name(ifstream& indata, salesPersonRec list[], int listSize)
{
	for (int i= 0; i<listSize; i++)
	{
		indata >> list[i].ID >> list[i].name;
		for (int quarter = 0; quarter < 4; quarter++)
		{
			list[i].saleByQuarter[quarter] = 0.0;
		}
		list[i].totalSale = 0.0;
	} 
};

void getData(ifstream& infile, salesPersonRec list[], int listSize)
{
	int index;
	int quarter;
	string sID;
	int month;
	double amount;
	
	infile >> sID;
	
	while (infile)
	{
		infile >> month >> amount;
		for (index = 0; index < listSize; index++)
		{
			if (sID == list[index].ID) break;
		}
		if (1 <= month && month <= 3) quarter = 0;
		else if (4 <= month && month <= 6) quarter = 1;
		else if (7 <= month && month <= 9) quarter = 2;
		else quarter = 3;
		
		if (index < listSize) list[index].saleByQuarter[quarter] += amount;
		else cout << "Invalid salesperson's ID." << endl;
			
		infile>>sID;
	}
};

void saleByQuarter(salesPersonRec list[], int listSize, double totalByQuarter[])
{
	double average[4];
	
	for (int quarter = 0; quarter < 4; quarter++) 
	{
		totalByQuarter[quarter] = 0.0;
	}
	for (int quarter = 0; quarter < 4; quarter++)
	{
		for (int index = 0; index < listSize; index++)
		{			
			totalByQuarter[quarter] += list[index].saleByQuarter[quarter];
		}
	}
};

void totalSaleByPerson(salesPersonRec list[], int listSize, double aveSaleByPerson[])
{
	for (int index = 0; index < listSize; index++)
	{
		for (int quarter = 0; quarter < 4; quarter++)
		{
			list[index].totalSale += list[index].saleByQuarter[quarter];
		}
		list[index].aveSaleByPerson=list[index].totalSale/4;
	}
	
};

void printReport(ofstream& outfile, salesPersonRec list[], int listSize, double saleByQuarter[], double average[])
{
	outfile<<"------------------------------- Annual Sales Report -------------------------------\n\n";
	outfile<<"Name		ID	       QT1	 QT2	   QT3	     QT4     Total   Average\n";
	outfile<<"____________________________________________________________________________________\n";

	for (int i=0; i < listSize; i++)
	{
		outfile << list[i].name<<"		";
		outfile << list[i].ID << "	";
		
		for (int quarter = 0; quarter < 4; quarter++)
		{
			outfile << setw(10)<< list[i].saleByQuarter[quarter];
		}
		outfile << setw(10) << list[i].totalSale << setw(10) << list[i].aveSaleByPerson << endl;
	}
	outfile << "Total			";
	
	for (int quarter = 0; quarter < 4; quarter++)
	{
		outfile << setw(10) << saleByQuarter[quarter];
	}
	outfile << endl;
	
	outfile << "Average			";
	
	for (int quarter = 0; quarter < 4; quarter++)
	{
		outfile << setw(10) << average[quarter];
	}
	outfile << endl << endl;
};

void maxSaleByPerson(ofstream& outData, salesPersonRec list[], int listSize)
{
	int maxIndex = 0;
	for (int index = 1; index < listSize; index++)
	{
		if (list[maxIndex].totalSale < list[index].totalSale)
		{
			maxIndex = index;
		}
	}
	outData << "Max Sale by SalesPerson: ID = " << list[maxIndex].ID << ", Amount = $" << list[maxIndex].totalSale<<endl;
};

void maxSaleByQuarter(ofstream& outData, double saleByQuarter[])
{
	int maxIndex = 0;
	for (int quarter = 0; quarter < 4; quarter++)
	{
		if (saleByQuarter[maxIndex] < saleByQuarter[quarter])
		maxIndex = quarter;
	}
	outData << "Max Sale by Quarter: Quarter = " << maxIndex + 1 << ", Amount = $" << saleByQuarter[maxIndex]<< endl;
};

void leastSaleQuarter(ofstream& outData, salesPersonRec list[], int listSize)
{
	int leastIndex = 0;
	int leastQuarter = 0;
	
	for (int j=0; j<listSize; j++)
	{
		for (int i=0; i<4; i++)
		{
			if (list[leastIndex].saleByQuarter[leastQuarter]>list[j].saleByQuarter[i] && list[j].saleByQuarter[i]!=0)
			{
				leastIndex=j;
				leastQuarter=i;
			}
		}
	}
	outData << "\n\nLeast Sale by Quarter: ID = " << list[leastIndex].ID << ", Name = " << list[leastIndex].name<<", Quarter = "<<leastQuarter+1<<", Amount = $" << list[leastIndex].saleByQuarter[leastQuarter]<<endl;
};

void maxSaleQuarter(ofstream& outData, salesPersonRec list[], int listSize)
{
	int maxIndex = 0;
	int maxQuarter = 0;
	
	for (int j=0; j<listSize; j++)
	{
		for (int i=0; i<4; i++)
		{
			if (list[maxIndex].saleByQuarter[maxQuarter]<list[j].saleByQuarter[i])
			{
				maxIndex=j;
				maxQuarter=i;
			}
		}
	}
	outData << "Max Sale by Quarter: ID = " << list[maxIndex].ID << ", Name = " << list[maxIndex].name<<", Quarter = "<<maxQuarter+1<<", Amount = $" << list[maxIndex].saleByQuarter[maxQuarter]<<endl;
};

void averagePerQuarter(salesPersonRec list[], int listSize, double aveQuarter[], double totalSales[])
{
	double average[4];
	
	for (int quarter = 0; quarter < 4; quarter++) 
	{
		aveQuarter[quarter] = 0.0;
	}
	
	for (int quarter = 0; quarter < 4; quarter++)
	{
		aveQuarter[quarter] = totalSales[quarter]/listSize;
	}
};

int main()
{
	ifstream infile;
	ofstream outfile;	
	 
	string inputFile;
	string outputFile;
	
	double totalSaleByQuarter[4];
	double avePerQuarter[4];
	double averagePerPerson[4];
	
	salesPersonRec salesPersonList[NO_OF_SALES_PERSON]; 
		
	cout<<"Enter salesPerson ID file name: ";
	cin>>inputFile;
	
	infile.open(inputFile.c_str());
	if (!infile)
	{
		cout<<"Cannot open the file!";
		return 1;
	}
	
	initialize(infile, salesPersonList, NO_OF_SALES_PERSON);

	infile.close();
	infile.clear();
	
	
	cout<<"\nEnter salesPerson name file name: ";
	cin>>inputFile;
	
	infile.open(inputFile.c_str());
	if (!infile)
	{
		cout<<"Cannot open the file!";
		return 1;
	}
	
	name(infile, salesPersonList, NO_OF_SALES_PERSON);

	infile.close();
	infile.clear();
		
	cout << "\nEnter the sales data file name: ";
	cin >> inputFile;
		
	infile.open(inputFile.c_str());
	if (!infile)
	{
		cout<<"Cannot open the file!";
		return 1;
	}
		
	cout << "\nEnter the output file name: ";
	cin >> outputFile;
	
	outfile.open(outputFile.c_str());
	outfile << fixed << showpoint << setprecision(2);
	
	getData(infile, salesPersonList, NO_OF_SALES_PERSON);
	
	saleByQuarter(salesPersonList, NO_OF_SALES_PERSON, totalSaleByQuarter);
	
	totalSaleByPerson(salesPersonList, NO_OF_SALES_PERSON, averagePerPerson);
		
	averagePerQuarter(salesPersonList, NO_OF_SALES_PERSON, avePerQuarter, totalSaleByQuarter);
		
	printReport(outfile, salesPersonList, NO_OF_SALES_PERSON, totalSaleByQuarter, avePerQuarter);
	
	maxSaleByPerson(outfile, salesPersonList, NO_OF_SALES_PERSON);
	
	maxSaleByQuarter(outfile, totalSaleByQuarter);
	
	leastSaleQuarter(outfile, salesPersonList, NO_OF_SALES_PERSON);
	
	maxSaleQuarter(outfile, salesPersonList, NO_OF_SALES_PERSON);
	
	infile.close();
	outfile.close();
		
	return 0;
}
