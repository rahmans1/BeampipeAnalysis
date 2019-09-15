#include "remolltypes.hh"
using namespace ROOT;

int multiple(TString dev,TString type,  TString particle, TString energy,  Int_t nEvents){


std::vector<TString> conf{"kryp_conf0", "kryp_conf1", "kryp_conf2", "real_conf7", "real_conf6", "real_conf0", "real_conf1", "real_conf2", "real_conf3", "real_conf4", "real_conf5", "real_conf8", "real_conf9", "ideal_conf9","hollow_conf4", "hollowkryp_conf4"};
std::vector<Int_t> col{kBlack, kBlue, kRed, kMagenta+3, kCyan+4, kYellow+2, kOrange-3,kGreen+3, kPink-9, kGreen-7, kGray+1,kRed-2, kCyan-9, kBlue+4, kOrange+10,kOrange+3};

std::map<TString,TString> pid= {{"all", "all"},{"electron", "e^{-/+}"}, {"photon","#gamma"},{"neutron", "n"}};
std::map<TString,TString> ene={{"all", ">1MeV"},{"lowene", "1-10 MeV"}, {"midene", "10-100 MeV"}, {"highene",">100 MeV"}};


std::vector<TFile*> f;
THStack h;

TCanvas c("c","c",1600,900);
gStyle->SetPalette(56);
gStyle->SetOptStat(0);
c.Print(Form("%s_%d_%s_%s.pdf[", dev.Data(),nEvents,particle.Data(),energy.Data()), "pdf");
if(type=="TH2D"){
	c.Divide(4,4);	
}else{
	c.cd();
        c.SetBottomMargin(0.13);
}

for (auto i=0;i<conf.size();i++){

f.push_back(new TFile(Form("/global/scratch/rahmans/root/beampipeStudy/first_pass/%s_%d_%s_%s.root",conf[i].Data(),nEvents,particle.Data(),energy.Data())));
if (type=="TH1D"){
if (dev.Contains("ke_")){
gPad->SetLogy();
}
auto hist=(TH1D*) f[i]->Get(dev.Data());
hist->SetMarkerColor(col[i]);
hist->SetLineColor(col[i]);
if (i==0){
h.SetTitle(hist->GetTitle());
}
h.Add(hist);
}else{
c.cd(i+1);
gPad->SetLogz();
auto hist=(TH2D*) f[i]->Get(dev.Data());
hist->Draw("colz");
hist->GetZaxis()->SetLabelSize(0.035);
TLatex label;
label.SetNDC();
label.SetTextFont(43);
label.SetTextSize(8);
label.DrawLatex(0.3,0.005, conf[i]+", PID:"+pid[particle]+", K.E.:"+ ene[energy]);
/*
TLatex plabel;
plabel.SetNDC();
plabel.SetTextFont(43);
plabel.SetTextSize(10);
plabel.DrawLatex(0.5, 0.025, Form("PID: %s, K.E.: %s", pid[particle].Data(), ene[energy].Data()));
*/
}

}

if(type=="TH1D"){
h.Draw("HISTnostack");

for(auto i=0; i<conf.size();i++){
TLatex label;
label.SetNDC();
label.SetTextFont(43);
label.SetTextSize(12);
label.SetTextColor(col[i]);
label.DrawLatex(0.08*3*(i+1)/4-0.045,0.05, conf[i].Data());
}
TLatex plabel;
plabel.SetNDC();
plabel.SetTextFont(43);
plabel.SetTextSize(13);
plabel.DrawLatex(0.5, 0.025, Form("PID: %s, K.E.: %s", pid[particle].Data(), ene[energy].Data()));
}


c.Print(Form("%s_%d_%s_%s.pdf",dev.Data(),nEvents,particle.Data(),energy.Data()));

c.Print(Form("%s_%d_%s_%s.pdf]",dev.Data(),nEvents,particle.Data(),energy.Data()), "pdf");

return 0;
}
