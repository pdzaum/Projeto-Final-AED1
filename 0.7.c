#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct inventario
{
    char item[100];
    int quantidade;
    struct inventario *prox;
};

struct ataques
{
    char nome[100];
    char descricao[1000];
    struct ataques *prox;
};

struct stats
{
    int numero;
    int modificador;
};

typedef struct inventario Inventario;

typedef struct ataques Ataques;

struct personagem
{
    char nome[100];
    char raca[50];
    char classe[50];
    char antecedente[50];
    char alinhamento[50];
    char caracteristicas[1000];
    char talentos[100];
    char ideais[1000];
    char vinculos[1000];
    char defeitos[1000];
    char personalidade[1000];
    char proficiencia[500];
    char idiomas[500];
    Inventario * itens;
    Ataques * atkspell;
    struct stats forca;
    struct stats destreza;
    struct stats constituicao;
    struct stats inteligencia;
    struct stats sabedoria;
    struct stats carisma;
    int level;
    int xp;
};

Ataques * ataques_cria ()
{
    Ataques * p = (Ataques*)malloc(sizeof(Ataques));
    p->prox = NULL;
    return p;
}

void ataques_insere (Ataques * p, char * nome, char *desc)
{
    Ataques * node = (Ataques*)malloc(sizeof(Ataques));
    strcpy(node->nome, nome);
    strcpy(node->descricao, desc);
    node->prox = p->prox;
    p->prox = node;
}

void ataques_remove (Ataques * p)
{
    Ataques * lixo = p->prox;
    p->prox = lixo->prox;
    free(lixo);
}

void ataques_procura_remove(Ataques * p, char * elemento)
{
    Ataques * AUX = ataques_cria();
    Ataques * scan = p->prox;

    while(strcmp(scan->nome, elemento) != 0)
    {
        ataques_insere(AUX, scan->nome,scan->descricao);
        scan = scan->prox;
        ataques_remove(p);
    }
    scan = AUX->prox;
    while(scan != NULL)
    {
        ataques_insere(p, scan->nome,scan->descricao);
        scan = scan->prox;
        ataques_remove(AUX);
    }
    free(AUX);
}

void ataques_imprime (Ataques * p)
{
    Ataques * scan = p->prox;
    while(scan != NULL)
    {
        printf("%s - %s\n", scan->nome, scan->descricao);
        scan = scan->prox;
    }
}

Inventario * inventario_cria ()
{
    Inventario * p = (Inventario*)malloc(sizeof(Inventario));
    p->quantidade = 0;
    p->prox = NULL;
    return p;
}

void inventario_insere (Inventario * p, char * elemento, int numero)
{
    Inventario * node = (Inventario*)malloc(sizeof(Inventario));
    strcpy(node->item, elemento);
    node->quantidade = numero;
    node->prox = p->prox;
    p->prox = node;
}

void inventario_remove (Inventario * p)
{
    Inventario * lixo = p->prox;
    p->prox = lixo->prox;
    free(lixo);
}

void inventario_procura_remove(Inventario * p, char * elemento, int numero)
{
    Inventario * AUX = inventario_cria();
    Inventario * scan = p->prox;

    while(strcmp(scan->item, elemento) != 0)
    {
        inventario_insere(AUX, scan->item,scan->quantidade);
        scan = scan->prox;
        inventario_remove(p);
    }
    scan->quantidade = scan->quantidade - numero;
    if(scan->quantidade == 0)
    {
        inventario_remove(p);
    }
    scan = AUX->prox;
    while(scan != NULL)
    {
        inventario_insere(p, scan->item,scan->quantidade);
        scan = scan->prox;
        inventario_remove(AUX);
    }
    free(AUX);
}

