#include "TGraph2D.h"
#include "TRandom3.h"

void TGraph_Example(){		// name of file


TGraph2D *gr= new TGraph2D("../TCAD/SimpleCMOS/DepletionSimRemesh/extraction_node_209.txt","%lg %lg %lE");		// creates graph called gr and reads file
TRandom3 *rando = new TRandom3();



gr->Draw("colz");	// draws 2D graph



int in_dep = 0;		// no. of throws inside the depletion zone
int total  = 0;		// total of number of throws


for (int i=0;i<100000;i++){


	double x= rando->Uniform(0,100.);		// make a throw
	double y= rando->Uniform(0,25.);
	
	double econc= gr->Interpolate(x,y);		// electron concentration
	total+=1;
	
	if(econc<1e13){
	
		in_dep+=1;				// inside the depletion region if electron concentration is less than 1e13
	};
	
	

};














cout << 100*double(in_dep)/total << " % of depleted volume" << endl;		// finds ratio of hits to tot. no. of throws, prints result













}
