#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

void reduce_data(
    std::string const& filename = "./nuovi_txt/V_cond_1,5_auto_errors.txt",
    std::string const& ofile_name = "./nuovi_txt/V_cond_1,5_auto_errors_red.txt") {
  std::ifstream infile{filename};
  std::ofstream ofile{ofile_name};
  if (!infile) {
    std::cerr << "file cannot be opened!" << std::endl;
    return;
  }
  std::string line{};
  int i = 0;
  while (std::getline(infile, line)) {
    if (i % 5 == 0) {
      ofile << line << "\n";
    }
    i++;
  }
}

void add_errors_data(
    std::string const& filename = "./nuovi_txt/V_res_1,5_auto.txt",
    std::string const& ofile_name = "./nuovi_txt/V_res_1,5_auto_errors.txt") {
  std::ifstream infile{filename};
  std::ofstream ofile{ofile_name};
  if (!infile) {
    std::cerr << "file cannot be opened!" << std::endl;
    return;
  }
  std::string line{};
  int i = 0;
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    auto x{0.};
    auto y{0.};
    auto ey{0.};
    iss >> x >> y >> ey;
    //if (x > 10000 && x < 15000) {
      if (ey <= 0.00032) {
        ofile << x << "\t" << y << "\t" << 0.00032 << "\n";
      } else {
        ofile << line << "\n";
      }
   // }
    i++;
  }
}

void remove_lines(
    std::string const& filename = "./nuovi_txt/sin_ind_12k.txt",
    std::string const& ofile_name = "./nuovi_txt/sin_ind_12k_red.txt") {
  std::ifstream infile{filename};
  std::ofstream ofile{ofile_name};
  if (!infile) {
    std::cerr << "file cannot be opened!" << std::endl;
    return;
  }
  std::string line{};
  int i = 0;
  auto x{0.};
  while (std::getline(infile, line)) {
    std::istringstream iss(line);
    iss>>x;
    if (x > 0.0027 && x < 0.003) {
      ofile << line << "\n";
    }
    i++;
  }
}
/*int main() {
  add_errors_data("./nuovi_txt/V_ind_1,5_auto.txt",
                  "./nuovi_txt/V_ind_1,5_auto_errors.txt");
}*/