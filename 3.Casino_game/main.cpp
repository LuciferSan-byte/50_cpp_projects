#include <chrono>
#include <iostream>
#include <random>
#include <thread>
class Game {
private:
  int prize = 10000;
  int difficulty = 1;
  int current_score = 0 , final_score = 5;
  int number_range = 5;
  int incercari = 3, stand = 1;
  std::mt19937 gen{std::random_device{}()};
  void clearscreen() { std::cout << "\033[2J\033[1;1H"; }
  void SetDifficulty(int diff) { difficulty = diff; }
  int getPlayerChoice() {
    int choice;
    while (true) {
      std::cout << "Alege un nr de la 1 la " << difficulty * number_range << " ";
      if(std::cin >> choice &&choice >= 1 && choice <= difficulty * number_range){
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return choice;
	    }
      std::cout << "Invalid input\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  int getCurrScore() { return current_score; }
  int getMaxScore() { return (final_score * difficulty); }
  bool DecideWin(int Player, int Computer)const{ return  Player == Computer;}

  void roundResult(int PlayerChoice , int ComputerChoice){
    std::cout << "Calculatorul a ales: " << ComputerChoice << "\n";
    if (DecideWin(PlayerChoice, ComputerChoice)) {
      std::cout << "Ai castigat\n";
      current_score++;
    } else {
      incercari--;
      std::cout << "Ai gresit mai ai " << incercari << " incercari\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000 ));
    clearscreen();
  }

  void display_Score()  {
    std::cout << "========= Scor ==========\n";
    std::cout << "          " << current_score << "/" << final_score*difficulty << "\n";
  }
  bool isGameOver() {
	if(incercari == 0 && current_score >= (final_score * difficulty)/2) return !last_stand();	
	if(incercari == 0) return true;
	return current_score >= final_score;
    }
  int getComputerChoice() {
    std::uniform_int_distribution<int> dist(1, (difficulty * number_range));
    return dist(gen);
  }

  void endgame(){ 
	std::cout << "\n===== Joc terminat =====\n"; 
	std::cout << "Ai Ghicit " << current_score << " din " << final_score*difficulty << " numere\n";
	if(current_score == final_score){
	    std::cout << "Ai castigat " << prize*difficulty  << "$\n";
	}else std::cout << "Ai castigat multa muie\n";
	
	bool rematch;
	std::cout << "Doriti sa va mai incercati norocul inca o data? [1 = Da / 0 = Nu]"; std::cin>>rematch;
	if(rematch)
	    restart();
	else
	    std::cout << "Fraier\n";
    }
    void restart(){
	current_score = 0;
	incercari = 3;
	stand = 1;
	clearscreen();
	start();
    }
    bool last_stand(){
	if(stand == 1){
	std::cout << "Sacrificati o parte din premiu pentru o incercare in plus? [1 = Da / 2 = Nu]";
	bool decizie; std::cin >> decizie;
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if(decizie){
	    prize  /= 2;
	    incercari = 1;
	    stand--;
	    return true;
	    }
	 }else return false;
	return false;
    }
public:
    void start(){
	clearscreen();
	std::cout << "\n====Casino guessing game====\n";
	std::cout << "Selectati o dificultate [1,2,3]  ";
	int diff;
	while(!(std::cin>>diff) || diff < 1 || diff >3){
	    std::cout << "--Sangele a avut un singur job de facut--\n";
	    std::cout << "--Introdu un nr valid [1,2,3]---\n";
	    std::cin.clear();
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	SetDifficulty(diff);
	clearscreen();
	   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while(!isGameOver()){
	    display_Score();
	   int playerChoice = getPlayerChoice();
	   int computerChoice = getComputerChoice();
	   roundResult(playerChoice, computerChoice);
	}
	endgame();
    }
};
int main(){
    Game game;
    game.start();
    return 0;
}
