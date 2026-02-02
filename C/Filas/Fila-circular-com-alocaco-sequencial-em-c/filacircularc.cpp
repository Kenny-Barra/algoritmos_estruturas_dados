#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define TAM 500

typedef struct Personagem
{
    char nome[200];
    char corDoCabelo[200];
    char corDaPele[200];
    char corDosOlhos[200];
    char anoNascimento[200];
    char genero[200];
    char homeworld[200];
    int altura;
    double peso;
}Personagem;

Personagem leitura(char* endr);
void operations(int numopr);
char *processendr(char *endr,int operation);
void name(Personagem *p,char* linha,char* refinicio, char* reffim);
void height(Personagem *p,char* linha,char* refinicio, char* reffim);
void mass(Personagem *p,char* linha,char* refinicio, char* reffim);
void haircolor(Personagem *p,char* linha,char* refinicio, char* reffim);
void skincolor(Personagem *p,char* linha,char* refinicio, char* reffim);
void eyecolor(Personagem *p,char* linha,char* refinicio, char* reffim);
void birthyear(Personagem *p,char* linha,char* refinicio, char* reffim);
void gender(Personagem *p,char* linha,char* refinicio, char* reffim);
void homeworld(Personagem *p,char* linha,char* refinicio, char* reffim);
long int idx(const char *padrao,char *entrada);
char *substr(int inicio,int fim, char* entrada);
char *repl( char* entrada,const char* pAntiga, const char* pNova);
void inserir(char* endr);
Personagem remover();
int validaentrada();

Personagem personagens[6];
int nump=0;
int primeiro=0;
int ultimo=0;
double media=0;
int resposta;

int main()
{
    char endr[TAM];
    int numopr;

    scanf(" %[^\n]", endr );

    while(strcmp(endr,"FIM")!=0)
    {
        if(validaentrada()==0)
        {
            remover();
        }

        inserir(endr);
        resposta=(int)round(media/nump);
        printf("%d\n",resposta);
        scanf(" %[^\n]", endr );
    }

    scanf("%d",&numopr);

    operations(numopr);

    return 0;
}

Personagem leitura(char* endr)
{
    Personagem p;

    char refname[25] = "'name': '";
    char refheigth[25] = "', 'height': '";
    char refmass[25] = "', 'mass': '";
    char refhaircolor[25] = "', 'hair_color': '";
    char refskincolor[25] = "', 'skin_color': '";
    char refeyecolor[25] = "', 'eye_color': '";
    char refbirthyear[25] = "', 'birth_year': '";
    char refgender[25] = "', 'gender': '";
    char refhomeworld[25] = "', 'homeworld': '";
    char reffim[25] = "', 'films':";

    char *linha = NULL;
    FILE *file = fopen(endr,"rb");
    size_t len = 0;

    if(file == NULL)
    {
        printf("Error");
        exit(1);
    }//end if        
    else 
    {
        getline(&linha,&len,file);
    }

    name(&p,linha,refname,refheigth);
    height(&p,linha,refheigth,refmass);
    mass(&p,linha,refmass,refhaircolor);
    haircolor(&p,linha,refhaircolor,refskincolor);
    skincolor(&p,linha,refskincolor,refeyecolor);
    eyecolor(&p,linha,refeyecolor,refbirthyear);
    birthyear(&p,linha,refbirthyear,refgender);
    gender(&p,linha,refgender,refhomeworld);
    homeworld(&p,linha,refhomeworld,reffim);

    fclose(file);
    free(linha);

    return p;
}

void operations(int numopr)
{
    Personagem p;
    char linha[100]="";
    char operation[10]="";
    char endr[100]="";
    int posi,i;

    for(int i=0;i<numopr;i++)
    {
        scanf(" %[^\n]",linha);
        strcpy(operation,processendr(linha,0));


        if(strstr(operation,"I"))
        {
            if(validaentrada()==0)
            {
                remover();
            }

            strcpy(endr,processendr(linha,1));
            inserir(endr);
            resposta=(int)round(media/nump);
            printf("%d\n",resposta);
        }
        else if(strstr(operation,"R"))
        {
            p=remover();
            printf("%s%s\n","(R) ",p.nome);
        }
    }

}

