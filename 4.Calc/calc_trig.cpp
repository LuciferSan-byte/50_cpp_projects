#include "includes.hpp"
#include "calc_trig.hpp"

Calc_trig::Calc_trig(){
    actions = { 
	[this]() -> std::any{ expresie_func(); return{};}, 
	[this]() -> std::any{ interfata_trig(); return{};}, 
	[this]() -> std::any{ undo_istoric(); return {};},
	[this]() -> std::any{ redo_istoric(); return{};}, 
	[this]() -> std::any{exit(1); return{};} };

}
bool Calc_trig::verificare_functie(const std::string & tip_functie_trig, std::string &functie_trig){
   size_t j = 0;
    for(char c : tip_functie_trig){
	if(c == functie_trig[j]){
	    j++;
	    if(j == tip_functie_trig.size()) return true;
	}
      }
    return false;
 }

void Calc_trig::evaluare_expresie_trig(){
    std::cout << "Introdu expresie: "; std::getline(std::cin, expresie);
    elimina_spatii_expresie();
    rezultat_expresie = calculare_expresie();
    std::string trig_istoric;
    trig_istoric = tip_functie_trig + "(" + expresie + ")";
    Adaugare_in_istoric(trig_istoric);
}

std::optional<double> Calc_trig::calc_functie_trig(std::string tip_functie_trig){
    
    if(tip_functie_trig == "sin") return std::sin(rezultat_expresie);
    if(tip_functie_trig == "cos") return std::cos(rezultat_expresie);
    if(tip_functie_trig == "tan"){
	double cos_val = std::cos(rezultat_expresie);
	if(std::abs(cos_val) < 1e-12) return std::nullopt;
	return std::tan(rezultat_expresie);
    }
    if(tip_functie_trig == "ctg"){
	double sin_val = std::sin(rezultat_expresie);
	if(std::abs(sin_val) < 1e-12) return std::nullopt;
	return 1.0/std::tan(rezultat_expresie); 
    }
    std::cout << "Expresie Invalida\n"; return std::nullopt;

}

void Calc_trig::verificare_functii_permise(bool &verificare_trig){
    for(std::string s : functii_permise) 
	if(verificare_functie(tip_functie_trig, s) == true ){
	    tip_functie_trig = s;
	    verificare_trig = true; 
	    break;
	}
}

void Calc_trig::interfata_trig(){
    std::cout << "Introdu functia trig:"; std::getline(std::cin,tip_functie_trig);
    bool verificare_trig = false;
   
    verificare_functii_permise(verificare_trig);
    while(verificare_trig == false){
	std::cout << "Input invalid\n";
	std::cout << "Reintrodu functia "; std::getline(std::cin, tip_functie_trig);
	verificare_functii_permise(verificare_trig);
    }

   evaluare_expresie_trig();

   auto rezultat = calc_functie_trig(tip_functie_trig);
   if(rezultat){
	std::cout << "Rezultatul este: " <<*rezultat << '\n';
    }else std::cout << "Functia trig nu este definita \n";
    
    reseteaza();
}

void Calc_trig::interfata(){
    int index;
    std::string line;
    std::cout << "\nCalculator stiintific v1.0\n";
    while(true){
    std::cout << "\n";
    afisare_istoric();
    std::cout << "[1] Calculare expresie";
    std::cout << "[2] Calculare Functie Trigonometrica";
    std::cout << "[3] undo istoric";
    std::cout << "[4] redo istoric";
    std::cout << "[5] exit\n";
    std::cout << "Alegeti o optiune: "; std::getline(std::cin,line);

    std::stringstream ss(line);
    if(!(ss >> index)){
	    std::cout << "input invalid\n";
	    continue;
	}
    runActions(index);
}
}
