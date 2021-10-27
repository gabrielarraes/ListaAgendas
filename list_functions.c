#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int z = 5;
void liberar_memoria(lista_agenda *lst) {
    free(lst);
}

void incluir_agenda(lista_agenda *lst) {
    atualiza_qtd_agendas(lst);

    agenda *ag = cria_agenda(4, z);
    z++;

    lst->agendas[lst->qtd_agendas] = *ag;
    free(ag);
    lst->qtd_agendas++;
}

agenda *cria_agenda(int capacidade_inicial, int identificador) {

    agenda *nova_agenda;

    nova_agenda = (agenda *) malloc(sizeof(agenda));
    nova_agenda->id = identificador;
    nova_agenda->qtd_contatos = 0;
    nova_agenda->capacidade = capacidade_inicial;
    nova_agenda->contatos = (contato *) malloc(sizeof(contato) * nova_agenda->capacidade);

    return nova_agenda;
}

lista_agenda *cria_lista(int capacidade_inicial, int capacidade_inicial_agenda) {

    lista_agenda *lista;
    //aloca memoria para lista de agendas
    lista = (lista_agenda *) malloc(sizeof(lista_agenda));
    lista->qtd_agendas = capacidade_inicial;
    lista->capacidade = capacidade_inicial;
    lista->agendas = (agenda *)malloc(sizeof(agenda) * capacidade_inicial);
    //alocando memoria para os contatos das agendas e inserindo id
    for (int i = 0; i < capacidade_inicial; i++) {
        lista->agendas[i].id = i + 1;
        lista->agendas[i].contatos = (contato *)malloc(sizeof(contato) * capacidade_inicial_agenda);
        lista->agendas[i].qtd_contatos = 0;
        lista->agendas[i].capacidade = capacidade_inicial_agenda;
    }

    return lista;
}

void incluir_contato(agenda *agenda, contato c) {
    agenda->contatos[agenda->qtd_contatos] = c;
    agenda->qtd_contatos++;
    atualiza_capacidade_agenda(agenda);
}

int atualiza_capacidade_agenda(agenda *a) {
    float percentual;
    int nova_capacidade;

    percentual = (float) a->qtd_contatos / (float) a->capacidade;

    if (percentual >= 0.5) {
        nova_capacidade = a->capacidade * 2;
        a->contatos = (contato *) realloc(a->contatos, sizeof(contato) * nova_capacidade);
        a->capacidade = nova_capacidade;
        return 1;
    }

    if (percentual <= 0.2) {
        nova_capacidade = a->capacidade / 2;
        a->contatos = (contato *) realloc(a->contatos, sizeof(contato) * nova_capacidade);
        a->capacidade = nova_capacidade;
        return 1;
    }

    return 0;
}

int atualiza_qtd_agendas(lista_agenda *la) {
    float percentual;
    int nova_capacidade;

    percentual = (float) la->qtd_agendas / (float) la->capacidade;

    if (percentual >= 0.4) {
        nova_capacidade = la->capacidade * 2;
        la->agendas = (agenda *) realloc(la->agendas, sizeof(agenda) * nova_capacidade);
        la->capacidade = nova_capacidade;
        return 1;
    }

    if (percentual <= 0.2) {
        nova_capacidade = la->capacidade / 2;
        la->agendas = (agenda *) realloc(la->agendas, sizeof(agenda) * nova_capacidade);
        la->capacidade = nova_capacidade;
        return 1;
    }

    return 0;
}

contato solicitar_informacoes_contato() {
    contato c;
    printf("Digite o nome do contato: ");
    fflush(stdin);
    fgets(c.nome, 35, stdin);
    c.nome[strlen(c.nome) - 1] = '\0';
    printf("Digite a idade do contato: ");
    scanf("%d", &c.idade);
    printf("Digite o telefone do contato: ");
    scanf("%ld", &c.telefone);
    printf("Digite o email do contato: ");
    fflush(stdin);
    fgets(c.email, 50, stdin);
    c.email[strlen(c.email) - 1] = '\0';
    return c;
}

