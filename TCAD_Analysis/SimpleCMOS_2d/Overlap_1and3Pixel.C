#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Overlap_1and3Pixel(){		// name of file

using namespace std;

int i=0;			// used to name the TGraphs
int j=0;

TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);
TLegend *leg = new TLegend(.80,.70,.85,.87);

TGraph *gr[15];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double bias=10;bias<=60;bias+=10){		// loop to create of graph for select bias values

	TString str =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/1pixel/CC_Simple_Pixel_bias=%.0f_500.txt",bias);		// does some magic, creates string with name of file
	
	if (i==4){
	
	i++;
	
	}

	gr[i] = new TGraph(str,"%lE %lE");		// creates graph called gr and reads file
	
	TString str1 =TString::Format("1 pixel %.0fV",bias);		// creates string with bias value
	gr[i]->SetTitle(str1);			// sets title to string
	gr[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
	gr[i]->SetLineWidth(1);

	mg->Add(gr[i]);				// adds graph to multigraph
	
	leg->AddEntry(gr[i],str1,"l");
	
	i++;
	
	
}

for (double bias=10;bias<=60;bias+=10){		// loop to create of graph for select bias values

	TString str3 =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/3pixel/CC_3pixel_bias=%.1f_200.txt",bias);		// does some magic, creates string with name of file
	
	if (j==4){
	
	j++;
	
	}

	gr[i] = new TGraph(str3,"%lE %lE");		// creates graph called gr and reads file
	
	TString str4 =TString::Format("3 pixel %.0fV",bias);		// creates string with bias value
	gr[i]->SetTitle(str4);			// sets title to string
	gr[i]->SetLineColor(j+1);		// sets line colour, changes for each graph
	gr[i]->SetLineWidth(1);
	gr[i]->SetLineStyle(2);
	
	mg->Add(gr[i]);				// adds graph to multigraph
	
	leg->AddEntry(gr[i],str4,"l");
	
	i++;
	j++;
	
}

pad1->Draw();
pad1->cd();
pad1->SetTickx(1);		//draws ticks on top side x axis
pad1->SetTicky(1);		//draws ticks on right hand side y axis

gPad->Update();

mg->Draw("AC");		// draws graph

// Make the graph look fancy...ish
mg->GetXaxis()->SetTitle("Time (s)");
mg->GetYaxis()->SetTitle("Collected Charge (C)");
mg->GetHistogram()->SetTitle("Collected Charge for 1 and 3 Pixel 100#mum Thick Sensor, Resistivity=100#Omegacm");
mg->SetMinimum(0);

//mg->GetXaxis()->SetLimits(1.0e-8,11.5e-8);

leg->SetTextSize(0.03);
leg->SetBorderSize(0);		// no border
leg->Draw();


}
