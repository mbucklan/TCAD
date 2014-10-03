#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>

void Pulse_shape_int(){		// name of file

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

	gr[i] = new TGraph(str,"%lE %lE");		// creates graph called gr and reads file
	
	TString str1 =TString::Format("%.1f V",bias);		// creates string with bias value
	
	double time=0;
	
	int n=0;			// n by m array
	int m=0;
	
	memset(data, 0, sizeof(data));			//set all array elements to 0

	for (double x=0;x<=499;x++){
		
		//write result to array
		data[n][m]= time;
		m++;
		data[n][m]= gr[i]->Integral(0, x);
		n++;
		m=0;
		
		time+=2e-11;
		
	}
	
	
	TString str2 =TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/1pixel/CC_Simple_Pixel_bias=%.0f.txt",bias);		// does some magic, creates string with name of file
	
	// write array to text file
	ofstream myfile (str2);
	if (myfile.is_open()) {

    		for (int k = 0; k < 499; k++) {
	
			for (int l = 0; l < 2; l++) {
		
				myfile << data[0+k][0+l] << " ";
			
			}
			
			myfile << endl;	
		
 	 	}
	
	}
	
	
	gr1[i] = new TGraph(str2,"%lE %lE");		// creates graph called gr and reads file
	
		
	gr1[i]->SetTitle(str1);			// sets title to string
	gr1[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
	//gr1[i]->SetLineWidth(1);
	//gr1[i]->SetMarkerSize(0.9);
	//gr1[i]->SetMarkerStyle(21);
		
	mg->Add(gr1[i]);				// adds graph to multigraph
	
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