char *processendr(char *endr,int operation)
{
    char clearendr[3][100];
    char aux[strlen(endr)];
    strcpy(aux,endr);
    char* pCorrente;
    char *resp=(char*) malloc(100);;
    int n=0;

    for(pCorrente= strtok(aux," "); pCorrente!=NULL ;pCorrente= strtok(NULL," "),n++)
    {
        strcpy(clearendr[n],pCorrente);
    }//end for

    strcpy(resp,clearendr[operation]);
    return resp;
}

void name(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(p->nome,substr(inicio,fim,linha));
}

void height(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);
    char substring[15];
    strcpy(substring,substr(inicio,fim,linha));

    if(!(strcmp(substring,"none")==0 || strcmp(substring,"unknown")==0))
    {
        p->altura=atoi(substring);
    }
    else
    {
        p->altura=0;
    }
}

void mass(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);
    char substring[15];
    strcpy(substring,substr(inicio,fim,linha));
    repl(substring,",","");

    if(!(strcmp(substring,"none")==0 || strcmp(substring,"unknown")==0))
    {
        p->peso=atof(substring);
    }
    else
    {
        p->peso=0;
    }
}

void haircolor(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(p->corDoCabelo,substr(inicio,fim,linha));
}

void skincolor(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(p->corDaPele,substr(inicio,fim,linha));
}

void eyecolor(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(p->corDosOlhos,substr(inicio,fim,linha));
}

void birthyear(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(p->anoNascimento,substr(inicio,fim,linha));
}

void gender(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(p->genero,substr(inicio,fim,linha));
}

void homeworld(Personagem *p,char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(p->homeworld,substr(inicio,fim,linha));
}

long int idx(const char *padrao,char *entrada)
{
    int pos=0;
    if(strstr(entrada, padrao)!=NULL){
        char *pointer = strstr(entrada, padrao);
        pos=pointer-entrada;
    }//end if 
    return pos;
}//end idx

char* substr(int inicio,int fim, char* entrada)
{
    int tamanho=fim-inicio;      
    char *substring = (char*) malloc(6000);
    int j=0;
    int i;

    for(i=inicio;i<fim;i++,j++){
        substring[j]=entrada[i];
    }//end for
    
    substring[j]='\0';
    return substring;
}//end substring teste

char *repl( char* entrada,const char* pAntiga, const char* pNova)
{

    if(strstr(entrada,pAntiga))
    {
        for(int inicio = idx(pAntiga, entrada); strstr(entrada, pAntiga )!=NULL; inicio = idx(pAntiga, entrada))
        { 
            strcpy(entrada,strcat(strcat(substr(0,inicio,entrada),pNova),entrada+inicio+strlen(pAntiga)));
        }//end for
    } 
    return entrada;
}//end replace

void inserir(char* endr)
{
    Personagem p=leitura(endr);
    int i;

    if(((ultimo + 1) % 6) == primeiro)
    {
        printf("Erro ao inserir!");
        exit(1);
    }

    media+=p.altura;
    nump++;
    personagens[ultimo] = p;
    ultimo = (ultimo + 1) % 6;
}

Personagem remover()
{
    int i;
    Personagem resp;

    if (primeiro == ultimo)
    {
        printf("Erro ao remover!");
        exit(1);
    }

    resp = personagens[primeiro];
    media-=resp.altura;
    nump--;
    primeiro = (primeiro + 1) % 6;

    return resp;
}

int validaentrada()
{
    int resposta=1;

    if(((ultimo + 1) % 6) == primeiro)
    {
        resposta=0;
    }

    return resposta;
}