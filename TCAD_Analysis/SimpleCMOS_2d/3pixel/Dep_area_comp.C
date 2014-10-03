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

	TString str =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/3pixel/3pixel_SqrtBias_Dep_pitch=%.1f.txt",pitch);		// does some magic, creates string with name of file


	gr[i] = new TGraph(str,"%lg %lg");		// creates graph called gr and reads file
	
	
	TString str1 =TString::Format("%.1f #mum",pitch);		// creates string with pitch value
	gr[i]->SetTitle(str1);			// sets title to string
	gr[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
	gr[i]->SetMarkerSize(2.0);
	
	mg->Add(gr[i]);				// adds graph to multigraph
	
	i+=1;
	
	}
	


pad1->Draw();
pad1->cd();
pad1->SetTickx(1);		//draws ticks on top side x axis
pad1->SetTicky(1);		//draws ticks on right hand side y axis
pad1->SetGrid(1,1);		//sets grid lines on major ticks
gPad->Update();

	
mg->Draw("ACP");		// draws multigraph

// Make the graph look fancy...ish
mg->GetXaxis()->SetTitle("#sqrt{Bias} (V)");
mg->GetYaxis()->SetTitle("Depletion Area (#mum^{2})");
mg->GetHistogram()->SetTitle("Depletion area vs. #sqrt{bias} for a simple 3 pixel device for various pitch values");

//mg->GetXaxis()->SetLimits(0,40);
//mg->SetMinimum(-2e12);
//mg->SetMaximum(47e12);


TLegend *leg = new TLegend(.80,.77,.85,.87);
leg->AddEntry(gr[0],"15.0 #mum","l");
leg->AddEntry(gr[1],"20.0 #mum","l");
leg->SetTextSize(0.03);
leg->Draw();


}
