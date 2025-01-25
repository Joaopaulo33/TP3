#include "LeitorDeDados.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip> // Para std::put_time

NoExpressao* LeitorDeDados::construirArvoreSintatica(const std::string& expressao) {
    Stack<NoExpressao*> pilha;
    std::istringstream tokens(expressao);
    std::string token;

    while (tokens >> token) {
        if (token == "&&") {
            NoExpressao* direita = pilha.top(); pilha.pop();
            NoExpressao* esquerda = pilha.top(); pilha.pop();
            NoExpressao* no = new NoExpressao(token);
            no->esquerda = esquerda;
            no->direita = direita;
            pilha.push(no);
        } else if (token != "(" && token != ")") {
            pilha.push(new NoExpressao(token));
        }
    }

    return pilha.isEmpty() ? nullptr : pilha.top();
}

bool LeitorDeDados::avaliarArvoreSintatica(NoExpressao* no, Voo* voo) {
    if (!no) return false;
    if (!no->esquerda && !no->direita) {
        return avaliarCondicao(voo, no->valor);
    }

    bool esquerda = avaliarArvoreSintatica(no->esquerda, voo);
    bool direita = avaliarArvoreSintatica(no->direita, voo);

    if (no->valor == "&&") {
        return esquerda && direita;
    }

    return false;
}

void LeitorDeDados::liberarArvoreSintatica(NoExpressao* no) {
    if (!no) return;
    liberarArvoreSintatica(no->esquerda);
    liberarArvoreSintatica(no->direita);
    delete no;
}

bool LeitorDeDados::lerArquivo(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return false;
    }

    std::string linha;
    int numeroDeVoos;

    std::getline(arquivo, linha);
    std::istringstream(linha) >> numeroDeVoos;

    for (int i = 0; i < numeroDeVoos; ++i) {
        std::getline(arquivo, linha);
        voos.add(new Voo(parseVoo(linha)));
    }

    int numeroDeConsultas;
    std::getline(arquivo, linha);
    std::istringstream(linha) >> numeroDeConsultas;

    for (int i = 0; i < numeroDeConsultas; ++i) {
        std::getline(arquivo, linha);
        consultas.add(new Consulta(parseConsulta(linha)));
    }

    arquivo.close();
    return true;
}

Voo LeitorDeDados::parseVoo(const std::string& linha) {
    std::istringstream stream(linha);
    std::string origem, destino, partida, chegada;
    double preco;
    int assentos, paradas;
    stream >> origem >> destino >> preco >> assentos >> partida >> chegada >> paradas;

    long dataHoraPartida = parseDataHora(partida);
    long dataHoraChegada = parseDataHora(chegada);

    return Voo(origem, destino, preco, assentos, dataHoraPartida, dataHoraChegada, paradas);
}

Consulta LeitorDeDados::parseConsulta(const std::string& linha) {
    std::istringstream stream(linha);
    int maxVoos;
    std::string criterio, expressao;
    stream >> maxVoos >> criterio;
    std::getline(stream, expressao);

    return Consulta(maxVoos, criterio, expressao);
}

void LeitorDeDados::processarConsultas() {
    for (int i = 0; i < consultas.getSize(); ++i) {
        Consulta* consulta = consultas.get(i);
        NoExpressao* arvoreSintatica = construirArvoreSintatica(consulta->expressaoLogica);

        Container<Voo*> resultados;
        for (int j = 0; j < voos.getSize(); ++j) {
            Voo* voo = voos.get(j);
            if (avaliarArvoreSintatica(arvoreSintatica, voo)) {
                resultados.add(voo);
            }
        }
        std::cout << consulta->maxVoos << " " << consulta->criterioOrdenacao << " " << consulta->expressaoLogica << std::endl;

        ordenarVoos(resultados, consulta->criterioOrdenacao);

        for (int k = 0; k < std::min(resultados.getSize(), consulta->maxVoos); ++k) {
            imprimirVoo(resultados.get(k));
        }

        liberarArvoreSintatica(arvoreSintatica);
    }
}

