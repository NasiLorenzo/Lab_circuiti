#include "TF1.h"
#include "TFile.h"
#include "TGraphErrors.h"

Double_t parab(double* x, double* par) {
    Double_t res = par[0] * x[0] * x[0] + par[1] * x[0] + par[2];
    return res;
}

void fit_quadra(){
    TGraphErrors* quadra = new TGraphErrors("./nuovi_txt/res_quadra.txt", "%lg %lg %g");

    quadra->SetLineColor(4);
    quadra->SetMarkerColor(4);
    quadra->SetTitle("Andamento della tensione");
    quadra->GetXaxis()->SetTitle("Frequenza, Hz");
    quadra->GetYaxis()->SetTitle("Ampiezza, V");
    quadra->GetXaxis()->CenterTitle(true);
    quadra->GetXaxis()->CenterTitle(true);


    TFile *file = new TFile("quadra.root", "RECREATE");
    auto xmin{11000.};
    auto xmax{14000.};
    TF1* pb = new TF1("pb", parab, xmin, xmax,3);
    pb->SetParameters(1,-24000,1);
    quadra->Fit("pb","","",xmin,xmax);
    quadra->Draw();
    pb->Draw("SAME");
    quadra->Write();
    file->Close();
}