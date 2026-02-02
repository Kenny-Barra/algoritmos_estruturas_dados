import java.io.*;
import java.util.*;

public class classe
{
    public static Personagem[] personagens = new Personagem[500];//vetor para salvar os objetos
    public static int nump=0;//contador de objetos criados

    public static void main(String[] args) throws Exception
    {
        MyIO.setCharset("UTF-8");
        String endr = MyIO.readLine(); //recebe o primeiro 'link' do personagem

        while(!endr.equals("FIM")) //verifica ate achar 'FIM'
        {
            personagens[nump]=new Personagem(); //estancia um novo objeto na posição do vetor
            leiturapersonagem(endr);
            nump++; //soma um ao contador de personagens criados
            endr = MyIO.readLine(); //recebe o proximo 'link' do personagem
        }

        MyIO.setCharset("ISO-8859-1");
        imprimir();
    }

    public static void leiturapersonagem(String endr) throws Exception 
    {//metodo para ler o arquivo e separar as informações
        String refname = "name: ";
        String refheigth = ", height: ";
        String refmass = ", mass: ";
        String refhaircolor = ", hair_color: ";
        String refskincolor = ", skin_color: ";
        String refeyecolor = ", eye_color: ";
        String refbirthyear = ", birth_year: ";
        String refgender = ", gender: ";
        String refhomeworld = ", homeworld: ";

        BufferedReader Arquivo = new BufferedReader(new InputStreamReader(new FileInputStream(endr), "UTF8")); //abre um bufferedreader para ler o arquivo recebido por parametro
        String linha = Arquivo.readLine(); //le as informações do arquivo
        
        linha = linha.replaceAll("\'",""); //retira todas as aspas simples das informações do arquivo
        linha = linha.replaceAll(", films:.*?}","");

        name(linha,refname,refheigth);
        height(linha,refheigth,refmass);
        mass(linha,refmass,refhaircolor);
        haircolor(linha,refhaircolor,refskincolor);
        skincolor(linha,refskincolor,refeyecolor);
        eyecolor(linha,refeyecolor,refbirthyear);
        birthyear(linha,refbirthyear,refgender);
        gender(linha,refgender,refhomeworld);
        homeworld(linha,refhomeworld);
    }

    public static void name(String linha,String refinicio, String reffim)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.indexOf(reffim);

        personagens[nump].setnome(linha.substring(inicio,fim));
    }

    public static void height(String linha,String refinicio, String reffim)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.indexOf(reffim);
        String substr=linha.substring(inicio,fim);
        substr=substr.replaceAll(",","");

        if(!(substr.equals("none")|| substr.equals("unknown")))
        {
            personagens[nump].setaltura(Integer.parseInt(substr));
        }
    }

    public static void mass(String linha,String refinicio, String reffim)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.indexOf(reffim);
        String substr=linha.substring(inicio,fim);
        substr=substr.replaceAll(",","");

        if(!(substr.equals("none")|| substr.equals("unknown")))
        {
            personagens[nump].setpeso(Double.parseDouble(substr));
        }
    }

    public static void haircolor(String linha,String refinicio, String reffim)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.indexOf(reffim);

        personagens[nump].setcorDoCabelo(linha.substring(inicio,fim));
    }

    public static void skincolor(String linha,String refinicio, String reffim)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.indexOf(reffim);

        personagens[nump].setcorDaPele(linha.substring(inicio,fim));
    }

    public static void eyecolor(String linha,String refinicio, String reffim)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.indexOf(reffim);

        personagens[nump].setcorDosOlhos(linha.substring(inicio,fim));
    }

    public static void birthyear(String linha,String refinicio, String reffim)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.indexOf(reffim);

        personagens[nump].setanoNascimento(linha.substring(inicio,fim));
    }

    public static void gender(String linha,String refinicio, String reffim)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.indexOf(reffim);

        personagens[nump].setgenero(linha.substring(inicio,fim));
    }

    public static void homeworld(String linha,String refinicio)
    {
        int inicio=linha.indexOf(refinicio)+refinicio.length();
        int fim=linha.length();

        personagens[nump].sethomeworld(linha.substring(inicio,fim));
    }

    public static void imprimir()
    {
        for(int i=0;i<nump;i++)
        {
            System.out.print(" ## "+personagens[i].getnome()+" ## "+personagens[i].getaltura()+" ## ");

            if(personagens[i].getpeso()==(int)personagens[i].getpeso())
            {
                System.out.print((int)personagens[i].getpeso());
            }
            else
            {
                System.out.print(personagens[i].getpeso());
            }
            
            System.out.println(" ## "+ personagens[i].getcorDoCabelo()+" ## "+personagens[i].getcorDaPele()+" ## "+personagens[i].getcorDosOlhos()+" ## "+
            personagens[i].getanoNascimento()+" ## "+personagens[i].getgenero()+" ## "+personagens[i].gethomeworld()+" ##");
        }
    }
}

