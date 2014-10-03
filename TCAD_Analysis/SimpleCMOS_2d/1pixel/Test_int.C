#include "TGraph.h"
#include <iostream>
#include <fstream>

void Test_int(){		// name of file

using namespace std;

double bias=2;

double data[201][2];

int m=0;

TGraph *gr[m];			// defines array to number of TGraphs

for (double bias=2;bias<=10;bias+=2){		// loop to create of graph for select bias values


	TString str =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD/SimpleCMOS/DepletionSimRemesh_Particle_v10/Current_Cleaned_bias=%.0f.txt",bias);		// does some magic, creates string with name of file

	gr[m] = new TGraph(str,"%lE %lE");		// creates graph called gr and reads file
	
	double time=0;
	
	int i=0;
	int j=0;
	
	memset(data, 0, sizeof(data));			//set all array elements to 0
	
	
	for (double x=0;x<=199;x++){
		
		data[i][j]= time;
		j++;
		data[i][j]= gr[m]->Integral(0, x);
		i++;
		j=0;
		time+=5e-11;
		
		
	}
	
	TString str2 =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/1pixel/Test_CC_Simple_Pixel_bias=%.0f.txt",bias);		// does some magic, creates string with name of file
	
	// write array to text file
	ofstream myfile (str2);
	if (myfile.is_open()) {

    		for (int k = 0; k < 201; k++) {
	
			for (int l = 0; l < 2; l++) {
		
				myfile << data[0+k][0+l] << " ";
			
				}
			
			myfile << endl;	
		
 	 	}
	
	}
	
}
	



}
