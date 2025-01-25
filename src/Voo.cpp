#include "Voo.hpp"

Voo::Voo(const std::string& org, const std::string& dst, double prc, int assentos,
         long partida, long chegada, int paradas)
    : origem(org), destino(dst), preco(prc), assentosDisponiveis(assentos),
      dataHoraPartida(partida), dataHoraChegada(chegada), numeroParadas(paradas) {
    duracao = dataHoraChegada - dataHoraPartida;
}