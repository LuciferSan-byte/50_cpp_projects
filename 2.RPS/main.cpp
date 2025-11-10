#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <unordered_set>
std::unordered_set<int> valid = {0,1,2};
int decizie, scoreP = 0, scoreC = 0, k;
void joc();
void meniu();
void clearscreen()  { std::cout << "\033[2J\033[1;1H"; }
int core(int decizie, int Calc_choice) {

    if(!valid.count(decizie)){
	std::cout << "Input invalid\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	meniu();
    }
  std::vector<std::vector<int>> joc = {
      {0, -1, 1}, // Piatra
      {1, 0, -1}, // hartie
      {-1, 1, 0}  // foarfeca
  };
  return joc[decizie][Calc_choice];
}

void remiza(bool rematch) {
  if (rematch) {
    scoreP = 0;
    scoreC = 0;
    joc();
  } else
    exit(1);
}

std::string alegere_calc(int Calc_choice) {
  std::vector<std::string> comp = {"Piatra", "Hartie", "Foarfeca"};
  return comp[Calc_choice];
}

void decizie_win_lose_draw(int Final, int Calc_choice, int &scoreP, int &scoreC) {
  if (Final == 1) {
    std::cout << "Calculatorul a Ales " << alegere_calc(Calc_choice) << "\n";
    std::cout << "Ai Castigat\n";
    scoreP++;
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    clearscreen();;
    meniu();
  }
  if (Final == 0) {
    std::cout << "Calculatorul a Ales " << alegere_calc(Calc_choice) << "\n";
    std::cout << "Egalitate\n";
     std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    clearscreen();
    meniu();
  }
  if (Final == -1) {
    std::cout << "Calculatorul a Ales " << alegere_calc(Calc_choice) << "\n";
    std::cout << "Ai Pierdut\n";
    scoreC++;
     std::this_thread::sleep_for(std::chrono::milliseconds(1200));
    clearscreen();
    meniu();
  }
}

void score(int scoreP, int scoreC, int k) {
  bool rematch;
  std::cout << "========= Scor ==========\n"
            << "Player: " << scoreP << " | | | " << "Calculator: " << scoreC;
  if ( scoreP == k) {
    clearscreen();
    std::cout << "Ai Castigat\n"
              << "Scor final\n"
              << "Player: " << scoreP << " | | | "
              << "Calculator: " << scoreC;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "\nDoriti sa mai jucati ?[1][0]: ";
    std::cin >> rematch;
    remiza(rematch);
    exit(1);
  }
  if (scoreC == k) {
    clearscreen();
    std::cout << "\nAi Pierdut \n"
              << "Scor final\n"
              << "Player:   " << scoreP << " | | | "
              << "Calculator:  " << scoreC;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "\nDoriti remiza ?[1][0]: ";
    std::cin >> rematch;
    remiza(rematch); 
    exit(1);
  }
}

void meniu() {
  score(scoreP, scoreC, k);
  std::cout << "\n-----Alege-ti-----\n";
  std::cout << "Piatra[0] Hartie[1] Foarfeca[2]\n";
  std::cout << "Input: ";
  std::cin >> decizie;
  static std::mt19937 gen{std::random_device{}()};
  std::uniform_int_distribution<int> dist(0, 2);
  int Calc_choice = dist(gen);
  int Final = core(decizie, Calc_choice);
  decizie_win_lose_draw(Final, Calc_choice, scoreP, scoreC);
}
void joc() {
  std::cout << "---Buna Ziua---\n";
  std::cout << "Pana la ce scor doriti sa jucati: ";
  std::cin >> k;
  clearscreen();
  meniu();
}
int main() {
    clearscreen();
    joc(); }



