#include <iostream>

using namespace std;

enum class TipoDoAluno
{
        TipoAluno,
        TipoRegular,
        TipoIntercambista
};

class Data
{
private:
    int dia;
    int mes;
    int ano;

public:
    Data()
    {
        dia = 0;
        mes = 0;
        ano = 0;
    }
    Data(int dia, int mes, int ano)
    {
        setDia(dia);
        setMes(mes);
        setAno(ano);
    }

    ~Data()
    {
    }

    bool setDia(int dia)
    {
        bool sucesso = false;
        if (dia >= 0 && dia <= 31)
        {
            this->dia = dia;
            sucesso = true;
        }
        return sucesso;
    }

    bool setMes(int mes)
    {
        bool sucesso = false;
        if (mes >= 0 && mes <= 12)
        {
            this->mes = mes;
            sucesso = true;
        }
        return sucesso;
    }

    bool setAno(int ano)
    {
        bool sucesso = false;
        if (ano >= -200000 && ano <= 200000)
        {
            this->ano = ano;
            sucesso = true;
        }
        return sucesso;
    }

    bool setData(int dia, int mes, int ano)
    {
        return setDia(dia) && setMes(mes) && setAno(ano);
    }
    int getDia()
    {
        return this->dia;
    }
    int getMes()
    {
        return this->mes;
    }
    int getAno()
    {
        return this->ano;
    }

    void leiaData()
    {
        int dia, mes, ano;
        cout << "Digite uma data: ";
        cin >> dia;
        cin >> mes;
        cin >> ano;
        this->setData(dia, mes, ano);
    }

    Data *getData()
    {
        return this;
    }

    void escrevaData()
    {
        cout << dia << "/" << mes << "/" << ano;
    }

    bool verifiqueMes(int mes)
    {
        bool sucesso = false;
        if (this->mes == mes)
        {
            sucesso = true;
        }
        return sucesso;
    }
    bool ehBissexto()
    {
        bool sucesso = false;
        if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0)
        {
            sucesso = true;
        }
        return sucesso;
    }

    bool verifiqueData(int data)
    {
        bool mes30 = mes == 4 || mes == 6 || mes == 9 || mes == 11;
        bool mes31 = mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12;

        bool sucesso = false;
        if (mes30)
        {
            if (dia >= 1 && dia <= 30)
                sucesso = true;
        }
        else if (mes31)
        {
            if (dia >= 1 && dia <= 31)
                sucesso = true;
        }
        else if (mes == 2)
        {
            if (ehBissexto())
            {
                if (dia >= 1 && dia <= 29)
                {
                    sucesso = true;
                }
            }
            else
            {
                if (dia >= 1 && dia <= 28)
                {
                    sucesso = true;
                }
            }
        }

        return sucesso;
    }
};

class Aluno
{
private:
    string nome;
    Data nascimento;
    static int cont;

public:
    Aluno()
    {
        cont++;
    }
    Aluno(string nome, Data nascimento)
    {
        setNome(nome);
        setNascimento(nascimento);
        cont++;
    }
    Aluno(string nome)
    {
        setNome(nome);
        Data b = Data();
        setNascimento(b);

        cont++;
    }

    virtual TipoDoAluno get_TipoDoAluno() const
    {
        return TipoDoAluno::TipoAluno;
    }

    ~Aluno()
    {
        cont--;
    }

    static void setCont(int cont)
    {
        Aluno::cont = cont;
    }
    static int getCont()
    {
        return Aluno::cont;
    }
    virtual void leiaAluno() = 0;

    void setNome(string nome)
    {
        this->nome = nome;
    }

    void setNascimento(Data DOnascimento)
    {
        nascimento.setData(DOnascimento.getDia(), DOnascimento.getMes(), DOnascimento.getAno());
    }

    string getNome()
    {
        return this->nome;
    }

    virtual void escrevaAluno() = 0;

    Data *getNascimento()
    {
        return nascimento.getData();
    }
};

class Regular : public Aluno
{
private:
    int matricula;

public:
    Regular() : Aluno()
    {
    }

    Regular(string nome, Data nascimento, int matricula) : Aluno(nome, nascimento)
    {
        setMatricula(matricula);
    }

    TipoDoAluno get_TipoDoAluno() const override
    {
        return TipoDoAluno::TipoRegular;
    }

    void setMatricula(int matricula)
    {
        this->matricula = matricula;
    }
    int getMatricula()
    {
        return this->matricula;
    }

    void leiaAluno()
    {
        string FE;
        cout << "Digite nome do aluno: ";

        cin.ignore();
        getline(cin, FE);
        setNome(FE);
        getNascimento()->leiaData();
        cout << "matricula" << endl;
        cin >> matricula;
    }

    void escrevaAluno()
    {
        cout << "nome: " << getNome();
        cout << "\nDataNascimento: ";
        getNascimento()->escrevaData();
        cout << "\n";
        cout << matricula << endl;
    }
};

class Intercambista : public Aluno
{
private:
public:
    Intercambista() : Aluno()
    {
    }

    Intercambista(string nome, Data nascimento) : Aluno(nome, nascimento)
    {
    }

     TipoDoAluno get_TipoDoAluno() const override
    {
        return TipoDoAluno::TipoIntercambista;
    }