bool LeitorDeDados::avaliarCondicao(Voo* voo, const std::string& condicao) {
    if (condicao.find("dur>=") != std::string::npos) {
        size_t pos = condicao.find("dur>=") + 5;
        long duracaoMinima = std::stol(condicao.substr(pos));
        return voo->duracao >= duracaoMinima;
    }
    if (condicao.find("sea>=") != std::string::npos) {
        size_t pos = condicao.find("sea>=") + 5;
        int minAssentos = std::stoi(condicao.substr(pos));
        return voo->assentosDisponiveis >= minAssentos;
    }
    if (condicao.find("dst==") != std::string::npos) {
        size_t pos = condicao.find("dst==") + 5;
        std::string destinoEsperado = condicao.substr(pos);
        return voo->destino == destinoEsperado;
    }
    return false;
}

void LeitorDeDados::ordenarVoos(Container<Voo*>& voos, const std::string& criterio) {
    for (int i = 0; i < voos.getSize(); ++i) {
        for (int j = i + 1; j < voos.getSize(); ++j) {
            Voo* a = voos.get(i);
            Voo* b = voos.get(j);

            bool swap = false;
            if (criterio == "psd") {
                if (a->preco > b->preco || 
                    (a->preco == b->preco && a->numeroParadas > b->numeroParadas) || 
                    (a->preco == b->preco && a->numeroParadas == b->numeroParadas && a->duracao > b->duracao)) {
                    swap = true;
                }
            } else if (criterio == "sdp") {
                if (a->numeroParadas > b->numeroParadas || 
                    (a->numeroParadas == b->numeroParadas && a->duracao > b->duracao) || 
                    (a->numeroParadas == b->numeroParadas && a->duracao == b->duracao && a->preco > b->preco)) {
                    swap = true;
                }
            } else if (criterio == "dps") {
                if (a->duracao > b->duracao || 
                    (a->duracao == b->duracao && a->preco > b->preco) || 
                    (a->duracao == b->duracao && a->preco == b->preco && a->numeroParadas > b->numeroParadas)) {
                    swap = true;
                }
            } else if (criterio == "pds") {
                if (a->preco > b->preco || 
                    (a->preco == b->preco && a->duracao > b->duracao) || 
                    (a->preco == b->preco && a->duracao == b->duracao && a->numeroParadas > b->numeroParadas)) {
                    swap = true;
                }
            } else if (criterio == "dsp") {
                if (a->duracao > b->duracao || 
                    (a->duracao == b->duracao && a->numeroParadas > b->numeroParadas) || 
                    (a->duracao == b->duracao && a->numeroParadas == b->numeroParadas && a->preco > b->preco)) {
                    swap = true;
                }
            } else if (criterio == "spd") {
                if (a->numeroParadas > b->numeroParadas || 
                    (a->numeroParadas == b->numeroParadas && a->preco > b->preco) || 
                    (a->numeroParadas == b->numeroParadas && a->preco == b->preco && a->duracao > b->duracao)) {
                    swap = true;
                }
            }

            if (swap) {
                voos.swap(i, j);
            }
        }
    }
}

void LeitorDeDados::imprimirVoo(Voo* voo) {
    // Converte long para std::time_t e verifica os valores
    std::time_t partida = static_cast<std::time_t>(voo->dataHoraPartida);
    std::time_t chegada = static_cast<std::time_t>(voo->dataHoraChegada);

    // Usar std::localtime e copiar o resultado imediatamente
    std::tm partida_tm = *std::localtime(&partida);
    std::tm chegada_tm = *std::localtime(&chegada);

    // Saída original
    std::cout << voo->origem << " " << voo->destino << " " << voo->preco << " "
              << voo->assentosDisponiveis << " "
              << std::put_time(&partida_tm, "%Y-%m-%dT%H:%M:%S") << " "
              << std::put_time(&chegada_tm, "%Y-%m-%dT%H:%M:%S") << " "
              << voo->numeroParadas << std::endl;
}

long LeitorDeDados::parseDataHora(const std::string& dataHora) {
    std::tm tm = {};
    std::istringstream ss(dataHora);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");

    if (ss.fail()) {
        std::cerr << "Erro ao analisar data/hora: " << dataHora << std::endl;
        return -1;
    }

    tm.tm_isdst = -1;
    std::time_t timeSinceEpoch = std::mktime(&tm);

    return static_cast<long>(timeSinceEpoch);
}