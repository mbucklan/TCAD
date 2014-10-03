#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Pulse_shape_int_graph(){		// name of file

using namespace std;

double bias=0;
int i=0;

TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);

TGraph *gr1[5];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double bias=2;bias<=10;bias+=2){		// loop to create of graph for select bias values

	TString str1 =TString::Format("%.1f V",bias);		// creates string with bias value
	TString str2 =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/1pixel/Test_CC_Simple_Pixel_bias=%.0f.txt",bias);		// does some magic, creates string with name of file
	
	gr1[i] = new TGraph(str2,"%lE %lE");		// creates graph called gr and reads file
		
	gr1[i]->SetTitle(str1);			// sets title to string
	gr1[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
	//gr1[i]->SetLineWidth(1);
	//gr1[i]->SetMarkerSize(0.9);
	//gr1[i]->SetMarkerStyle(21);
		
	mg->Add(gr1[i]);				// adds graph to multigraph
	i+=1;
	
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
mg->GetHistogram()->SetTitle("Colled Charge for 1 Pixel 100#mum Thick Sensor, Resistivity=100#Omegacm");

//mg->GetXaxis()->SetLimits(1.0e-8,11.5e-8);

TLegend *leg = new TLegend(.80,.70,.85,.87);
leg->AddEntry(gr1[0],"2V","l");
leg->AddEntry(gr1[1],"4V","l");
leg->AddEntry(gr1[2],"6V","l");
leg->AddEntry(gr1[3],"8V","l");
leg->AddEntry(gr1[4],"10V","l");

leg->SetTextSize(0.03);
leg->Draw();


}
