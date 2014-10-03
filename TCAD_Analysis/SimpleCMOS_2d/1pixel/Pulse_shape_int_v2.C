#include "TGraph.h"
#include <iostream>
#include <fstream>
#include "TTree.h"

void Pulse_shape_int_v2(){		// name of file

using namespace std;

double bias=2;
int i=0;			// used to name the TGraphs

double data[501][2];

TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);

TGraph *gr[5];			// defines array to number of TGraphs
TGraph *gr1[5];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double bias=2;bias<=10;bias+=2){		// loop to create of graph for select bias values

	TString str =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD/SimpleCMOS/DepletionSimRemesh_Particle_v10/Current_Cleaned_bias=%.0f.txt",bias);		// does some magic, creates string with name of file
	TString str1 =TString::Format("Current_Cleaned_bias=%.0f",bias);		// does some magic, creates string with name of file
	
	
	TTree *tree = new TTree("T",str1);
	tree->Branch("Time", &Time, "Time/D");
	tree->Branch("Current", &Current, "Current/D");
	char line[499];
		
	while (fgets(&line,499,fp)) {
      		sscanf(&line[0],"%d %d",&Time,&Current);
    		tree->Fill();
   	}
	tree->Write();
	

}


}
