#ifndef CALC_HPP
#define CALC_HPP

#include "includes.hpp"

class Calc{
private:
    std::vector<std::function<std::any()>> actions;
    std::string caractere_permise = "+-*/()";
    double rezultat = 0;
    std::string expresie = "";
    std::deque<std::string> istoric_calcule_expresie;
    std::deque<std::string> istoric_calcule_expresie_redo;

    double adunare(double x,double y);
    double scadere(double x, double y);
    double inmultire(double x, double y);
    double impartire(double x, double y);

    double getRezultat()const;
    
    void reseteaza();
    void Adaugare_in_istoric(const std::string &expresie); 
    void undo_istoric();
    void redo_istoric();
    void goleste_istoric();
    
    void expresie_func();
    void elimina_spatii_expresie();
    std::vector<std::string> inFixToRPN(std::string expresie);
    double evaluateRPN(std::vector<std::string>&rpn);
    double calculare_expresie();
    void prelucreaz_expresie();
    int prioritate_semn(const char c)const;

    void clearscreen(){ std::cout << "\033[2J\033[1;1H";}
public:
    Calc();
    void runActions(size_t index);
    void afisare_istoric();
    void interfata();
};


#endif 
