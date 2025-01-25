# Nome do executável
EXEC = tp3.out

# Diretórios
SRCDIR = ./src
INCDIR = ./include
OBJDIR = ./obj
BINDIR = ./bin

# Lista de arquivos objeto (.o) com o caminho do diretório 'obj'
OBJ = $(OBJDIR)/tp3.o $(OBJDIR)/Voo.o $(OBJDIR)/Consulta.o $(OBJDIR)/LeitorDeDados.o

# Compilador
CC = g++

# Opções de compilação (adiciona o caminho do diretório include e ativa C++11)
CFLAGS = -Wall -g -std=c++11 -I$(INCDIR)

# Regra padrão que será chamada quando rodarmos "make"
all: $(BINDIR)/$(EXEC)

# Regra para criar o executável na pasta 'bin'
$(BINDIR)/$(EXEC): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para criar o diretório 'obj' se ele não existir
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Regra para criar o diretório 'bin' se ele não existir
$(BINDIR):
	mkdir -p $(BINDIR)

# Regra para compilar cada arquivo .cpp em um arquivo .o correspondente
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza, remove os arquivos objeto e o executável
clean:
	rm -f $(OBJ) $(BINDIR)/$(EXEC)

# Regra de limpeza completa, remove os diretórios obj e bin
cleanall:
	rm -rf $(OBJDIR) $(BINDIR)