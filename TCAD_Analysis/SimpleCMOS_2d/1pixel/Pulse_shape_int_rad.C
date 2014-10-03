#include "TGraph2D.h"
#include "TGraph.h"
#include "TRandom3.h"
#include <iostream>
#include <fstream>


void Pulse_shape_int_rad(){		// name of file

using namespace std;

int i=0;			// used to name the TGraphs

int bins = 200;
double total_time = 1e-8;
double bin_width = total_time/bins;

double bias=200;

double raw_data[bins+1][2];			// data from TCAD, current cleaned file
double adapted_data[bins+1][2];			// data with leakage current subtracted, adapted array file
double int_data[bins+1][2];			// integrated data i.e. the charge, CC file

TCanvas *c1 = new TCanvas("c1","c1", 600, 400);
TPad *pad1 = new TPad("pad1","",0,0,1,1);
TLegend *leg = new TLegend(.70,.70,.85,.87);

TGraph *gr1[4];			// defines array to number of TGraphs

TMultiGraph *mg = new TMultiGraph();		// create multigraph

for (double fluence=13;fluence<=15;fluence+=1){		// loop to create of graph for select bias values

	TString str =TString::Format("/afs/cern.ch/work/m/mbucklan/TCAD/SimpleCMOS/DepletionSimRemesh_Particle_Rad/Rad_Current_Cleaned_bias=%.0f_Fluence=1e%.0f_200.txt",bias,fluence);		// does some magic, creates string with name of file
	
	TString str1 =TString::Format("1e%.0f n_{eq} cm^{-2}",fluence);		// creates string with bias value
	
	int a=0;			// a by b array for raw_data
	int b=0;
	
	memset(raw_data, 0, sizeof(raw_data));			//set all array elements to 0
	
	// read current data from file and store in array
	ifstream infile (str);   
 	if (infile.is_open()){		
	
       		for (int c=0;c<=bins;c++){ 
       
       			infile >> raw_data[a][b] >> raw_data[a][b+1];
			a++;
			b=0;
		
      		}
      
     	}
	
	int x=0;		// x by y array for adapted_data
	int y=0;
	memset(adapted_data, 0, sizeof(adapted_data));			//set all array elements to 0
	
	for (int e=0;e<=bins;e++){ 
       			
			adapted_data[x][0]= raw_data[x][0];
       			adapted_data[x][1]= -1*(raw_data[x][1] - raw_data[0][1]);
			x++;

      	}
	
	TString str2 =TString::Format("/afs/cern.ch/work/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/1pixel/Rad_Adapted_array_bias=%.0f_Fluence=1e%.0f_200.txt",bias,fluence);		// does some magic, creates string with name of file
	
	// write adapted_data array to text file
	ofstream adapted_file (str2);
	if (adapted_file.is_open()) {

    		for (int f = 0; f <= bins; f++) {
	
			for (int g = 0; g < 2; g++) {
		
				adapted_file << adapted_data[0+f][0+g] << " ";
			
			}
			
			adapted_file << endl;	
		
 	 	}
	
	}
	
	int n=0;			// n by m array for int_data
	int m=0;
	
	
	memset(int_data, 0, sizeof(int_data));			//set all array elements to 0

	for (int h=1;h<=bins+1;h++){		// loop that finds area under curve at increasing time points using trap rule and stores to array
		
		double sum=0;
		
		for (int d=1;d<=h-1;d++){			// loop for last term in trap rule formula, sum of midpoints
		
			sum+=adapted_data[d][1];
			
		}
		
		int_data[n][m]= adapted_data[n][0];
		m++;
		int_data[n][m]= 0.5*bin_width*(adapted_data[0][1] + adapted_data[h][1] + 2*(sum));
		n++;
		m=0;
		
		
	}
	
	TString str3 =TString::Format("/afs/cern.ch/work/m/mbucklan/TCAD_Analysis/SimpleCMOS_2d/1pixel/Rad_CC_bias=%.0f_Fluence=1e%.0f_200.txt",bias,fluence);		// does some magic, creates string with name of file
	
	// write data array to text file
	ofstream myfile (str3);
	if (myfile.is_open()) {

    		for (int k = 0; k <= bins; k++) {
	
			for (int l = 0; l < 2; l++) {
		
				myfile << int_data[0+k][0+l] << " ";
			
			}
			
			myfile << endl;	
		
 	 	}
	
	}
	
	
	if (i==4){
	
	i++;
	
	}
	
	gr1[i] = new TGraph(str3,"%lE %lE");		// creates graph and reads file
	
		
	gr1[i]->SetTitle(str1);			// sets title to string
	gr1[i]->SetLineColor(i+1);		// sets line colour, changes for each graph
		
	mg->Add(gr1[i]);			// adds graph to multigraph
	
	leg->AddEntry(gr1[i],str1,"l");
	
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
//mg->GetYaxis()->SetTitleOffset(1.2);

TString str4 =TString::Format("Colled Charge for 1 Pixel 100#mum Thick Sensor at %.0fV, Resistivity=100#Omegacm",bias);		// does some magic, creates string with name of file

mg->GetHistogram()->SetTitle(str4);
mg->SetMinimum(0);

leg->SetTextSize(0.03);
//leg->SetBorderSize(0);		// no border
leg->Draw();


}
