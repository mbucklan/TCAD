#include "TGraph.h"
#include <iostream>
#include <fstream>

void eDensity(){		// name of file

using namespace std;


double pedgeL= 2.0;		// distance from the left edge to the p implant
double nedgeR= 2.0;		// distance from the right edge to the n implant
double bias=0;
int i=0;			// used to name the TGraphs

TCanvas *c1 = new TCanvas("c1","c1",600,400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);

TGraph *gr[31];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double bias=0.;bias<=60.0;bias+=10.0){		// loop to create of graph for select bias values

	TString str =TString::Format("../TCAD/SimpleCMOS/DepletionSimRemesh/extraction_yCut_bias=%.1f_pedgeL=%.1f_nedgeR=%.1f.txt",bias,pedgeL,nedgeR);		// does some magic, creates string with name of file


	gr[i] = new TGraph(str,"%lg %lg");		// creates graph called gr and reads file
	
	
	TString str1 =TString::Format("%.1f V",bias);		// creates string with bias value
	gr[i]->SetTitle(str1);			// sets title to string
	gr[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
	
	mg->Add(gr[i]);				// adds graph to multigraph
	
	i+=1;
	
	}
	

	
mg->Draw("ACP");		// draws graph
gPad->Update();


// Make the graph look fancy...ish
mg->GetXaxis()->SetTitle("Depth (#mum)");
mg->GetYaxis()->SetTitle("Electron Density (cm^{-3})");
mg->GetHistogram()->SetTitle("Electron Density vs. depth into sensor at width 12.5#mum for various bias values");

mg->GetXaxis()->SetLimits(0,30);
mg->SetMinimum(-2e12);
mg->SetMaximum(47e12);


c1->BuildLegend();


}
