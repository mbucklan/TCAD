#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Pulse_shape_3pixel_Rad(){		// name of file

using namespace std;

int i=0;			// used to name the TGraphs

double bias=30;

TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);
TLegend *leg = new TLegend(.75,.70,.85,.87);

TGraph *gr[5];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double fluence=13;fluence<=15;fluence+=1){		// loop to create of graph for select bias values

	TString str =TString::Format("/afs/cern.ch/work/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/3pixel/Rad_Adapted_array_3pixel_bias=%.1f_Fluence=1e+%.0f_200.txt",bias,fluence);		// does some magic, creates string with name of file
	
	if (i==4){
	
	i++;
	
	}

	gr[i] = new TGraph(str,"%lE %lE");		// creates graph called gr and reads file
	
	TString str1 =TString::Format("1e+%.0f n_{eq} cm^{-2}",fluence);		// creates string with bias value
	
	gr[i]->SetTitle(str1);			// sets title to string
	gr[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
	gr[i]->SetLineWidth(1);
	//gr[i]->SetMarkerSize(0.9);
	//gr[i]->SetMarkerStyle(21);
	
	mg->Add(gr[i]);				// adds graph to multigraph

	leg->AddEntry(gr[i],str1,"l");
	
	i++;
	
	}


pad1->Draw();
pad1->cd();
pad1->SetTickx(1);		//draws ticks on top side x axis
pad1->SetTicky(1);		//draws ticks on right hand side y axis

gPad->Update();

mg->Draw("AL");		// draws graph

// Make the graph look fancy...ish
mg->GetXaxis()->SetTitle("Time (s)");
mg->GetYaxis()->SetTitle("Total Current (A)");

TString str2 =TString::Format("Pulse Shape for 3 Pixel 100#mum Thick Sensor at %.0fV, Resistivity=100#Omegacm",bias);		// does some magic, creates string with name of file
	
mg->GetHistogram()->SetTitle(str2);
mg->SetMinimum(0);

//mg->GetXaxis()->SetLimits(0.1e-8,0.4e-8);

leg->SetTextSize(0.03);
leg->Draw();


}
