#ifndef VOO_HPP
#define VOO_HPP

#include <string>

class Voo {
public:
    std::string origem;
    std::string destino;
    double preco;
    int assentosDisponiveis;
    long dataHoraPartida;
    long dataHoraChegada;
    int numeroParadas;
    long duracao;

    Voo(const std::string& origem, const std::string& destino, double preco,
        int assentos, long dataHoraPartida, long dataHoraChegada, int paradas);
};

#endif // VOO_HPP