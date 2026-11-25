#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>


#define NUM_MAX_CAD 1024


typedef struct Ficha
{
    int ocupado;
    char codigo[14];
    char nome[256];
    char especie[256];
    char raca[256];
    int idade;
    char sexo;
    char condicoes[256];

} Ficha;


Ficha vetor_fichas[NUM_MAX_CAD];
int total_fichas = 0;
char caminho_arquivo_fichas[256];

void cadastro_inicializar();
int cadastro_verificar_capacidade_maxima();
void cadastro_inserir_fichas(Ficha fichas);
Ficha cadastro_pesquisar_fichas(char *codigo);
int cadastro_remover_fichas(char *codigo);
void cadastro_salvar_dados_arquivo();
void cadastro_inicializar_arquivo();
void cadastro_carregar_dados_arquivo();

int tela_menu_opcoes();
void tela_cadastrar();
void tela_pesquisar();
void tela_remover();
void tela_relatorio();
int tela_sair();

int tela_mensagem(char *mensagem);
void leia_codigo(char *str);
void leia_nome(char *str);
void leia_especie(char *str);
void leia_raca(char *str);
int leia_idade();
char leia_sexo();
void leia_condicoes(char *str);

int main()
{
    setlocale(LC_ALL, "portuguese");
    system("chcp 1252 > null");

    cadastro_inicializar();
    cadastro_inicializar_arquivo();
    cadastro_carregar_dados_arquivo();

    int sair = 0;
    int opcao;

    do
    {
        opcao = tela_menu_opcoes();

        switch(opcao)
        {
        case 1:
            tela_cadastrar();
            break;

        case 2:
            tela_pesquisar();
            break;

        case 3:
            tela_remover();
            break;

        case 4:
            tela_relatorio();
            break;

        case 5:
            sair = tela_sair();
            break;

        default:
            printf("\nOpção Inválida !!! \n");
            system("pause");
        }

    }
    while(sair == 0);

    cadastro_salvar_dados_arquivo();

    system("cls");
    printf("\nFim da execução do programa!\n");

    return 0;
}

int tela_menu_opcoes()
{
    int opcao;
    system("cls");
    printf("==============================\n");
    printf("        Menu de Opções        \n");
    printf("==============================\n\n");
    printf("1 - Cadastrar ficha \n");
    printf("------------------------------\n");
    printf("2 - Pesquisar ficha \n");
    printf("------------------------------\n");
    printf("3 - Remover ficha \n");
    printf("------------------------------\n");
    printf("4 - Gerar relatório \n");
    printf("------------------------------\n");
    printf("5 - Sair \n\n\n");

    printf("Escolha uma opção: ");
    int erro = scanf("%d", &opcao);


    if(erro != 1)
    {

        fflush(stdin);

        opcao = -1;
    }


    return opcao;
}

void tela_cadastrar()
{
    int continuar;


    Ficha fichas;

    do
    {
        system("cls");
        printf("1 - Cadastrar ficha \n");

        if(cadastro_verificar_capacidade_maxima() == 1)
        {
            printf("\nErro: O cadastro de fichas já atingiu sua capacidade máxima!\n");
            system("pause");
            break;
        }

        leia_codigo(fichas.codigo);
        leia_nome(fichas.nome);
        leia_especie(fichas.especie);
        leia_raca(fichas.raca);
        fichas.idade = leia_idade();
        fichas.sexo = leia_sexo();
        leia_condicoes(fichas.condicoes);

        cadastro_inserir_fichas(fichas);


        continuar = tela_mensagem("\nGostaria de cadastrar outra ficha?");

    }
    while(continuar == 1);
}




void tela_pesquisar()
{
    int continuar;
    char codigo[14];

    do
    {

        system("cls");
        printf("2 - Pesquisar ficha \n");

        leia_codigo(codigo);

        Ficha fichasDados = cadastro_pesquisar_fichas(codigo);
        if(fichasDados.ocupado == 1)
        {
            printf("\nFicha com o mesmo CÓDIGO: \n");
            printf("Código:     %s\n", fichasDados.codigo);
            printf("Nome:    %s\n", fichasDados.nome);
            printf("Espécie:   %s\n", fichasDados.especie);
            printf("Raça:   %s\n", fichasDados.raca);
            printf("Idade:   %d\n", fichasDados.idade);
            printf("Sexo:    %c\n", fichasDados.sexo);
            printf("Condições médicas:   %s\n", fichasDados.condicoes);
            system("pause");
        }
        else
        {
            printf("\nNão foi encontrada uma ficha com o código informado!\n\n");
            system("pause");
        }

        continuar = tela_mensagem("\nGostaria de pesquisar outra ficha?");

    }
    while(continuar == 1);
}




