#include <iostream>
#include <string>
#include "LeitorDeDados.hpp"
int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <nome_do_arquivo>" << std::endl;
        return 1;
    }

    std::string nomeArquivo = argv[1];

    LeitorDeDados leitor;

    if (!leitor.lerArquivo(nomeArquivo)) {
        std::cerr << "Erro ao ler o arquivo: " << nomeArquivo << std::endl;
        return 1;
    }

    // Processar as consultas após a leitura dos dados
    leitor.processarConsultas();

    return 0;
}