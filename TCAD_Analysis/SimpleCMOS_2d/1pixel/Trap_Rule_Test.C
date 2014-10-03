#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Trap_Rule_Test(){		// name of file

using namespace std;

TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);


double data[501][2];

for (int x=0;x<=500;x++){ 
			
	data[x][0]= x;
       	data[x][1]= (x*x);

}
	
TString str =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/1pixel/data.txt");		// does some magic, creates string with name of file
	
// write adapted_data array to text file
ofstream file (str);
if (file.is_open()) {

    	for (int f = 0; f <= 500; f++) {
	
		for (int g = 0; g < 2; g++) {
		
			file << data[0+f][0+g] << " ";
			
		}
			
		file << endl;	
		
 	 }
	
}

double int_data[501][2];
	
int n=0;			// n by m array for int_data	
int m=0;
	

for (int h=0;h<=500;h++){		// loop that finds area under curve at increasing time points using trap rule and stores to array
		
	double sum=0;
		
	for (int d=1;d<=h-1;d++){			// loop for last term in trap rule formula, sum of midpoints
		
		sum+=data[d][1];
			
	}
		
	//write result to array
	int_data[n][m]= h;
	m++;
	int_data[n][m]= 0.5*(data[0][1] + data[h][1] + 2*(sum));
	n++;
	m=0;
		
		
}
	
TString str1 =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/1pixel/int_data.txt");		// does some magic, creates string with name of file
	
// write data array to text file
ofstream myfile (str1);
if (myfile.is_open()) {

    	for (int k = 0; k <= 500; k++) {
	
		for (int l = 0; l < 2; l++) {
		
			myfile << int_data[0+k][0+l] << " ";
			
		}
			
		myfile << endl;	
		
 	 }
	
}
	

TGraph *gr1 = new TGraph(str1,"%lE %lE");		// creates graph and reads file	
	


pad1->Draw();
pad1->cd();
pad1->SetTickx(1);		//draws ticks on top side x axis
pad1->SetTicky(1);		//draws ticks on right hand side y axis

gPad->Update();

gr1->Draw();




}
