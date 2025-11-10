#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
std::string nume_elev;
void meniu_principal();
void sleep();
void verificare(const std::string &nume_elev){
     if(!std::filesystem::exists(nume_elev)){
    std::cerr << "Elevul nu exista";
    sleep();
    meniu_principal();
    }
}
void afisare_date_elev(const std::string &nume_elev) {
    verificare(nume_elev); 
  std::ifstream readFile(nume_elev + "/date");
  if (readFile.peek() == std::ifstream::traits_type::eof()) {
    std::cout << "Fisierul elevului este gol";
  } else {
    std::string line;
    while (std::getline(readFile, line)) {
      std::stringstream ss(line);
      std::string nume_materie;
      int credit, nota, prezente;
      if (ss >> nume_materie >> credit >> nota >> prezente)
        std::cout << nume_materie << " credite: " << credit << " nota: " << nota
                  << " prezente: " << prezente << std::endl;
    }
  }
    sleep();
    meniu_principal();
}

void adaugare_date_elev(const std::string &nume_elev) {
    verificare(nume_elev);
  std::ofstream outFile(nume_elev + "/date");
  uint16_t nr_materii;
  std::cout << "Introduce-ti nr de materii ";
  std::cin >> nr_materii;

  for (int i = 1; i <= nr_materii; i++) {
    std::string nume_matrie;
    int credit, prezente, nota;
    std::cout << "Introduce-ti numele materiei: ";
    std::cin >> nume_matrie;
    std::cout << "Introduce-ti numarul de credite: ";
    std::cin >> credit;
    std::cout << "Introduce-ti nota: ";
    std::cin >> nota;
    std::cout << "Introduce-ti nr de prezente: ";
    std::cin >> prezente;
    outFile << nume_matrie << " " << credit << " " << nota << " " << prezente
            << "\n";
  }
  outFile.close();
  sleep();
    meniu_principal();
}

void media(const std::string &nume_elev) {
    verificare(nume_elev);
  std::ifstream inFile(nume_elev + "/date");
  if (!inFile)
    std::cerr << "Eroare la deschiderea fisierului";
  std::string line;
  double sum = 0, sum_credit = 0;
  int credit, nota;
  while (std::getline(inFile, line)) {
    std::stringstream ss(line);
    std::string temp;
    if (ss >> temp >> credit >> nota) {
      sum += credit * nota;
      sum_credit += credit;
    }
  }
  std::ofstream outFile(nume_elev + "/medie");
  outFile << (double)(sum_credit);
  outFile.close();
  inFile.close();
  std::cout << (double)(sum / sum_credit);	
    sleep();
    meniu_principal();
}

void fisier_elev() {
  if (std::filesystem::exists(nume_elev)) {
    std::cout << "Elevul este deja in baza de date\n";
    meniu_principal();
  }
  if (std::filesystem::create_directory(nume_elev))
    std::cout << nume_elev << " adaugat cu succes in baza de date ";
  else {
    std::cerr << "Eraore";
    exit(1);
  }
  std::string fullPath = nume_elev + "/" + "date";
  std::string fullPath2 = nume_elev + "/medie";
  std::ofstream outFile(fullPath);
  std::ofstream outFile2(fullPath2);
  if (outFile.is_open() && outFile2.is_open()) {
    std::cout << "Fisiere create cu succes\n";
    outFile.close();
  } else{
    std::cout << "Fisierul nu a putut fi creat";
    }
    sleep();
    meniu_principal();
}

void cautare_elev(const std::string &nume_elev) {
    verificare(nume_elev);
  bool decizie = false;
  if (!std::filesystem::exists(nume_elev)) {
    std::cout << "--Nu exista elevul in baza de date--\n";
    std::cout << "--Doriti sa creati un folder pentru -" << nume_elev << "-: ";
    std::cin >> decizie;
  }
  if (std::filesystem::exists(nume_elev)) {
    std::cout << "ELevul exista in baza de date";
  }
  if (decizie){
    fisier_elev();
    }
    sleep();
    meniu_principal();
}

void sleep() { std::this_thread::sleep_for(std::chrono::milliseconds(2000)); }

void Nume_elev() {
  std::cout << "introdu nume elev";
  std::cin >> nume_elev;

  meniu_principal();
}

void meniu_principal() {
  system("clear");
  int decizie;
  std::cout << "1.Introdu numele elev \n";
  std::cout << "2.Adauga elev in baza de date\n";
  std::cout << "3.autare elev\n";
  std::cout << "4.Afisare date elev\n";
  std::cout << "5.adaugare_date_elev\n";
  std::cout << "6.Calculare medie elev\n";
  std::cout << "7.Iesire program\n\n";
  std::cout << "-Decizie- ";
  std::cin >> decizie;
  switch (decizie) {
  case 1:
    Nume_elev();
    break;
  case 2:
    fisier_elev();
    break;
  case 3:
    cautare_elev(nume_elev);
    break;
  case 4:
    afisare_date_elev(nume_elev);
    break;
  case 5:
    adaugare_date_elev(nume_elev);
    break;
  case 6:
    media(nume_elev);
    break;
  case 7:
    exit(1);
    break;
  default:
    std::cout << "Numar invalid";
    meniu_principal();
  }
}
int main() { meniu_principal(); }
