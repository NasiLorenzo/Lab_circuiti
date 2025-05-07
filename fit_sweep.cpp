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

void fit(TString fname = "V_ind_sweep_noresistenza_0,1Vpp.txt",
         Double_t f0 = 12780, Double_t V0 = 0.05, Double_t R = 290,
         Double_t L = 0.047, Double_t C = 3.3E-9) {
  TFile *file = new TFile("data.root", "RECREATE");
  TF1 *resonance = new TF1("myfunc", ris_sin_cond, 200, 24000, 4);
  resonance->SetParameter(0, V0);
  resonance->SetParameter(1, R);
  resonance->SetParameter(2, L);
  resonance->SetParameter(3, C);
  resonance->SetParName(0, "Ampiezza sorgente");
  resonance->SetParName(1, "Resistenza");
  resonance->SetParName(2, "Induttanza");
  resonance->SetParName(3, "Capacità");
  // resonance->FixParameter(0,0.05);

  TGraphErrors *data = new TGraphErrors(fname, "%lg %lg %lg");

  data->Fit("myfunc", "R");
  data->Draw("AP");
  data->SetLineColor(4);
  data->SetMarkerColor(4);
  resonance->Draw("same");
  data->SetTitle("Figura di diffrazione");
  data->GetXaxis()->SetTitle("Posizione, m");
  data->GetYaxis()->SetTitle("Int. luminosa, unit. arb.");
  data->GetXaxis()->CenterTitle(true);
  data->GetXaxis()->CenterTitle(true);
  TLegend *leg = new TLegend(.6, .7, .9, .9);
  leg->SetTextSize(0.04);
  leg->SetBorderSize(0);  // no border for legend
  leg->SetFillColor(0);   // fill color is white
  leg->AddEntry(data, "L= 1.088 m, d=0.101 mm", "p");
  leg->AddEntry(resonance, "fit", "l");
  leg->Draw();
  data->Write();
  file->Close();
  std::cout << "La f di risonanza vale: "
            << TMath::Sqrt(1 / (2 * TMath::Pi() * resonance->GetParameter(2) *
                                resonance->GetParameter(3)))
            << "\n";
}

void my_data(TString fname = "V_ind_sweep_noresistenza_0,1Vpp.txt") {
  TGraphErrors *data = new TGraphErrors(fname, "%lg %lg %lg");
  data->Draw("AP");
  data->SetLineColor(4);
  data->SetMarkerColor(4);
  data->SetTitle("Figura di diffrazione");
  data->GetXaxis()->SetTitle("Posizione, m");
  data->GetYaxis()->SetTitle("Int. luminosa, unit. arb.");
  data->GetXaxis()->CenterTitle(true);
  data->GetXaxis()->CenterTitle(true);
}