void tela_remover()
{
    int continuar;

    char codigo[14];

    do
    {
        system("cls");
        printf("3 - Remover ficha \n\n");

        leia_codigo(codigo);

        int rs = cadastro_remover_fichas(codigo);

        if(rs == 1)
        {
            printf("\nFicha removida com sucesso!\n");
        }
        else
        {
            printf("\nNão foi possível remover a ficha do cadastro!\n");
        }

        system("pause");


        continuar = tela_mensagem("\nGostaria de remover outra ficha?");


    }
    while(continuar);
}



void tela_relatorio()
{

    system("cls");
    printf("4 - Gerar relatório \n\n");

    printf("Total de fichas cadastradas: %d\n\n", total_fichas);

    for(int i=0; i<NUM_MAX_CAD; i++)
    {

        if(vetor_fichas[i].ocupado == 1)
        {
            printf("Código:     %s\n", vetor_fichas[i].codigo);
            printf("Nome:    %s\n", vetor_fichas[i].nome);
            printf("Espécie:   %s\n", vetor_fichas[i].especie);
            printf("Raça:   %s\n", vetor_fichas[i].raca);
            printf("Idade:   %d\n", vetor_fichas[i].idade);
            printf("Sexo:    %c\n", vetor_fichas[i].sexo);
            printf("Condições médicas:   %s\n", vetor_fichas[i].condicoes);
            printf("------------------------------\n");
        }
    }

    system("pause");
}


int tela_sair()
{

    int sair;

    system("cls");
    printf("5 - Sair \n\n");
    sair = tela_mensagem("\nDeseja mesmo sair?");


    return sair;
}

int tela_mensagem(char *mensagem)
{
    char ch;
    char texto[256] = "";
    int erro;


    strcat(texto, mensagem);
    strcat(texto, " (s/n): ");

    do
    {
        erro = 0;

        printf(texto);

        scanf(" %c", &ch);


        fflush(stdin);

        ch = toupper(ch);

        if( !(ch == 'S' || ch == 'N') )
        {
            erro = 1;
            printf("ERRO: São aceitos apenas os valores 's' ou 'n'!\n");
        }

    }
    while(erro);

    if(ch == 'S') return 1;
    else return 0;
}


void leia_codigo(char *str)
{
    int erro;

    do
    {
        erro = 0;

        printf("\nDigite o código de identificação: ");


        scanf(" %13[^\n]", str);


        fflush(stdin);


        if(strlen(str) > 12)
        {
            erro = 1;
            printf("ERRO: O código deve possuir até 12 (doze) caracteres!\n");
        }

    }
    while(erro == 1);
}


void leia_nome(char *str)
{
    int erro;


    do
    {
        erro = 0;

        printf("\nDigite o nome: ");
        scanf(" %255[^\n]", str);


        fflush(stdin);


        if(strlen(str) > 254)
        {
            erro = 1;
            printf("ERRO: O nome pode possuir no máximo 254 carracteres!\n");
        }
        if(strlen(str) < 3)
        {
            erro = 1;
            printf("ERRO: O nome deve possuir pelo menos 3 (três) carracteres!\n");
        }

    }
    while(erro == 1);
}


void leia_especie(char *str)
{
    int erro;


    do
    {
        erro = 0;

        printf("\nDigite a especie: ");
        scanf(" %255[^\n]", str);


        fflush(stdin);


        if(strlen(str) > 254)
        {
            erro = 1;
            printf("ERRO: Pode possuir no máximo 254 carracteres!\n");
        }
        if(strlen(str) < 3)
        {
            erro = 1;
            printf("ERRO: Deve possuir pelo menos 3 (três) carracteres!\n");
        }

    }
    while(erro == 1);
}

void leia_raca(char *str)
{
    int erro;


    do
    {
        erro = 0;

        printf("\nDigite a raça: ");
        scanf(" %255[^\n]", str);


        fflush(stdin);


        if(strlen(str) > 254)
        {
            erro = 1;
            printf("ERRO: Pode possuir no máximo 254 carracteres!\n");
        }
        if(strlen(str) < 3)
        {
            erro = 1;
            printf("ERRO: Deve possuir pelo menos 3 (três) carracteres!\n");
        }

    }
    while(erro == 1);
}

