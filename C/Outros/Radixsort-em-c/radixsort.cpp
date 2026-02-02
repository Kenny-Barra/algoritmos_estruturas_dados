#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TAM 1000

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
void radixsort();
void salvarArq(double tempo);
void operations(int numopr);
char *processendr(char *endr,int operation);
void imprimir();
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
void inserirInicio(char* endr);
void inserirFim(char* endr);
void inserir(char* endr,int pos);
Personagem removerInicio();
Personagem removerFim();
Personagem remover(int pos);

Personagem personagens[500];
int nump=0;
char removidos[TAM][100];
int numremovidos=0;
int numcpr=0;
int nummov=0;

int main()
{
    clock_t tempo;
    char endr[TAM];
    int numopr;
    double tmp=0;

    tempo=clock();

    scanf(" %[^\n]", endr );

    while(strcmp(endr,"FIM")!=0)
    {
        inserirFim(endr);
        scanf(" %[^\n]", endr );
    }

    imprimir();

    tempo=clock()-tempo;
    tmp=(((double)tempo)/((double)((CLOCKS_PER_SEC/1000))));

    salvarArq(tmp);

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

void radixsort() 
{
	int i, exp = 1, m = 0, bucket[nump];
    Personagem temp[nump];

	for(i = 0; i < nump; i++)
    {
        numcpr+=2;
		if(personagens[i].altura > m)
        {
			m = personagens[i].altura;
		}
	}

	while((m/exp) > 0)
    {
		for (i = 0; i < nump; i++)
        {
            numcpr++;
			bucket[i] = 0;
		}
		for(i = 0; i < nump; i++) 
        {
            numcpr++;
			bucket[(personagens[i].altura / exp) % 10]++;
		}
		for(i = 1; i < nump; i++)
        {
            numcpr++;
			bucket[i] += bucket[i-1];
		}
		for(i = (nump - 1); i >= 0; i--)
        {
            numcpr++;
            nummov++;
			temp[--bucket[(personagens[i].altura / exp) % 10]] = personagens[i];
		}
		for(i = 0; i < nump; i++)
        {
            numcpr++;
			personagens[i] = temp[i];
		}

		exp *= 10;
	}
}

void salvarArq(double tempo)
{
    FILE *arq;

    arq = fopen("matricula_radixsort.txt", "wt");

    if (arq == NULL)
    {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    fprintf(arq,"645412\t%lf\t%d\t%d",tempo,numcpr,nummov);

    fclose(arq);
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

        if(strstr(operation,"II"))
        {
            strcpy(endr,processendr(linha,1));
            inserirInicio(endr);
        }
        else if(strstr(operation,"I*"))
        {
            strcpy(endr,processendr(linha,2));
            posi=atoi(processendr(linha,1));
            inserir(endr,posi);
        }
        else if(strstr(operation,"IF"))
        {
            strcpy(endr,processendr(linha,1));
            inserirFim(endr);
        }
        else if(strstr(operation,"RI"))
        {
            p=removerInicio();
            //printf("%s",p.nome);
            strcpy(removidos[numremovidos],"(R) ");
            strcat(removidos[numremovidos],p.nome);
            numremovidos++;
        }
        else if(strstr(operation,"R*"))
        {
            posi=atoi(processendr(linha,1));
            p=remover(posi);
            //printf("%s",p.nome);
            strcpy(removidos[numremovidos],"(R) ");
            strcat(removidos[numremovidos],p.nome);
            numremovidos++;
        }
        else if(strstr(operation,"RF"))
        {
            p=removerFim();
            strcpy(removidos[numremovidos],"(R) ");
            strcat(removidos[numremovidos],p.nome);
            numremovidos++;
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

void imprimir()
{
    int i;
    radixsort();

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

void inserirInicio(char* endr)
{
    Personagem p=leitura(endr);
    int i;

    if(nump >= TAM)
    {
        printf("Erro ao inserir!");
        exit(1);
    } 

    for(i = nump; i > 0; i--)
    {
        personagens[i] = personagens[i-1];
    }

    personagens[0] = p;
    nump++;
}

void inserirFim(char* endr)
{
    Personagem p=leitura(endr);

    if(nump>=TAM)
    {
        printf("Erro ao inserir!\n");
        exit(1);
    }

    personagens[nump] = p;
    nump++;
}

void inserir(char* endr,int pos)
{
    Personagem p=leitura(endr);
    int i;

    if(nump >= TAM || pos < 0 || pos > nump)
    {
        printf("Erro ao inserir!");
        exit(1);
    }

    for(i = nump; i > pos; i--)
    {
        personagens[i] = personagens[i-1];
    }

    personagens[pos] = p;
    nump++;
}

Personagem removerInicio()
{
    int i;
    Personagem resp;

    if(nump == 0)
    {
        printf("Erro ao remover!");
        exit(1);
    }

    resp = personagens[0];
    nump--;

    for(i = 0; i < nump; i++)
    {
        personagens[i] = personagens[i+1];
    }

    return resp;
}

Personagem removerFim()
{
    if (nump == 0)
    {
        printf("Erro ao remover!");
        exit(1);
    }

    return personagens[--nump];
}

Personagem remover(int pos)
{
    int i;
    Personagem resp;

    if (nump == 0 || pos < 0 || pos >= nump)
    {
        printf("Erro ao remover!");
        exit(1);
    }

    resp = personagens[pos];
    nump--;

    for(i = pos; i < nump; i++)
    {
        personagens[i] = personagens[i+1];
    }

    return resp;
}