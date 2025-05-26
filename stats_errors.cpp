#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "TGraphErrors.h"
#include "TH1F.h"
#include "TString.h"

void statistica(std::string const& filename = "./nuovi_txt/stats_V.txt") {
  std::vector<double> data{};
  Double_t xmin = 4.915;
  Double_t xmax = 4.925;
  Double_t strumentale = 0.000300;
  Int_t nbins = (xmax - xmin) / strumentale;
  TH1F* incertezze_V =
      new TH1F("histo1", "Incertezza statistica voltaggi", nbins, xmin, xmax);
  std::ifstream infile{filename};
  if (!infile) {
    std::cerr << "file cannot be opened!" << std::endl;
    return;
  }
  std::string line{};
  double x{};
  double x_last{};
  double min{1000};
  auto diff{0.};
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    iss >> x;
    diff = abs(x_last - x);
    if (diff < min && diff != 0) {
      min = diff;
    }
    x_last = x;
    incertezze_V->Fill(x);
  }
  incertezze_V->Draw();
  std::cout<<"La mean vale "<<incertezze_V->GetMean()<<"\n";
  std::cout << "La stddev vale " << incertezze_V->GetStdDev() << "\n";
  std::cout << "La minima differenza vale: " << min << "\n";
}

void statistica_amp_cond(
    std::string const& filename = "./nuovi_txt/stats_amp_1.txt") {
  Double_t xmin = 1.194;
  Double_t xmax = 1.195;
  Int_t nbins = 20;
  TH1F* incertezze_amp =
      new TH1F("histo1", "Incertezza statistica voltaggi", nbins, xmin, xmax);
  std::ifstream infile{filename};
  if (!infile) {
    std::cerr << "file cannot be opened!" << std::endl;
    return;
  }
  std::string line{};
  double x{};
  double x_last{};
  double min{1000};
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    iss >> x;
    if ((abs(x_last - x) < min) && abs(x_last - x) != 0) {
      min = abs(x_last - x);
    }
    x_last = x;
    incertezze_amp->Fill(x);
  }
  incertezze_amp->Draw();
  std::cout<<"La mean vale "<<incertezze_amp->GetMean()<<"\n";
  std::cout << "La stddev vale " << incertezze_amp->GetStdDev() << "\n";
  std::cout << "stddev/mean: "
            << incertezze_amp->GetStdDev() / incertezze_amp->GetMean() << "\n"
            << "La minima differenza vale: " << min << "\n";
}

void statistica_amp_res(
    std::string const& filename = "./nuovi_txt/stats_amp_2.txt") {
  Double_t xmin = 0.0652;
  Double_t xmax = 0.0654;
  Int_t nbins = 100;
  TH1F* incertezze_amp =
      new TH1F("histo1", "Incertezza statistica voltaggi", nbins, xmin, xmax);
  std::ifstream infile{filename};
  if (!infile) {
    std::cerr << "file cannot be opened!" << std::endl;
    return;
  }
  std::string line{};
  double x{};
  double x_last{};
  double min{1000};
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    iss >> x;
    if ((abs(x_last - x) < min) && abs(x_last - x) != 0) {
      min = abs(x_last - x);
    }
    x_last = x;
    incertezze_amp->Fill(x);
  }
  incertezze_amp->Draw();
  std::cout<<"La mean vale "<<incertezze_amp->GetMean()<<"\n";
  std::cout << "La stddev vale " << incertezze_amp->GetStdDev() << "\n";
  std::cout << "stddev/mean: "
            << incertezze_amp->GetStdDev() / incertezze_amp->GetMean() << "\n"
            << "La minima differenza vale: " << min << "\n";
}

void statistica_amp_ind(
    std::string const& filename = "./nuovi_txt/stats_amp_3.txt") {
  Double_t xmin = 0.468;
  Double_t xmax = 0.4689;
  Int_t nbins = 20;
  TH1F* incertezze_amp =
      new TH1F("histo1", "Incertezza statistica voltaggi", nbins, xmin, xmax);
  std::ifstream infile{filename};
  if (!infile) {
    std::cerr << "file cannot be opened!" << std::endl;
    return;
  }
  std::string line{};
  double x{};
  double x_last{};
  double min{1000};
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    iss >> x;
    if ((abs(x_last - x) < min) && abs(x_last - x) != 0) {
      min = abs(x_last - x);
    }
    x_last = x;
    incertezze_amp->Fill(x);
  }
  incertezze_amp->Draw();
  std::cout<<"La mean vale "<<incertezze_amp->GetMean()<<"\n";
  std::cout << "La stddev vale " << incertezze_amp->GetStdDev() << "\n";
  std::cout << "stddev/mean: "
            << incertezze_amp->GetStdDev() / incertezze_amp->GetMean() << "\n"
            << "La minima differenza vale: " << min << "\n";
}

void errors_correlation(){
  const Int_t n=3;
  Double_t x[n]={1.19449,0.0652983,0.468322};
  Double_t y[n]={0.000209694,2.89812E-05,0.000117844};
  TGraphErrors* errors = new TGraphErrors(n,x,y);
  errors->Fit("pol1");
  errors->Draw();
}

void statistica_amp_phase(
    std::string const& filename = "./nuovi_txt/stats_amp_phase.txt") {
  Double_t xmin = 1.38;
  Double_t xmax = 1.40;
  Int_t nbins = 20;
  TH1F* incertezze_amp =
      new TH1F("histo1", "Incertezza statistica voltaggi", nbins, xmin, xmax);
  std::ifstream infile{filename};
  if (!infile) {
    std::cerr << "file cannot be opened!" << std::endl;
    return;
  }
  std::string line{};
  double x{};
  double x_last{};
  double min{1000};
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    iss >> x;
    if ((abs(x_last - x) < min) && abs(x_last - x) != 0) {
      min = abs(x_last - x);
    }
    x_last = x;
    incertezze_amp->Fill(x);
  }
  incertezze_amp->Draw();
  std::cout<<"La mean vale "<<incertezze_amp->GetMean()<<"\n";
  std::cout << "La stddev vale " << incertezze_amp->GetStdDev() << "\n";
  std::cout << "stddev/mean: "
            << incertezze_amp->GetStdDev() / incertezze_amp->GetMean() << "\n"
            << "La minima differenza vale: " << min << "\n";
}

void stats_offset(TString fname="./nuovi_txt/phase_offset_ch1.txt"){
  TGraphErrors* syst = new TGraphErrors(fname,"%lg %lg %lg");
  syst->Fit("pol1");
  syst->Draw();
}