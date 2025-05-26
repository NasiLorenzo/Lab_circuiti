#include "TCanvas.h"
#include "TF1.h"
#include "TGraphErrors.h"

Double_t phase(double* x, double* par) {
  Double_t res = par[4] * TMath::ATan((1 / (2 * TMath::Pi() * x[0] * par[0]) -
                                       2 * TMath::Pi() * x[0] * par[1]) /
                                      par[2]) +
                 par[3];
  return res;
}

Double_t phase_notan(double* x, double* par) {
  Double_t res = par[4] * ((1 / (2 * TMath::Pi() * x[0] * par[0]) -
                            2 * TMath::Pi() * x[0] * par[1]) /
                           par[2]) +
                 par[3];
  return res;
}

void fit_phase(TString fname_ind = "./nuovi_txt/phase_ind.txt",
               TString fname_res = "./nuovi_txt/phase_res.txt",
               TString fname_cond = "./nuovi_txt/phase_cond.txt") {
  TGraphErrors* phase_ind = new TGraphErrors(fname_ind, "%lg %lg %g");
  TGraphErrors* phase_res = new TGraphErrors(fname_res, "%lg %lg %g");
  TGraphErrors* phase_cond = new TGraphErrors(fname_cond, "%lg %lg %g");
  auto xmin{2500.};
  auto xmax{23000.};
  TF1* atan = new TF1("phase", phase, xmin, xmax, 5);
  atan->SetParNames("Capacità", "Induttanza", "Resistenza", "offset");
  atan->SetParameters(3.3E-9, 0.047, 620, TMath::Pi() / 2, 1);
  TCanvas* canv = new TCanvas("c1", "Fasi relative", 700, 500);
  canv->Divide(2, 2);
  canv->cd(1);
  phase_ind->Fit("phase", "RM","",xmin,xmax);
  atan->SetParameter(0, 3.3E-9);
  atan->SetParameter(1, 0.047);
  atan->SetParameter(2, 620);
  phase_ind->Draw();
  canv->cd(2);
  atan->SetParameter(3, 0);
  phase_res->Fit("phase", "RS","",xmin,xmax);
  phase_res->Draw();
  canv->cd(3);
  phase_cond->Fit("phase","","",xmin,xmax);
  phase_cond->Draw();
}

void fit_quadra(TString fname_res="./nuovi_txt/res_quadra.txt"){
    TGraphErrors* res_quadra=new TGraphErrors(fname_res,"%lg %lg %lg");
    res_quadra->Draw();
}

