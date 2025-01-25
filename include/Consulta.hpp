#ifndef CONSULTA_HPP
#define CONSULTA_HPP

#include <string>

class Consulta {
public:
    int maxVoos;
    // Trigrama (ex.: "pds")
    std::string criterioOrdenacao; 
    // Expressão lógica de filtragem
    std::string expressaoLogica;   

    Consulta(int maxV, std::string criterio, std::string expressao)
        : maxVoos(maxV), criterioOrdenacao(criterio), expressaoLogica(expressao) {}
};

#endif // CONSULTA_HPP