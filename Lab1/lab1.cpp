/*
 *	Name: Ngawang Rinchen
 *	
 *	Problem: Read input from file of varying data types.  Output the average of one column (Price) with respect to other columns (Brand & Category).  Also, Return a list of one column (Skus) with
 *	their respective years as a list.
 *	
 *	Solution: Eliminate each element of the vector (Brand & Category) as you sum and take the average of the price.  Use the same design to isolate and output the skus by their year. 
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

void findAverage(vector <string> colOne, vector <float> colTwo);
vector <float> clone(vector <float> target);
void countSku(vector <int> vSku, vector <int> vYears);
ofstream outStream ("Output.txt");

int main(){
	string sku, brand, category, year, price;
	vector <int> vSku; 
	vector <string> vBrand; 
	vector <string> vCategory; 
	vector <int> vYear; 
	vector <float> vPrice;

	ifstream inStream;
	inStream.open("data.csv");	

	if(inStream.good()){

		string line;

		while(getline(inStream, line)){

			stringstream lineStream (line);	

			//SKU Col		
			getline(lineStream,sku,',');
			stringstream sSku (sku);
			int iSku = 0;
			sSku >> iSku;
			vSku.push_back(iSku);		

			//Brand Col
			getline(lineStream, brand, ',');
			vBrand.push_back(brand);

			//Category Col
			getline(lineStream, category, ',');
			vCategory.push_back(category);

			//Year Col		
			getline(lineStream,year,',');
			stringstream sYear (year);
			int iYear = 0;
			sYear >> iYear;
			vYear.push_back(iYear);

			//Price Col		
			getline(lineStream,price,',');
			stringstream sPrice (price);
			float iPrice = 0;
			sPrice >> iPrice;
			vPrice.push_back(iPrice);		

		}

		cout << "Average Price By Brand:\n";
		outStream << "Average Price By Brand:\n";
		findAverage(vBrand,vPrice);
		
		cout << "\nAverage Price By Category\n";
		outStream << "\nAverage Price By Category\n";
		findAverage(vCategory, vPrice);
		
		cout << "\nSkus By Year\n";
		outStream << "\nSkus By Year\n";
		countSku(vSku,vYear);

	} else {
		cout << "Unable to open file.";
	}	

	inStream.close();
	outStream.close();
}

void findAverage(vector <string> colOne, vector <float> colTwo){

	int counter = 0;
	float sum = 0;
	string pattern;
	vector <string> colOneFinal;
	vector <float> colTwoFinal;

	//Remove Header
	colOne.erase(colOne.begin());
	colTwo.erase(colTwo.begin());

	//While vector is not empty, look at first element and remove it.  Scan the rest of the vector for that pattern and remove it as well while taking the sum and counting.
	while (!colOne.empty()){
		counter = 0;
		sum = 0;	
		pattern = colOne.at(0);
		cout << pattern << " : ";
		outStream << pattern << " : ";
		sum += colTwo.at(0);
		counter++;
		colOne.erase(colOne.begin());
		colTwo.erase(colTwo.begin());

		for(int i = 0 ; i < colOne.size() ; i++){	
			if(colOne.at(i) == pattern){
				counter++;
				sum += colTwo.at(i);
				colOne.erase(colOne.begin()+i);
				colTwo.erase(colTwo.begin()+i);
				i--;
			}

		}
		cout << (sum/counter) << "\n";		
		outStream << (sum/counter) << "\n";		
	}	
}

void countSku(vector <int> vSku, vector <int> vYears){

	int pattern;
	int counter = 0;
	vector <string> vSkuFinal;
	vector <float> vYearsFinal;

	//Remove Header
	vSku.erase(vSku.begin());
	vYears.erase(vYears.begin());

	//While year vector is not empty, remove first year and find matching years, removing them and printing the skus.
	while (!vYears.empty()){
		counter = 0;	
		pattern = vYears.at(0);
		cout << pattern << " : " << vSku.at(0) << " ";
		outStream << pattern << " : " << vSku.at(0) << " ";

		counter++;
		vSku.erase(vSku.begin());
		vYears.erase(vYears.begin());

		for(int i = 0 ; i < vYears.size() ; i++){	
			if(vYears.at(i) == pattern){
				counter++;
				cout << vSku.at(i) << " "; 
				outStream << vSku.at(i) << " "; 
				vSku.erase(vSku.begin()+i);
				vYears.erase(vYears.begin()+i);
				i--;
			}

		}
		cout << " [ "  << counter << " ]\n";
		outStream << " [ "  << counter << " ]\n";
	}	
}
