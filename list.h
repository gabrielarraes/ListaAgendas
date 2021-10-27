#ifndef UNTITLED2_LIST_H
#define UNTITLED2_LIST_H

typedef struct lista_agenda {
    struct agenda *agendas;
    int qtd_agendas;
    int capacidade;
} lista_agenda;

typedef struct agenda {
    int id;
    struct contato *contatos;
    int capacidade;
    int qtd_contatos;
    int padding;
} agenda;

typedef struct contato {
    char nome[35];
    int idade;
    long telefone;
    char email[50];
} contato;

agenda *cria_agenda(int capacidade_inicial, int identificador);
int atualiza_capacidade_agenda(agenda *a);
contato solicitar_informacoes_contato();
void mostrar_contato(contato c);
void incluir_contato(agenda *agenda, contato c);
void menu(lista_agenda *lst);
contato *buscar_contato(agenda *a, char *nome_procurado);
void deletar_contato(agenda *a, char *nome);
int atualiza_qtd_agendas(lista_agenda *la);
void incluir_agenda(lista_agenda *lst);
lista_agenda *cria_lista(int capacidade_inicial, int capacidade_inicial_agenda);


#endif
