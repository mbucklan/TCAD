#include "TGraph.h"
#include <iostream>
#include <fstream>

void Dep_area_comp(){		// name of file

using namespace std;

double pitch=15.0;
int i=0;			// used to name the TGraphs

TCanvas *c1 = new TCanvas("c1","c1",600,400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);

TGraph *gr[2];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double pitch=15.0;pitch<=20.0;pitch+=5.0){		// loop to create multigraph for select bias values

	TString str =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/3pixel/Dep_area_sqrt_pitch=%.1f.txt",pitch);		// does some magic, creates string with name of file


	gr[i] = new TGraph(str,"%lg %lg");		// creates graph called gr and reads file
	
	
	TString str1 =TString::Format("%.1f V",bias);		// creates string with bias value
	gr[i]->SetTitle(str1);			// sets title to string
	gr[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
	
	mg->Add(gr[i]);				// adds graph to multigraph
	
	i+=1;
	
	}
	

	
mg->Draw("ACP");		// draws multigraph
gPad->Update();


// Make the graph look fancy...ish
mg->GetXaxis()->SetTitle("Depth (#mum)");
mg->GetYaxis()->SetTitle("Electron Density (cm^{-3})");
mg->GetHistogram()->SetTitle("Electron Density vs. depth into 3 pixel sensor with a pitch of 20#mum at half width for various bias values");

mg->GetXaxis()->SetLimits(0,40);
mg->SetMinimum(-2e12);
mg->SetMaximum(47e12);


c1->BuildLegend();


}
