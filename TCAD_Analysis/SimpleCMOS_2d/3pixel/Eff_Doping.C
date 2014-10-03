#include "TGraph.h"
#include <iostream>
#include <fstream>

void Eff_Doping(){		// name of file

using namespace std;

double bias=30;
int i=0;			// used to name the TGraphs

TCanvas *c1 = new TCanvas("c1","c1",600,400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);
TLegend *leg = new TLegend(.80,.70,.85,.87);

TGraph *gr[4];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double fluence=13;fluence<=15;fluence+=1){		// loop to create multigraph for select bias values

	TString str =TString::Format("/afs/cern.ch/work/m/mbucklan/TCAD/SimpleCMOS/DepletionSimRemesh_3pixels_Rad/Neffextraction_3pixel_yCut_bias=%.1f_pitch=15.0_Fluence=1e+%.0f.txt",bias,fluence);		// does some magic, creates string with name of file
		
	if (i==4){
	
	i++;
	
	}

	gr[i] = new TGraph(str,"%lg %lg");		// creates graph called gr and reads file
	
	
	TString str1 =TString::Format("1e%.0f n_{eq} cm^{-2}",fluence);		// creates string with bias value
	
	gr[i]->SetTitle(str1);			// sets title to string
	gr[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
	
	mg->Add(gr[i]);				// adds graph to multigraph
	leg->AddEntry(gr[i],str1,"l");
	
	i++;
	
}
	
pad1->Draw();
pad1->cd();
pad1->SetTickx(1);		//draws ticks on top side x axis
pad1->SetTicky(1);		//draws ticks on right hand side y axis

gPad->Update();
	
mg->Draw("AL");		// draws multigraph

// Make the graph look fancy...ish
mg->GetXaxis()->SetTitle("Depth (#mum)");
mg->GetYaxis()->SetTitle("Effective Doping Concentration (cm^{-3})");

TString str2 =TString::Format("Effective Doping Concentration for 3 Pixel 100#mum Thick Sensor at %.0fV, Resistivity=100#Omegacm",bias);		// does some magic, creates string with name of file

mg->GetHistogram()->SetTitle(str2);

mg->SetMinimum(-2e12);

leg->SetTextSize(0.03);
leg->Draw();

}
