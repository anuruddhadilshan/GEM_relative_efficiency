/// For runs with one GEM this takes the Tracking root file makes a simplified
/// file with the important plots.
///
/// It also reads out the number of triggers and hits to be used to make 
/// efficiency plots


void simplify(int run){

  TFile *root_file = new TFile(Form("Tracking_run3_%i.root",run),"READ");
  /*TFile *root_output = new TFile(Form("Simplified_run%i.root",run),"recreate");
  
  TH1F *HitDistX = (TH1F*)root_file->Get("hHitDistX_0");
  TH1F *HitDistY = (TH1F*)root_file->Get("hHitDistY_0");
  TH1F *ClusterDistX = (TH1F*)root_file->Get("hClusterDistX_0");
  TH1F *ClusterDistY = (TH1F*)root_file->Get("hClusterDistY_0");
  TH2F *ClusterDist = (TH2F*)root_file->Get("hhClusterDist_0");
  
  TH1F *ClusterADCx = (TH1F*)root_file->Get("hClusterAdcDistX_0");
  TH1F *ClusterADCy = (TH1F*)root_file->Get("hClusterAdcDistY_0");
  TH1F *StripsADCx = (TH1F*)root_file->Get("hStripsADCdistX_module_0");
  TH1F *StripsADCy = (TH1F*)root_file->Get("hStripsADCdistY_module_0");
  
  TH2F *ChargeSharing = (TH2F*)root_file->Get("hhClusterChargeRatio_0");
  
  TH1F *ClusterSizeX = (TH1F*)root_file->Get("hClusterSize_x_module_0");
  TH1F *ClusterSizeY = (TH1F*)root_file->Get("hClusterSize_y_module_0");*/
  
  TH1F *NClustersPerEvent_X = (TH1F*)root_file->Get("hNbClusterPerPlane_x_module_0");
  /*TH1F *NClustersPerEvent_Y = (TH1F*)root_file->Get("hNbClusterPerPlane_y_module_0");


  ClusterADCx->GetXaxis()->SetRangeUser(0,3000);
  ClusterADCy->GetXaxis()->SetRangeUser(0,3000);

  StripsADCx->GetXaxis()->SetRangeUser(0,600);
  StripsADCy->GetXaxis()->SetRangeUser(0,600);

  
  NClustersPerEvent_X->SetTitle("# of Clusters per Event X");
  NClustersPerEvent_Y->SetTitle("# of Clusters per Event Y");

  HitDistX->Write("HitDistX");
  HitDistY->Write("HitDistY");
  ClusterDistX->Write("ClusterDistX");
  ClusterDistY->Write("ClusterDistY");

  ClusterDist->Write("ClusterDist");
  ClusterADCx->Write("ClusterADC_X");
  ClusterADCy->Write("ClusterADC_Y");
  StripsADCx->Write("StripsADC_X");
  StripsADCy->Write("StripsADC_Y");
  
  ChargeSharing->Write("ClusterChargeSharing");
  
  ClusterSizeX->Write("ClusterSizeX");
  ClusterSizeY->Write("ClusterSizeY");
  
  NClustersPerEvent_X->Write("NClustersPerEvent_X");
  NClustersPerEvent_Y->Write("NClustersPerEvent_Y");

  

  root_output->Write();*/


  TFile *f = new TFile(Form("gem_hit_0%i_00.root",run),"read");
  TTree *t = (TTree*)f->Get("GEMHit");

  cout<<"Good events in run :"<<NClustersPerEvent_X->GetEntries()<<endl;
  cout<<"Triggers in run: "<<t->GetMaximum("evtID")<<endl;

}
