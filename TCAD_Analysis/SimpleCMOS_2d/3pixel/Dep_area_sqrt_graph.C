#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Dep_area_sqrt_graph(){		// name of file

using namespace std;

TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);

TGraph *graph= new TGraph("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/3pixel/3pixel_SqrtBias_Dep_pitch=20.0.txt","%lg %lg");		// creates graph called gr and reads file

// makes graph look fancy...ish
graph->SetLineColor(2);
graph->SetLineWidth(1);
graph->SetMarkerSize(0.75);
graph->SetMarkerStyle(21);
graph->SetTitle("Depletion area vs. #sqrt{bias} for a simple 3 pixel device with pitch 20#mum");
graph->GetXaxis()->SetTitle("#sqrt{Bias} (V)");
graph->GetYaxis()->SetTitle("Depletion Area (#mum^{2})");
graph->GetXaxis()->CenterTitle();
graph->GetYaxis()->CenterTitle();

pad1->Draw();
pad1->cd();
pad1->SetTicky(2);		//draws ticks and labels on right hand side y axis
pad1->SetGrid(1,1);		//sets grid lines on major ticks

graph->Draw("ACP");

}
