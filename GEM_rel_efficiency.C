/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   ROOT macro to make "Relative Efficiency vs High Voltage" plots for UVA-SBS GEM layers with 4 SBS gem modules in a layer. Have to use the "rootlogon.C" file to load.
//
//   Written by Anuruddha Rathnayake after modifying the scripts "simplify.C" and "efficiency_plot.C" written by Sean Jeaffas for a single GEM setup.
//
//   Function calling method-> GEM_rel_efficiency(mod1#, mod2#, mod3#, mod4#, mod1_prodID, mod2_prodID, mod3_prodID, mod4_prodID, GEM_layer#)
//   modx#: Goes from 0 to 19 (For 5 layers in the cosmic stand)
//   modx_prodID: The production ID given at UVA while GEM fabrication
//   GEM_layer#: Goes from 0 through 10 (For 11 UVA-SBS GEM layers)
//
//   Last Modified: 09/16/2020
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GEM_rel_efficiency(int mod_0, int mod_1, int mod_2, int mod_3, int prod_id_0, int prod_id_1, int prod_id_2, int prod_id_3, int layer_n){
  
  int n_modules = 4; //Number of modules in a layer
  TString modules[n_modules];
 
  modules[0] = to_string(mod_0); modules[1] = to_string(mod_1); modules[2] = to_string(mod_2); modules[3] = to_string(mod_3);
  
  int HV_values[] = {3700, 3750, 3800, 3850, 3900, 3925, 3950, 3975, 4000, 4025, 4050, 4075, 4100}; //The set of High Voltage points we are running the test
  int n_HV_values = sizeof(HV_values)/sizeof(HV_values[0]);

  TFile *root_file[n_modules*n_HV_values];
  TH1F *NClustersPerEvent_X[n_modules*n_HV_values];
  TFile *f[n_modules*n_HV_values];
  TTree *t[n_modules*n_HV_values];
  TGraphErrors *g[n_modules];

  int nn=0;
  int hits;
  int triggers;
  int n_HV_point;
  TString layer_num_starting_from_1_convention = to_string(layer_n+1);

  //This loop will read the the number of clusters recorded and trigger events for each voltage value, for each GEM module from the analysis root files
  for(int j=0; j < n_modules; j++){
    
    ofstream outfile("module_"+modules[j]+".dat");
    
    g[j] = new TGraphErrors();
    n_HV_point = 0;
    
    for(int i=0; i < n_HV_values; i++){
      
      root_file[nn] = new TFile(Form("Tracking_run"+layer_num_starting_from_1_convention+"_%i.root",HV_values[i]),"READ");
      NClustersPerEvent_X[nn] = (TH1F*)root_file[nn]->Get("hNbClusterPerPlane_x_module_"+ modules[j]);
      hits = NClustersPerEvent_X[nn]->GetEntries();
      
      f[nn] = new TFile(Form("gem_hit_Layer"+layer_num_starting_from_1_convention+"_%iV.root",HV_values[i]),"read");
      t[nn] = (TTree*)f[nn]->Get("GEMHit");
      triggers =  t[nn]->GetEntries("evtID");
      
      g[j]->SetPoint(n_HV_point,HV_values[i],hits*1.0/triggers);
      g[j]->SetPointError(n_HV_point,0,hits*1.0/triggers*sqrt(1.0/hits + 1.0/triggers));
      n_HV_point++;

      outfile << HV_values[i] <<" "<< hits <<" "<<  triggers <<" "<< hits/triggers <<"\n";
      nn++;
    }
    outfile.close();
  }

  //Making plots and formating
  TCanvas *c1 = new TCanvas();
  c1->SetGrid();
  TString layer_num = to_string(layer_n);
  TLegend *leg = new TLegend(0.1,0.7,0.3,0.9,"SBS-UVA GEM Layer#"+layer_num);
  leg->SetFillColor(0);

  
  TString prod_id[n_modules];
  prod_id[0]=to_string(prod_id_0); prod_id[1]=to_string(prod_id_1);  prod_id[2]=to_string(prod_id_2);  prod_id[3]=to_string(prod_id_3);
  

   for(int i = 0; i < n_modules; i++) {
    if(i == 0){
      g[i]->Draw("AP");
      g[i]->SetMarkerStyle(8);
      g[i]->SetMarkerSize(1.5);
      g[i]->SetTitle("GEM Layer#"+layer_num+";Voltage (V);Relative Efficency");
      g[i]->GetXaxis()->SetLimits(3600,4200);          //Can change axis limits as needed
      g[i]->GetYaxis()->SetRangeUser(0,0.4);
    }
    else{
      g[i]->SetMarkerStyle(8);
      g[i]->SetMarkerSize(1.5);
      //g[i]->SetTitle( "Module_"+ modules[i] +" Relative Efficiency;Voltage (V);Relative Efficency");
      g[i]->SetMarkerColor(i+1);
      g[i]->Draw("same P");
      
    }
    leg->AddEntry(g[i],"GEM_"+to_string(i)+" ; Prod ID: "+prod_id[i]);
   }
   leg->Draw("Same");

   /*TPaveText *pt1 = new TPaveText(0.50,0.22,0.89,0.42,"nbNDC");
  pt1->AddText("Relative Efficiency = #frac{# events with clusters}{# events triggered}");
  pt1->SetFillColor(0);
  pt1->Draw("same");*/
   //Saving the final plot as an image file
  c1->SaveAs("Layernum"+layer_num+"_"+modules[0]+"_"+modules[1]+"_"+modules[2]+"_"+modules[3]+"test_efficiency.png");

}

