#ifndef CALC_TRIG_HPP
#define CALC_TRIG_HPP
#include "includes.hpp"
#include "Calc.hpp"

class Calc_trig:public Calc{
private:
    std::string tip_functie_trig; 
    double rezultat_expresie;
    std::vector<std::string> functii_permise = {"sin","cos","tan", "ctg" };
    bool verificare_functie(const std::string & tip_functie_trig, std::string &functie_trig);
    void verificare_functii_permise(); 
    void evaluare_expresie_trig();
    std::optional<double> calc_functie_trig(std::string tip_functie_trig);
public:
    void interfata();
    void interfata_trig();
    Calc_trig();
};


#endif

