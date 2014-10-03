#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Dep_area(){		// name of file

using namespace std;


double pedgeL= 2.0;		// distance from the left edge to the p implant
double nedgeR= 2.0;		// distance from the right edge to the n implant

double data [31][2];		// define array to store data
int n=0;			// n by m array
int m=0;			

for (double bias=2.0;bias<=60.0;bias+=2.0){		// loop to create of graph for each bias value and output data to an array


	
	TString str =TString::Format("../TCAD/SimpleCMOS/DepletionSimRemesh/extraction_bias=%.1f_pedgeL=%.1f_nedgeR=%.1f.txt",bias,pedgeL,nedgeR);		// does some magic, creates string with name of file
	TGraph2D *gr= new TGraph2D(str,"%lg %lg %lE");		// creates graph called gr and reads file
	TRandom3 *rando = new TRandom3();



	gr->Draw("colz");	// draws 2D graph


	double tot_area = 2500;
	int in_dep = 0;		// no. of throws inside the depletion zone
	int total  = 0;		// total of number of throws


	for (int i=0;i<100000;i++){

		// make a throw, defines x and y coordinates
		double x= rando->Uniform(0,100.);		
		double y= rando->Uniform(0,25.);
	
		double econc= gr->Interpolate(x,y);		// electron concentration, obtains value of throw
		total+=1;
	
		if(econc<1e13){
	
			in_dep+=1;				// inside the depletion region if electron concentration is less than 1e13
		}	
		
	}

	// write result to array
	data[n][m]= bias;
	m++;
	data[n][m]= tot_area*double(in_dep)/total;
	n++;
	m=0;


}

// write array to text file
ofstream myfile ("../TCAD_Analysis/SimpleCMOS_2d/1pixel/Bias_Dep_SimplePixel.txt");
if (myfile.is_open()) {

    	for (int k = 0; k < 31; k++) {
	
		for (int l = 0; l < 2; l++) {
		
			myfile << data[0+k][0+l] << " ";
			
			}
			
		myfile << endl;	
		
 	 }

}


TGraph *graph= new TGraph("../TCAD_Analysis/SimpleCMOS_2d/1pixel/Bias_Dep_SimplePixel.txt","%lg %lg");		// creates a graph called graph and reads file

// makes graph look fancy...ish
graph->SetLineColor(2);
graph->SetLineWidth(1);
graph->SetMarkerSize(0.9);
graph->SetMarkerStyle(21);
graph->SetTitle("Depletion area vs. bias for a simple pixel");
graph->GetXaxis()->SetTitle("Bias (-V)");
graph->GetYaxis()->SetTitle("Depletion Area (#mum^{2})");
graph->GetXaxis()->CenterTitle();
graph->GetYaxis()->CenterTitle();

graph->Draw("ACP");		// draws graph

}
