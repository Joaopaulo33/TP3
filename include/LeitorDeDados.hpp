#ifndef LEITOR_DE_DADOS_HPP
#define LEITOR_DE_DADOS_HPP

#include <string>
#include "Voo.hpp"
#include "Consulta.hpp"
#include "Container.hpp"
#include "Stack.hpp"

// Estrutura para representar nós da árvore sintática
struct NoExpressao {
    std::string valor;
    NoExpressao* esquerda;
    NoExpressao* direita;

    NoExpressao(const std::string& val) : valor(val), esquerda(nullptr), direita(nullptr) {}
};

class LeitorDeDados {
public:
    // Contêiner para armazenar ponteiros para objetos Voo e Consulta
    Container<Voo*> voos;
    Container<Consulta*> consultas;

    // Método para ler dados de um arquivo
    bool lerArquivo(const std::string& nomeArquivo);

    // Método para processar e executar as consultas armazenadas
    void processarConsultas();

private:
    // Métodos auxiliares para conversão de dados
    Voo parseVoo(const std::string& linha);
    Consulta parseConsulta(const std::string& linha);
    long parseDataHora(const std::string& dataHora);

    // Construção e avaliação da árvore sintática
    NoExpressao* construirArvoreSintatica(const std::string& expressao);
    bool avaliarArvoreSintatica(NoExpressao* no, Voo* voo);
    void liberarArvoreSintatica(NoExpressao* no);

    // Métodos auxiliares para processamento de lógica
    bool avaliarCondicao(Voo* voo, const std::string& condicao);
    void ordenarVoos(Container<Voo*>& voos, const std::string& criterio);
    void imprimirVoo(Voo* voo);
};

#endif // LEITOR_DE_DADOS_HPP