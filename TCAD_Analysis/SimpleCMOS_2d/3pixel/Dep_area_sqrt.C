#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Dep_area_sqrt(){		// name of file

using namespace std;

double data [31][2];		// define array to store data
int n=0;			// n by m array
int m=0;
double pitch=20.0;			

for (double bias=2.0;bias<=60.0;bias+=2.0){		// loop to create of graph for each bias value and output data to an array


	
	TString str =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD/SimpleCMOS/DepletionSimRemesh_3pixels/3pixel_extraction_bias=%.1f_pitch=%.1f.txt",bias,pitch);		// does some magic, creates string with name of file and inserts bias value
	TGraph2D *gr= new TGraph2D(str,"%lg %lg %lE");		// creates graph called gr and reads file
	TRandom3 *rando = new TRandom3();



	gr->Draw("colz");	// draws 2D graph


	double tot_area = 6400;
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
	data[n][m]= sqrt (double (bias));
	m++;
	data[n][m]= tot_area*double(in_dep)/total;
	n++;
	m=0;
	

}

// write array to text file
ofstream myfile ("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/3pixel/3pixel_SqrtBias_Dep_pitch=20.0.txt");
if (myfile.is_open()) {

    	for (int k = 0; k < 31; k++) {
	
		for (int l = 0; l < 2; l++) {
		
			myfile << data[0+k][0+l] << " ";
			
		}
			
		myfile << endl;	
		
 	 }

}
/*
TCanvas *c2 = new TCanvas("c2","c2", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);

TGraph *graph= new TGraph("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/3pixel/3pixel_SqrtBias_Dep.txt","%lg %lg");		// creates graph called gr and reads file

// makes graph look fancy...ish
graph->SetLineColor(2);
graph->SetLineWidth(1);
graph->SetMarkerSize(0.75);
graph->SetMarkerStyle(21);
graph->SetTitle("Depletion area vs. #sqrt{bias} for a simple 3 pixel device with pitch 15#mum");
graph->GetXaxis()->SetTitle("#sqrt{Bias} (V)");
graph->GetYaxis()->SetTitle("Depletion Area (#mum^{2})");
graph->GetXaxis()->CenterTitle();
graph->GetYaxis()->CenterTitle();

pad1->Draw();
pad1->cd();
pad1->SetTicky(2);		//draws ticks and labels on right hand side y axis
pad1->SetGrid(1,1);		//sets grid lines on major ticks

graph->Draw("ACP");
*/
}
