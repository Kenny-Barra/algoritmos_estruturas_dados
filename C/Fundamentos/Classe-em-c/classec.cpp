#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void leitura(char* endr);
void imprimir();
void name(char* linha,char* refinicio, char* reffim);
void height(char* linha,char* refinicio, char* reffim);
void mass(char* linha,char* refinicio, char* reffim);
void haircolor(char* linha,char* refinicio, char* reffim);
void skincolor(char* linha,char* refinicio, char* reffim);
void eyecolor(char* linha,char* refinicio, char* reffim);
void birthyear(char* linha,char* refinicio, char* reffim);
void gender(char* linha,char* refinicio, char* reffim);
void homeworld(char* linha,char* refinicio, char* reffim);
long int idx(const char *padrao,char *entrada);
char *substr(int inicio,int fim, char* entrada);
char *repl( char* entrada,const char* pAntiga, const char* pNova);

Personagem personagens[500];
int nump=0;

int main()
{
    char endr[1000];

    scanf(" %[^\n]", endr );

    while(strcmp(endr,"FIM")!=0)
    {
        leitura(endr);
        nump++;
        scanf(" %[^\n]", endr );
    }

    imprimir();

    return 0;
}

void leitura(char* endr)
{
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

    name(linha,refname,refheigth);
    height(linha,refheigth,refmass);
    mass(linha,refmass,refhaircolor);
    haircolor(linha,refhaircolor,refskincolor);
    skincolor(linha,refskincolor,refeyecolor);
    eyecolor(linha,refeyecolor,refbirthyear);
    birthyear(linha,refbirthyear,refgender);
    gender(linha,refgender,refhomeworld);
    homeworld(linha,refhomeworld,reffim);

    fclose(file);
    free(linha);

}

void imprimir()
{
    int i;

    for(i=0;i<nump;i++)
    {
        printf(" ## %s ## %d ## ",personagens[i].nome,personagens[i].altura);
         
        if(personagens[i].peso==(int)personagens[i].peso)
        {
            printf("%d",(int)personagens[i].peso);
        }
        else
        {
            printf("%.1lf",personagens[i].peso);
        }
        
        printf(" ## %s ## %s ## %s ## %s ## %s ## %s ## \n",personagens[i].corDoCabelo,personagens[i].corDaPele,personagens[i].corDosOlhos,
        personagens[i].anoNascimento,personagens[i].genero,personagens[i].homeworld);

        //printf(" \n");
    }
}

void name(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(personagens[nump].nome,substr(inicio,fim,linha));
}

void height(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);
    char substring[15];
    strcpy(substring,substr(inicio,fim,linha));

    if(!(strcmp(substring,"none")==0 || strcmp(substring,"unknown")==0))
    {
        personagens[nump].altura=atoi(substring);
    }
    else
    {
        personagens[nump].altura=0;
    }
}

void mass(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);
    char substring[15];
    strcpy(substring,substr(inicio,fim,linha));
    repl(substring,",","");

    if(!(strcmp(substring,"none")==0 || strcmp(substring,"unknown")==0))
    {
        personagens[nump].peso=atof(substring);
    }
    else
    {
        personagens[nump].peso=0;
    }
}

void haircolor(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(personagens[nump].corDoCabelo,substr(inicio,fim,linha));
}

void skincolor(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(personagens[nump].corDaPele,substr(inicio,fim,linha));
}

void eyecolor(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(personagens[nump].corDosOlhos,substr(inicio,fim,linha));
}

void birthyear(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(personagens[nump].anoNascimento,substr(inicio,fim,linha));
}

void gender(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(personagens[nump].genero,substr(inicio,fim,linha));
}

void homeworld(char* linha,char* refinicio, char* reffim)
{
    int inicio=idx(refinicio,linha)+strlen(refinicio);
    int fim=idx(reffim,linha);

    strcpy(personagens[nump].homeworld,substr(inicio,fim,linha));
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