int leia_idade()
{
    int erro;


    int idade;

    do
    {
        printf("\nDigite a idade (anos): ");
        erro = scanf("%d", &idade);

        fflush(stdin);

        if(erro != 1)
        {
            printf("ERRO: Digite um valor inteiro válido!\n");
        }
        else if(idade < 1 || idade > 120)
        {
            erro = -1;
            printf("ERRO: A idade deve estar entre 1 e 120 anos!\n");
        }

    }
    while(erro != 1);

    return idade;
}

char leia_sexo()
{
    int erro;

    char sexo;

    char strSexo[3];

    do
    {
        erro = 0;

        printf("\nDigite o sexo (M / F): ");


        scanf(" %2[^\n]", strSexo);

        fflush(stdin);

        if(strlen(strSexo) == 1)
        {

            sexo = toupper(strSexo[0]);
        }
        else
        {
            erro = 1;
        }


        if( !(sexo == 'M' || sexo == 'F') || erro == 1 )
        {
            erro = 1;
            printf("ERRO: São aceitos apenas os valores 'M' ou 'F'!\n");
        }

    }
    while(erro == 1);

    return sexo;

}


void leia_condicoes(char *str)
{
    int erro;


    do
    {
        erro = 0;

        printf("\nDigite as condições médicas: ");
        scanf(" %255[^\n]", str);


        fflush(stdin);


        if(strlen(str) > 254)
        {
            erro = 1;
            printf("ERRO: O texto pode possuir no máximo 254 carracteres!\n");
        }
        if(strlen(str) < 3)
        {
            erro = 1;
            printf("ERRO: O texto deve possuir pelo menos 3 (três) carracteres!\n");
        }
    }
    while(erro == 1);

}


void cadastro_inicializar()
{
    total_fichas = 0;


    for(int i=0; i < NUM_MAX_CAD; i++)
    {

        vetor_fichas[i].ocupado = 0;
    }
}




int cadastro_verificar_capacidade_maxima()
{

    if(total_fichas >= NUM_MAX_CAD)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}




void cadastro_inserir_fichas(Ficha fichas)
{

    int idxPesquisa = -1;


    for(int i=0; i < NUM_MAX_CAD; i++)
    {
        if(vetor_fichas[i].ocupado == 1)
        {

            if( strcmp(vetor_fichas[i].codigo, fichas.codigo) == 0)
            {
                idxPesquisa = i;
                break;
            }
        }
    }


    if(idxPesquisa != -1)
    {
        printf("\nErro: Não foi possível inserir os dados pois já existe uma ficha com o mesmo código no cadastro:\v");

        printf("\nFicha com o mesmo código: \n");
        printf("Código:     %s\n", vetor_fichas[idxPesquisa].codigo);
        printf("Nome:    %s\n", vetor_fichas[idxPesquisa].nome);
        printf("Espécie:    %s\n", vetor_fichas[idxPesquisa].especie);
        printf("Raça:    %s\n", vetor_fichas[idxPesquisa].raca);
        printf("Idade:   %d\n", vetor_fichas[idxPesquisa].idade);
        printf("Sexo:    %c\n", vetor_fichas[idxPesquisa].sexo);
        printf("Condições médicas:    %s\n", vetor_fichas[idxPesquisa].condicoes);
        system("pause");
    }
    else
    {

        for(int i=0; i < NUM_MAX_CAD; i++)
        {
            if(vetor_fichas[i].ocupado == 0)
            {
                vetor_fichas[i].ocupado = 1;


                strcpy(vetor_fichas[i].codigo, fichas.codigo);
                strcpy(vetor_fichas[i].nome, fichas.nome);
                strcpy(vetor_fichas[i].especie, fichas.especie);
                strcpy(vetor_fichas[i].raca, fichas.raca);
                strcpy(vetor_fichas[i].condicoes, fichas.condicoes);
                vetor_fichas[i].idade = fichas.idade;
                vetor_fichas[i].sexo = fichas.sexo;


                total_fichas = total_fichas + 1;
                cadastro_salvar_dados_arquivo();

                printf("\nDados cadastrados com sucesso! \n");
                system("pause");

                break;
            }
        }
    }
}


