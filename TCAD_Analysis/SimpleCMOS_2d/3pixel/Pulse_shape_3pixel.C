#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Pulse_shape_3pixel(){		// name of file

using namespace std;

int i=0;			// used to name the TGraphs

TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);
TLegend *leg = new TLegend(.80,.70,.85,.87);

TGraph *gr[5];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double bias=10;bias<=40;bias+=10){		// loop to create of graph for select bias values

	TString str =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/3pixel/Adapted_array_3pixel_bias=%.1f_200.txt",bias);		// does some magic, creates string with name of file
	
	if (i==4){
	
	i++;
	
	}

	gr[i] = new TGraph(str,"%lE %lE");		// creates graph called gr and reads file
	
	TString str1 =TString::Format("%.0fV",bias);		// creates string with bias value
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

mg->Draw("AC");		// draws graph

// Make the graph look fancy...ish
mg->GetXaxis()->SetTitle("Time (s)");
mg->GetYaxis()->SetTitle("Total Current (A)");
mg->GetHistogram()->SetTitle("Pulse Shape for 3 Pixel 100#mum Thick Sensor, Resistivity=100#Omegacm");
mg->SetMinimum(0);

mg->GetXaxis()->SetLimits(0.1e-8,0.4e-8);

leg->SetTextSize(0.03);
leg->Draw();


}
