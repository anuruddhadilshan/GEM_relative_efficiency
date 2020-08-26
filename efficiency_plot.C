//////////////////////////////////////////////////////////
//
//   Script to make Relative Efficiency plots vs Voltage
//
//   Author: Sean Jeffas
//
//
//   Last Modification: 8/10/2020
//
//
//////////////////////////////////////////////////////////

bool equivalent;

////// This function reads in the data points from a file and plots the points with errors ///////
TGraphErrors *make_graph(ifstream &infile){
  int run;
  double V;
  double V_eq;
  int triggered, hits;

  TGraphErrors *g = new TGraphErrors();

  int n_points = 0;

  /// Read in information about run and triggers from dat file
  while(!infile.eof()) {
    infile >> run;
    infile >> V;
    infile >> V_eq;
    infile >> hits;
    infile >> triggered;
    n_points++;

    if(equivalent) V = V_eq;

    g->SetPoint(n_points,V,hits*1.0/triggered);
    g->SetPointError(n_points,0,hits*1.0/triggered*sqrt(1.0/hits + 1.0/triggered));
  }
  

  return g;

}



///// This is the main function that makes the plot  /////////
void efficiency_plot(){

  bool save = true;    // Are we saving the resuts?
  equivalent = false;  // Use actual voltages or equivalent voltages? (only needed if different than standard divider)
  
  TString GEM = "6";      // Which GEM 
  TString dividers[] = {"90","85","100"};    // List of dividers used for plot.

  int n_dividers = sizeof(dividers)/sizeof(dividers[0]);
  
  TString Dir = "GEM_num/GEM_" + GEM + "/";    // Assumes all the data is in a directory called GEM_num
  
  TGraphErrors *g[n_dividers];

  TLegend *leg = new TLegend (0.60,0.15,0.89,0.24);
  leg->SetBorderSize(0);
 
  
  for(int i = 0; i < n_dividers; i++) {
    ifstream infile(Dir + "/divider_"+dividers[i]+"/efficiency.dat");
    g[i] = make_graph(infile);
    if(dividers[i] == "100_2") leg->AddEntry(g[i], "100% Divider 2nd Test", "p");
    else leg->AddEntry(g[i], dividers[i] + "% Divider", "p");
  }
  
  TCanvas *c1 = new TCanvas();


  // Making plots and formatting 
  for(int i = 0; i < n_dividers; i++) {
    if(i == 0){
      g[i]->Draw("AP");
      g[i]->SetMarkerStyle(8);
      g[i]->SetMarkerSize(0.8);
      if(equivalent) g[i]->SetTitle("GEM " + GEM+" Relative Efficiency;Equivalent Voltage (V);Relative Efficency");
      else g[i]->SetTitle("GEM " + GEM+" Relative Efficiency;Voltage (V);Relative Efficency");
      if(equivalent) g[i]->GetXaxis()->SetLimits(3800,4400);
      else g[i]->GetXaxis()->SetLimits(3800,4400);          //Can change axis limits as needed
      g[i]->GetYaxis()->SetRangeUser(0,1);
    }
    else{
      g[i]->SetMarkerStyle(8);
      g[i]->SetMarkerSize(0.8);
      g[i]->SetMarkerColor(i+1);
      g[i]->Draw("same P");
      
    }
  }

  TPaveText *pt1 = new TPaveText(0.50,0.22,0.89,0.42,"nbNDC");
  pt1->AddText("Relative Efficiency = #frac{# events with clusters}{# events triggered}");
  pt1->SetFillColor(0);
  pt1->Draw("same");

  leg->Draw("same");


  // Output to a plots directory 
  if(save){
    if(equivalent) c1->SaveAs("plots/GEM_"+GEM+"_efficiency_eq.png");
    else c1->SaveAs("plots/GEM_"+GEM+"_efficiency.png");
  }



}