class Personagem
{
    private String nome;
    private String corDoCabelo;
    private String corDaPele;
    private String corDosOlhos;
    private String anoNascimento;
    private String genero;
    private String homeworld;
    private int altura;
    private double peso;

    public Personagem()
    {
        this.nome="";
        this.corDoCabelo="";
        this.corDaPele="";
        this.corDosOlhos="";
        this.anoNascimento="";
        this.genero="";
        this.homeworld="";
        this.altura=0;
        this.peso=0;
    }

    public Personagem(String nome,String corDoCabelo,String corDaPele,String corDosOlhos,String anoNascimento,
    String genero,String homeworld,int altura,double peso)
    {
        this.nome=nome;
        this.corDoCabelo=corDoCabelo;
        this.corDaPele=corDaPele;
        this.corDosOlhos=corDosOlhos;
        this.anoNascimento=anoNascimento;
        this.genero=genero;
        this.homeworld=homeworld;
        this.altura=altura;
        this.peso=peso;
    }

    public void setnome(String nome)
    {
        this.nome=nome;
    }

    public void setcorDoCabelo(String corDoCabelo)
    {
        this.corDoCabelo=corDoCabelo;
    }

    public void setcorDaPele(String corDaPele)
    {
        this.corDaPele=corDaPele;
    }

    public void setcorDosOlhos(String corDosOlhos)
    {
        this.corDosOlhos=corDosOlhos;
    }

    public void setanoNascimento(String anoNascimento)
    {
        this.anoNascimento=anoNascimento;
    }

    public void setgenero(String genero)
    {
        this.genero=genero;
    }

    public void sethomeworld(String homeworld)
    {
        this.homeworld=homeworld;
    }

    public void setaltura(int altura)
    {
        this.altura=altura;
    }

    public void setpeso(double peso)
    {
        this.peso=peso;
    }

    public String getnome()
    {
        return this.nome;
    }

    public String getcorDoCabelo()
    {
        return this.corDoCabelo;
    }

    public String getcorDaPele()
    {
        return this.corDaPele;
    }

    public String getcorDosOlhos()
    {
        return this.corDosOlhos;
    }

    public String getanoNascimento()
    {
        return this.anoNascimento;
    }

    public String getgenero()
    {
        return this.genero;
    }

    public String gethomeworld()
    {
        return this.homeworld;
    }

    public int getaltura()
    {
        return this.altura;
    }

    public double getpeso()
    {
        return this.peso;
    }

    public Personagem clone()
    {
        Personagem p = new Personagem();

        p.setnome(this.nome);
        p.setcorDoCabelo(this.corDoCabelo);
        p.setcorDaPele(this.corDaPele);
        p.setcorDosOlhos(this.corDosOlhos);
        p.setanoNascimento(this.anoNascimento);
        p.setgenero(this.genero);
        p.sethomeworld(this.homeworld);
        p.setaltura(this.altura);
        p.setpeso(this.peso);

        return p;
    }
}