Ficha cadastro_pesquisar_fichas(char *codigo)
{
    int idxPesquisa = -1;

    for(int i=0; i<NUM_MAX_CAD; i++)
    {

        if(vetor_fichas[i].ocupado == 1)
        {
            if(strcmp(vetor_fichas[i].codigo, codigo) == 0)
            {

                idxPesquisa = i;

                break;
            }
        }
    }


    if(idxPesquisa != -1)
    {
        return vetor_fichas[idxPesquisa];

    }
    else
    {

        Ficha fichaSemDados = {0, "", "", "", "", 0, ' ', ""};

        return fichaSemDados;
    }
}




int cadastro_remover_fichas(char *codigo)
{
    int idxPesquisa = -1;

    for(int i = 0; i < NUM_MAX_CAD; i++)
    {


        if(vetor_fichas[i].ocupado == 1)
        {
            if(strcmp(vetor_fichas[i].codigo, codigo) == 0)
            {

                total_fichas = total_fichas - 1;


                vetor_fichas[i].ocupado = 0;
                cadastro_salvar_dados_arquivo();

                idxPesquisa = i;

                break;
            }
        }
    }


    if(idxPesquisa != -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void cadastro_inicializar_arquivo()
{
    strcpy(caminho_arquivo_fichas, "cadastro_de_fichas.txt");

    FILE *fp = fopen(caminho_arquivo_fichas, "r");

    if(fp == NULL)
    {
        cadastro_salvar_dados_arquivo();
    }
    else
    {
        fclose(fp);
    }
}

void cadastro_carregar_dados_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_fichas, "r");

    if(fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        exit(EXIT_FAILURE);
    }

    char linha[512];

    for(int i = 0; i < 3; i++)
    {
        if(fgets(linha, sizeof(linha), fp) == NULL)
        {
            fclose(fp);
            return;
        }
    }

    if(fscanf(fp, "Total de fichas: %d\n", &total_fichas) != 1)
    {
        total_fichas = 0;
        fclose(fp);
        return;
    }

    if(total_fichas < 0 || total_fichas > NUM_MAX_CAD)
    {
        total_fichas = 0;
        fclose(fp);
        return;
    }

    int total_carregado = 0;

    for(int i = 0; i < total_fichas; i++)
    {
        Ficha fichas = {0};

        if(fgets(linha, sizeof(linha), fp) == NULL)
            break;
        if(fscanf(fp, "Código de identificação: %13[^\n]\n", fichas.codigo) != 1)
            break;
        if(fscanf(fp, "Nome: %255[^\n]\n", fichas.nome) != 1)
            break;
        if(fscanf(fp, "Espécie: %255[^\n]\n", fichas.especie) != 1)
            break;
        if(fscanf(fp, "Raça: %255[^\n]\n", fichas.raca) != 1)
            break;
        if(fscanf(fp, "Idade: %d\n", &fichas.idade) != 1)
            break;
        if(fscanf(fp, "Sexo: %c\n", &fichas.sexo) != 1)
            break;
        if(fscanf(fp, "Condições médicas: %255[^\n]\n", fichas.condicoes) != 1)
            break;

        fichas.ocupado = 1;

        vetor_fichas[i] = fichas;

        total_carregado++;

        if(fgets(linha, sizeof(linha), fp) == NULL)
            break;
    }

    total_fichas = total_carregado;

    fclose(fp);
}



void cadastro_salvar_dados_arquivo()
{
    FILE *fp = fopen(caminho_arquivo_fichas, "w");

    if(fp == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        return;
    }

    fprintf(fp, "==============================\n");
    fprintf(fp, "=     CADASTRO DE FICHAS     =\n");
    fprintf(fp, "==============================\n");

    fprintf(fp, "Total de fichas: %d\n\n", total_fichas);

    for(int i = 0; i < NUM_MAX_CAD; i++)
    {
        if(vetor_fichas[i].ocupado == 1)
        {
            fprintf(fp, "------------------------------\n");
            fprintf(fp, "Código de identificação: %s\n", vetor_fichas[i].codigo);
            fprintf(fp, "Nome: %s\n", vetor_fichas[i].nome);
            fprintf(fp, "Espécie: %s\n", vetor_fichas[i].especie);
            fprintf(fp, "Raça: %s\n", vetor_fichas[i].raca);
            fprintf(fp, "Idade: %d\n", vetor_fichas[i].idade);
            fprintf(fp, "Sexo: %c\n", vetor_fichas[i].sexo);
            fprintf(fp, "Condições médicas: %s\n", vetor_fichas[i].condicoes);
            fprintf(fp, "------------------------------\n");
        }
    }

    fclose(fp);
}









