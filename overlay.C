#include "remolltypes.hh"
using namespace ROOT;

int overlay(TString conf, Int_t nEvents,TString particle, TString energy){

TFile f(Form("/global/scratch/rahmans/root/beampipeStudy/new/%s_%d_%s_%s.root",conf.Data(),nEvents,particle.Data(),energy.Data()));

TCanvas c("c","c",800,600);
gStyle->SetPalette(56);
c.Print(Form("%s_%d_%s_%s.pdf[", conf.Data(),nEvents,particle.Data(),energy.Data()), "pdf");
for(auto&& keyAsObj:*f.GetListOfKeys()){
   c.cd();
   auto obj=(TKey*) keyAsObj;
   TString class_name= obj->GetClassName();
   if (class_name=="TH1D"){
   	c.SetLogy();
   }else{
        c.SetLogy(0);
   	c.SetLogz();
   }
   auto hist=  f.Get(obj->GetName());
   hist->Draw("colz");
   c.Print(Form("%s_%d_%s_%s.pdf",conf.Data(),nEvents,particle.Data(), energy.Data()));
}
c.Print(Form("%s_%d_%s_%s.pdf]",conf.Data(),nEvents,particle.Data(), energy.Data()), "pdf");

return 0;
}
