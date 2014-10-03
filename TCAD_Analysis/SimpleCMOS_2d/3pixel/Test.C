#include "TGraph2D.h"
#include <iostream>
#include <fstream>

void Test(){

using namespace std;

double bias = 2.0;
TString str = TString::Format("/afs/cern.ch/user/m/mbucklan/TCAD/SimpleCMOS/DepletionSimRemesh_3pixels/3pixel_extraction_bias=%.1f.txt",bias);

//for some reason cannot use ../TCAD/etc. any more need to use the who file path


TGraph2D *gr = new TGraph2D(str,"%lg %lg %lE");

cout << "Everythin is ok.";


}