    void leiaAluno()
    {
        string FE;
        cout << "Digite nome do aluno: ";

        cin.ignore();
        getline(cin, FE);
        setNome(FE);
        getNascimento()->leiaData();
    }

    void escrevaAluno()
    {
        cout << "nome: " << getNome();
        cout << "\nDataNascimento: ";
        getNascimento()->escrevaData();
        cout << "\n";
    }
};

void listaAlunos(Aluno *PUC[], int TAM)
{
    for (int i = 0; i < TAM; i++)
    {
        PUC[i]->escrevaAluno();
    }
}
void removerAluno(Aluno *PUC[], int TAM)
{
    int ID;
    for (int i = 0; i < TAM; i++)
    {
        cout << (i + 1) << " - " << PUC[i]->getNome() << endl;
    }
    cout << "Digite o ID do Usuario: ";
    cin >> ID;
    ID--;
    if (ID < 0 && ID >= TAM)
    {
        cout << "ERRO!, ID INVALIDO!!!";
    }
    else
    {
        delete PUC[ID];
        for (int i = ID; i < TAM - 1; i++)
        {
            PUC[i] = PUC[i + 1];
        }
    }
}

void listaRegular(Aluno *PUC[], int TAM)
{
    for (int i = 0; i < TAM; i++)
    {  
        if(PUC[i]->get_TipoDoAluno()==TipoDoAluno::TipoRegular)
        PUC[i]->escrevaAluno();
    }
}

void listaIntercambista(Aluno *PUC[], int TAM)
{
    for (int i = 0; i < TAM; i++)
    {
         if(PUC[i]->get_TipoDoAluno()==TipoDoAluno::TipoIntercambista)
        PUC[i]->escrevaAluno();
    }
}

int menu()
{
    int op;
    bool invalido = false;
   
    // imprime opcoes possiveis do menu
    cout << "MENU" << endl;
    cout << "0 - Sair programa" << endl;
    cout << "1 - Cadastrar Alunos" << endl;
    cout << "2 - Listar Alunos" << endl;
    cout << "3 - Aniversariantes do Mes" << endl;
    cout << "4 - Remover Aluno" << endl;

    // solicita opcao do usuario, repetindo leitura se invalida
    do
    {
        cout << "Digite uma opcao: " << endl;
        cin >> op;
        invalido = (op < 0 || op > 4);
        if (invalido)
            cout << "Opcao invalida! Tente novamente" << endl;
    } while (invalido);

    return op;
}

int menu2()
{
    int op;
    bool invalido = false;

    // imprime opcoes possiveis do menu
    cout << "MENU" << endl;
    cout << "0 - Retornar ao menu anterior" << endl;
    cout << "1 - Listar apenas alunos regulares" << endl;
    cout << "2 - Listar apenas alunos intercambistas" << endl;
    cout << "3 - Listar todos os alunos" << endl;

    // solicita opcao do usuario, repetindo leitura se invalida
    do
    {
        cout << "Digite uma opcao: " << endl;
        cin >> op;
        invalido = (op < 0 || op > 3);
        if (invalido)
            cout << "Opcao invalida! Tente novamente" << endl;
    } while (invalido);

    return op;
}

void listaAniversariantes(Aluno *PUC[], int TAM)
{
    int mes;
    bool invalido = false;
    do
    {

        cout << "digite o mes desejado" << endl;
        cin >> mes;
        invalido = (mes < 1 || mes > 12);
        if (invalido)
            cout << "Opcao invalida! Tente novamente" << endl;
    } while (invalido);

    for (int i = 0; i < TAM; i++)
    {
        if (PUC[i]->getNascimento()->getMes() == mes)
            PUC[i]->escrevaAluno();
    }
}

const int MAX = 100;
int Aluno::cont = 0;

int main()
{   
    cout << "SISTEMA DO CADASTRO DE ALUNOS ICEI PUC MINAS" << endl;
    Aluno *PUC[MAX];
    int op;
    int op2;

    do
    {
        op = menu();

       try
       {
        switch (op)
        {
        case 0:
            cout << "Sair programa" << endl;
            break;
        case 1:
        {   

            int selecao;

           
            int index = Aluno::getCont();

            if(index == MAX)
            {
            throw 1;
            }
            else {
            cout << " Regular=0 , Intercambista=1 " << endl;
            cin >> selecao;
            if (selecao == 0)
            {
                PUC[index] = new Regular();
            }
            else if (selecao == 1)
            {
                PUC[index] = new Intercambista();
            }
            
            PUC[index]->leiaAluno();
            }
            break;
            
        }
        case 2:
        {

            do
            {
                op2 = menu2();
                switch (op2)
                {
                case 0:
                    cout << "Retornando ao menu anterior" << endl;
                    break;

               case 1:
                    listaRegular(PUC, Aluno::getCont());
                           break;

                   case 2:
                           listaIntercambista(PUC, Aluno::getCont());
                           break;

                case 3:
                    listaAlunos(PUC, Aluno::getCont());
                    break;
                }

            } while (op2 != 0);
            break;
        }
        case 3:
            listaAniversariantes(PUC, Aluno::getCont());
            break;
        case 4:
            removerAluno(PUC, Aluno::getCont());
            break;
        }
       }catch(...){
            op = menu();
       }
           
    } while (op != 0);

    return 0;
}
