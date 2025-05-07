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

void fit(TString fname_cond = "V_cond_sin_sweep_1.5Vpp_errori_stand.txt",
         TString fname_res = "V_res_sweep_sin_1.5Vpp_errori_stand.txt",
         TString fname_ind = "V_ind_sweep_1.5Vpp_errori_stand.txt",
         Double_t f0 = 12780, Double_t V0 = 0.05, Double_t R = 600,
         Double_t L = 0.047, Double_t C = 3.3E-9) {
  TFile *file = new TFile("data_cond.root", "RECREATE");
  TCanvas *canv = new TCanvas("canv", "Risonanze sinusoidale", 700, 600);
  canv->Divide(2,2);
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
  res_cond->FixParameter(0,0.75);

  res_ind->SetParameter(0, V0);
  res_ind->SetParameter(1, R);
  res_ind->SetParameter(2, L);
  res_ind->SetParameter(3, C);
  res_ind->SetParName(0, "Ampiezza sorgente");
  res_ind->SetParName(1, "Resistenza");
  res_ind->SetParName(2, "Induttanza");
  res_ind->SetParName(3, "Capacità");
  res_ind->FixParameter(0,0.75);

  res_res->SetParameter(0, V0);
  res_res->SetParameter(1, R);
  res_res->SetParameter(2, L);
  res_res->SetParameter(3, C);
  res_res->SetParName(0, "Ampiezza sorgente");
  res_res->SetParName(1, "Resistenza");
  res_res->SetParName(2, "Induttanza");
  res_res->SetParName(3, "Capacità");
  res_res->FixParameter(0,0.75);

  TGraphErrors *data_cond = new TGraphErrors(fname_cond, "%lg %lg %lg");
  TGraphErrors *data_res = new TGraphErrors(fname_res, "%lg %lg %lg");
  TGraphErrors *data_ind = new TGraphErrors(fname_ind, "%lg %lg %lg");
  
  canv->cd(1);
  data_cond->Fit("myfunc1", "R");
  data_cond->Draw("AP");
  data_cond->SetLineColor(4);
  data_cond->SetMarkerColor(4);
  res_cond->Draw("same");
  data_cond->SetTitle("Figura di diffrazione");
  data_cond->GetXaxis()->SetTitle("Posizione, m");
  data_cond->GetYaxis()->SetTitle("Int. luminosa, unit. arb.");
  data_cond->GetXaxis()->CenterTitle(true);
  data_cond->GetXaxis()->CenterTitle(true);
  
  canv->cd(2);
  data_ind->Fit("myfunc2", "R");
  data_ind->Draw("AP");
  data_ind->SetLineColor(4);
  data_ind->SetMarkerColor(4);
  res_ind->Draw("same");
  data_res->GetXaxis()->SetTitle("frequenza, Hz");
  data_res->GetYaxis()->SetTitle("Ampiezza, V");
  
  canv->cd(3);
  data_res->Fit("myfunc3", "R");
  data_res->Draw("AP");
  data_res->SetLineColor(4);
  data_res->SetMarkerColor(4);
  res_res->Draw("same");
  TLegend *leg = new TLegend(.6, .7, .9, .9);
  leg->SetTextSize(0.04);
  leg->SetBorderSize(0);  // no border for legend
  leg->SetFillColor(0);   // fill color is white
  leg->AddEntry(data_cond, "L= 1.088 m, d=0.101 mm", "p");
  leg->AddEntry(res_cond, "fit", "l");
  leg->Draw();
  data_cond->Write();
  file->Close();
  std::cout << "La f di risonanza vale: "
            << TMath::Sqrt(1 / (2 * TMath::Pi() * res_cond->GetParameter(2) *
                                res_cond->GetParameter(3)))
            << "\n";
}

void my_data(TString fname = "V_ind_sweep_noresistenza_0,1Vpp.txt") {
  TGraphErrors *data_cond = new TGraphErrors(fname, "%lg %lg %lg");
  data_cond->Draw("AP");
  data_cond->SetLineColor(4);
  data_cond->SetMarkerColor(4);
  data_cond->SetTitle("Figura di diffrazione");
  data_cond->GetXaxis()->SetTitle("Posizione, m");
  data_cond->GetYaxis()->SetTitle("Int. luminosa, unit. arb.");
  data_cond->GetXaxis()->CenterTitle(true);
  data_cond->GetXaxis()->CenterTitle(true);
}