void inventario_imprime (Inventario * p)
{
    Inventario * scan = p->prox;
    while(scan != NULL)
    {
        printf("%s - %d\n", scan->item, scan->quantidade);
        scan = scan->prox;
    }
}
int main()
{
    FILE *file;

    struct personagem ficha;

    char input[1000];
    char fnome[100];

    printf("Digite o nome do personagem\n");
    fgets(ficha.nome,100,stdin);
    strcpy(fnome,ficha.nome);
    strcat(fnome,".txt");
    file = fopen(fnome,"a");
    fprintf(file,"Nome: %s",ficha.nome);

    printf("Digite a raca do personagem\n");
    fgets(ficha.raca,100,stdin);
    fprintf(file,"Raca: %s",ficha.raca);

    printf("Digite a classe do personagem\n");
    fgets(ficha.classe,100,stdin);
    fprintf(file,"Classe: %s",ficha.classe);

    printf("Digite o antecedente do personagem\n");
    fgets(ficha.antecedente,100,stdin);
    fprintf(file,"Antecedente: %s",ficha.antecedente);

    printf("Digite o alinhamento do personagem\n");
    fgets(ficha.alinhamento,100,stdin);
    fprintf(file,"Alinhamento: %s",ficha.alinhamento);

    printf("Digite as caracteristicas do personagem\n");
    fgets(ficha.caracteristicas,100,stdin);
    fprintf(file,"Caracteristicas: %s",ficha.caracteristicas);

    printf("Digite os talentos do personagem\n");
    fgets(ficha.talentos,100,stdin);
    fprintf(file,"Talentos: %s",ficha.talentos);

    printf("Digite os ideais do personagem\n");
    fgets(ficha.ideais,100,stdin);
    fprintf(file,"Ideais: %s",ficha.ideais);

    printf("Digite os vinculos do personagem\n");
    fgets(ficha.vinculos,100,stdin);
    fprintf(file,"Vinculos: %s",ficha.vinculos);

    printf("Digite os defeitos do personagem\n");
    fgets(ficha.defeitos,100,stdin);
    fprintf(file,"Defeitos: %s",ficha.defeitos);

    printf("Digite a personalidade do personagem\n");
    fgets(ficha.personalidade,100,stdin);
    fprintf(file,"Personalidade: %s",ficha.personalidade);

    printf("Digite a proficiencia do personagem\n");
    fgets(ficha.proficiencia,100,stdin);
    fprintf(file,"Proficiencia: %s",ficha.proficiencia);

    printf("Digite os idiomas do personagem\n");
    fgets(ficha.idiomas,100,stdin);
    fprintf(file,"Idiomas: %s",ficha.idiomas);

    fclose(file);

    Inventario * cabeca = inventario_cria();
    FILE *fileinv;
    char finvnome[100];
    strcpy(finvnome,ficha.nome);
    strcat(finvnome,"_inventario");
    strcat(finvnome,".txt");
    char scan[100];
    int n;
    int scann;
    int aux = 0;
    int num = 0;
    int i;

    printf("Digite 1 para inserir itens ao inventario, 2 para remover, 3 para voltar ao menu anterior\n");
    while(aux == 0)
    {
        scanf("%d", &n);

        if(n == 1){

            scanf("%s",scan);
            scanf("%d", &scann);
            inventario_insere(cabeca, scan, scann);
            num++;
        }
         if (n == 2){
           
            scanf("%s",scan);
            scanf("%d", &scann);
            inventario_procura_remove(cabeca, scan, scann);
            num--;
        }
         if(n == 3){
            aux = 1;
        }
    }
    fileinv = fopen(finvnome,"w");
    Inventario * x = cabeca->prox;
    while(x != NULL)
    {
        fprintf(fileinv,"%s - %d\n", x->item, x->quantidade);
        x = x->prox;
    }
    fclose(fileinv);
    
    Ataques * att = ataques_cria();
    FILE *fileat;
    char fatnome[100];
    strcpy(fatnome,ficha.nome);
    strcat(fatnome,"_ataques");
    strcat(fatnome,".txt");
    char scan1[100];
    int n1;
    char scann1[1000];
    int aux1 = 0;
    int num1 = 0;
    int i1;

    printf("Digite 1 para inserir ataques, 2 para remover, 3 para voltar ao menu anterior\n");
    while(aux1 == 0)
    {
        scanf("%d", &n1);

        if(n1 == 1){
            scanf("%s",scan1);
            scanf("%s",scann1);
            ataques_insere(att, scan1, scann1);
            num1++;
        }
         if (n1 == 2){
           
            scanf("%s",scan1);
            ataques_procura_remove(att, scan1);
            num1--;
        }
         if(n1 == 3){
            aux1 = 1;
        }
    }
    fileat = fopen(fatnome,"w");
    Ataques * y = att->prox;
    while(y != NULL)
    {
        fprintf(fileat,"%s - %s\n", y->nome, y->descricao);
        y = y->prox;
    }
    fclose(fileat);
    return 0;
}