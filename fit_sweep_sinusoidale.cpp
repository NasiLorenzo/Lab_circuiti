#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TMath.h"
Double_t ris_sin_cond(double *x, double *par) {
  Double_t res =
      par[0] /
      (TMath::Sqrt(par[1] * par[1] +
                   TMath::Power(2. * TMath::Pi() * x[0] * par[2] -
                                    1 / (par[3] * 2. * TMath::Pi() * x[0]),
                                2)) *
       2. * TMath::Pi() * x[0] * par[3]);
  return res;
}

Double_t ris_sin_res(double *x, double *par) {
  Double_t res =
      par[0] * par[1] /
      (TMath::Sqrt(par[1] * par[1] +
                   TMath::Power(2. * TMath::Pi() * x[0] * par[2] -
                                    1 / (par[3] * 2. * TMath::Pi() * x[0]),
                                2)));
  return res;
}

Double_t ris_sin_ind(double *x, double *par) {
  Double_t res =
      par[0] * par[2] * 2 * TMath::Pi() * x[0] /
      (TMath::Sqrt(par[1] * par[1] +
                   TMath::Power(2. * TMath::Pi() * x[0] * par[2] -
                                    1 / (par[3] * 2. * TMath::Pi() * x[0]),
                                2)));
  return res;
}

void fit(TString fname_cond = "./nuovi_txt/V_cond_1,5_auto.txt",
         TString fname_res = "./nuovi_txt/V_res_1,5_auto.txt",
         TString fname_ind = "./nuovi_txt/V_ind_1,5_auto.txt",
         Double_t f0 = 12780, Double_t V0 = 0.05, Double_t R = 600,
         Double_t L = 0.047, Double_t C = 3.3E-9) {
  TFile *file = new TFile("data_cond.root", "RECREATE");
  TCanvas *canv = new TCanvas("canv", "Risonanze sinusoidale", 700, 600);
  canv->Divide(2, 2);
  TF1 *res_cond = new TF1("myfunc1", ris_sin_cond, 200, 24000, 4);
  TF1 *res_ind = new TF1("myfunc2", ris_sin_ind, 200, 24000, 4);
  TF1 *res_res = new TF1("myfunc3", ris_sin_res, 200, 24000, 4);
  res_cond->SetParameter(0, V0);
  res_cond->SetParameter(1, R);
  res_cond->SetParameter(2, L);
  res_cond->SetParameter(3, C);
  res_cond->SetParName(0, "Ampiezza sorgente");
  res_cond->SetParName(1, "Resistenza");
  res_cond->SetParName(2, "Induttanza");
  res_cond->SetParName(3, "Capacità");
  // res_cond->FixParameter(0,0.75);

  res_ind->SetParameter(0, V0);
  res_ind->SetParameter(1, R);
  res_ind->SetParameter(2, L);
  res_ind->SetParameter(3, C);
  res_ind->SetParName(0, "Ampiezza sorgente");
  res_ind->SetParName(1, "Resistenza");
  res_ind->SetParName(2, "Induttanza");
  res_ind->SetParName(3, "Capacità");
  // res_ind->FixParameter(0,0.75);

  res_res->SetParameter(0, V0);
  res_res->SetParameter(1, R);
  res_res->SetParameter(2, L);
  res_res->SetParameter(3, C);
  res_res->SetParName(0, "Ampiezza sorgente");
  res_res->SetParName(1, "Resistenza");
  res_res->SetParName(2, "Induttanza");
  res_res->SetParName(3, "Capacità");
  // res_res->FixParameter(0,0.75);

  TGraphErrors *data_cond = new TGraphErrors(fname_cond, "%lg %lg %lg");
  TGraphErrors *data_res = new TGraphErrors(fname_res, "%lg %lg %lg");
  TGraphErrors *data_ind = new TGraphErrors(fname_ind, "%lg %lg %lg");

  canv->cd(1);
  data_cond->Fit("myfunc1", "R");
  data_cond->Draw("AP");
  data_cond->SetLineColor(4);
  data_cond->SetMarkerColor(4);
  res_cond->Draw("same");
  data_cond->SetTitle("Condensatore");
  data_cond->GetXaxis()->SetTitle("Frequenza, Hz");
  data_cond->GetYaxis()->SetTitle("Ampiezza, V");
  data_cond->GetXaxis()->CenterTitle(true);
  data_cond->GetXaxis()->CenterTitle(true);

  canv->cd(2);
  data_ind->Fit("myfunc2", "R");
  data_ind->Draw("AP");
  data_ind->SetLineColor(4);
  data_ind->SetMarkerColor(4);
  data_ind->SetTitle("Induttore");
  data_ind->GetXaxis()->SetTitle("Frequenza, Hz");
  data_ind->GetYaxis()->SetTitle("Ampiezza, V");
  data_ind->GetXaxis()->CenterTitle(true);
  data_ind->GetXaxis()->CenterTitle(true);

  res_ind->Draw("same");

  data_res->SetTitle("Resistore");
  data_res->GetXaxis()->SetTitle("Frequenza, Hz");
  data_res->GetYaxis()->SetTitle("Ampiezza, V");
  canv->cd(3);
  data_res->Fit("myfunc3", "R");
  data_res->Draw("AP");
  data_res->SetLineColor(4);
  data_res->SetMarkerColor(4);
  res_res->Draw("same");
  data_cond->Write();
  file->Close();
  std::cout << "La f di risonanza vale: "
            << 1. /( 2. * TMath::Pi()) *
                   TMath::Sqrt(1 / (res_cond->GetParameter(2) *
                                    res_cond->GetParameter(3)))
            << "\n";
}