#include "Calc.hpp"
#include "includes.hpp"

Calc::Calc(){
    
    actions = {
	[this]() -> std::any{ expresie_func(); return{};},
	[this]() -> std::any{ undo_istoric(); return{};},
	[this]() -> std::any{ redo_istoric(); return{};},
	[this]() -> std::any{exit(1); return{};}  
    };
}
void Calc::runActions(size_t index){
    if(index < 1 || index > actions.size()){
	std::cout << "Index invalid";
	return;
    }
    actions[index - 1]();
}

int Calc::prioritate_semn(const char c)const{
    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/') return 2;
    return 0;
}
//afisaje 
void Calc::interfata(){
    int index;
    std::cout << "\nCalculator stiintific v1.0\n";
    while(true){
    std::cout << "\n";
    afisare_istoric();
    std::cout << "[1] Calculare expresie";
    std::cout << "[2] undo istoric";
    std::cout << "[3] redo istoric";
    std::cout << "[4] exit";
    std::cout << "Alegeti o optiune: "; std::cin >> index;
    runActions(index);
    }
}

//istoric
void Calc::Adaugare_in_istoric(const std::string &expresie){
    istoric_calcule_expresie.push_back(expresie);
}

void Calc::afisare_istoric(){
   for (std::string val : istoric_calcule_expresie)
	std::cout <<"                  " << val << "\n";
}

void Calc::undo_istoric(){
    if(istoric_calcule_expresie.empty()){
	std::cout << "Va aflati la cea mai noua operatie facuta";
    }else{
	istoric_calcule_expresie_redo.push_back(expresie);
	expresie = istoric_calcule_expresie.back();
	istoric_calcule_expresie.pop_back();
    }
}

void  Calc::redo_istoric(){
    if(istoric_calcule_expresie_redo.empty()){
	std::cerr << "Nu exista operatii mai vechi";
    }else{
	istoric_calcule_expresie.push_back(expresie);
	expresie = istoric_calcule_expresie_redo.back();
	istoric_calcule_expresie_redo.pop_back();
    }
}
void Calc::goleste_istoric(){
    istoric_calcule_expresie.clear();
    istoric_calcule_expresie_redo.clear();
}

// prelucreaz_expresie
void Calc::expresie_func(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Introduce-ti expresia: "; std::getline(std::cin,expresie);
    elimina_spatii_expresie(); 
    std::cout << "Rezultatul este: " << calculare_expresie();
    Adaugare_in_istoric(expresie);
    reseteaza();
}
void Calc::elimina_spatii_expresie(){
    expresie.erase(
	std::remove_if(expresie.begin(),expresie.end(),
		   [](char c){return c == ' ';}),
	           expresie.end()) ;
}
std::vector<std::string> Calc::inFixToRPN(std::string expresie){
    std::stack<char> operators;
    std::vector<std::string> output;
    std::string number = "";

    for(int i = 0; i < (int)expresie.size();i++){
	char c = expresie[i];
	if(std::isdigit(c)){
	 number += c;
	 if(i == (int)expresie.size() - 1 || !std::isdigit(expresie[i+1])){
	   output.push_back(number);
	   number = "";
	}
	}
	else if (c == '+' || c == '-' || c == '*' || c == '/'){
	    while(!operators.empty() && prioritate_semn(operators.top()) >= prioritate_semn(c)){
		output.push_back(std::string(1, operators.top()));
		operators.pop();
	    }
	    operators.push(c);
	}
    }

    while(!operators.empty()){
	output.push_back(std::string(1, operators.top()));
	operators.pop();
    }
    return output;
}
double Calc::evaluateRPN(std::vector<std::string> & rpn){
    std::stack<double> s;

    for(std::string &token : rpn){
	if(std::isdigit(token[0])) s.push(std::stod(token)); 
        
	else{
	    double b = s.top(); s.pop();
	    double a = s.top(); s.pop();

	    if(token == "+") s.push(adunare(a, b));
	    else if(token == "-") s.push(scadere(a,b));
	    else if(token == "*") s.push(inmultire(a,b));
	    else if (token == "/") s.push(impartire(a,b));
    }
    }
    return s.top();
}

double Calc::calculare_expresie(){
    std::vector<std::string> rpn;
    rpn = inFixToRPN(expresie);
    return evaluateRPN(rpn);


}

// Operatii
double Calc::adunare(double x, double y){
    return x + y;
}
double Calc::scadere(double x,double y){
    return x - y;
}
double Calc::inmultire(double x, double y){
    return   x * y;
}
double Calc::impartire(double x, double y){
    try{
	if(y == 0) throw std::runtime_error("impartire la 0");
	return x / y;
    }catch(std::exception &e){
	std::cerr << "Eroare: " << e.what() << std::endl;
    }
    return x / y;
}
void Calc::reseteaza(){ 
    rezultat = 0;
    expresie = "";
 }