void mostrar_contato(contato c) {
    printf("\n|-----> Nome: %s Email: %s Idade: %d Telefone: %ld |", c.nome, c.email, c.idade, c.telefone);
}

void menu(lista_agenda *lst) {
    int opcao, id, j, x, h, i, d;
    char procurado[35];
    contato *c;
    contato contato_novo;
    agenda *agnd;

    do {
        printf("\n\n Quantidade de agendas: %d", lst->qtd_agendas);
        printf("\n 1 - Incluir agenda");
        printf("\n 2 - Buscar um contato");
        printf("\n 3 - Remover um contato");
        printf("\n 4 - Mostrar agenda completa");
        printf("\n 5 - incluir contato");
        printf("\n 6 - sair");
        printf("\n Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nAgenda %d incluida com sucesso.", z);
                incluir_agenda(lst);

                break;
            case 2:
                printf("\nDigite o nome que deseja procurar: ");
                fflush(stdin);
                fgets(procurado,50,stdin);
                procurado[strlen(procurado)-1] = '\0';
                printf("informe o numero da agenda: ");
                scanf("%d", &d);
                for (j=0; d < lst->qtd_agendas; j++) {
                    if (lst->agendas[j].id == d) {
                        c = buscar_contato(&lst->agendas[j], procurado);
                        break;
                    }
                }

                if (c==NULL)
                {
                    printf("\nNao existe '%s' na agenda %d",procurado, d);
                }
                else
                {
                    mostrar_contato(*c);
                }
                break;
            case 3:
                printf("\ndigite o nome que deseja excluir: ");
                fflush(stdin);
                fgets(procurado, 50, stdin);
                procurado[strlen(procurado) - 1] = '\0';
                printf("informe o numero da agenda: ");
                scanf("%d", &h);

                for (j=0; j < lst->qtd_agendas; j++) {
                    if (lst->agendas[j].id == h) {
                        deletar_contato(&lst->agendas[j], procurado);
                    }
                }
                break;
            case 4:
                printf("\ninforme o numero da agenda: ");
                scanf("%d", &x);
                printf("\n|| agenda %d --------------------------------------------------------------------------------->", x);

                for (j = 0; j < lst->qtd_agendas; j++) {
                    if (x > lst->qtd_agendas) {
                        printf("\nagenda de numero %d nao foi iniciada", x);
                        printf("\ninforme o numero da agenda: \n");
                        scanf("%d", x);
                    }
                    if (lst->agendas[j].id == x) {
                        for (i = 0; i < lst->agendas[j].qtd_contatos; i++) {
                            mostrar_contato(lst->agendas[j].contatos[i]);
                        }
                        break;
                    }
                }
                printf("\n|| ------------------------------------------------------------------------------------------>");
                break;
            case 5:
                printf("\ninforme o numero da agenda: ");
                scanf("%d", &id);

                for (j = 0; j < lst->qtd_agendas; j++) {
                    if (lst->agendas[j].id == id) {
                        contato_novo = solicitar_informacoes_contato();
                        incluir_contato(&lst->agendas[j], contato_novo);
                        printf("\nContato Incluido na agenda %d.", lst->agendas[j].id);
                        break;
                    }
                }
                break;
            case 6:
                break;
            default:
                printf("\nopcao invalida");
                break;
        }
    } while (opcao != 6);

}

contato *buscar_contato(agenda * a, char * nome_procurado) {
    for (int i = 0; i < a->qtd_contatos; i++) {
        if (strcmp(a->contatos[i].nome, nome_procurado) == 0) {
            return &a->contatos[i];
        }
    }
    return NULL;
}

void deletar_contato(agenda *a, char *nome) {
    for (int i = 0; i < a->qtd_contatos; i++) {
        if (strcmp(a->contatos[i].nome, nome) == 0) {
            int index = i;

            for (int l = index; l < a->qtd_contatos - 1; l++) {
                a->contatos[l] = a->contatos[l + 1];
            }

            free(&a->contatos[a->qtd_contatos--]);
            atualiza_capacidade_agenda(a);
            break;
        }
    }
}

