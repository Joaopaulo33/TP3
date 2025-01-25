#ifndef LEITOR_DE_DADOS_HPP
#define LEITOR_DE_DADOS_HPP

#include <string>
#include "Voo.hpp"
#include "Consulta.hpp"
#include "Container.hpp"

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

    // Métodos auxiliares para processamento de lógica
    bool avaliarExpressaoLogica(Voo* voo, const std::string& expressao);
    bool avaliarCondicao(Voo* voo, const std::string& condicao); // Avaliação de condições individuais
    void ordenarVoos(Container<Voo*>& voos, const std::string& criterio);
    void imprimirVoo(Voo* voo);
};

#endif // LEITOR_DE_DADOS_HPP