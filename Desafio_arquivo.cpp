//MARIO CELSO DE ALMEIDA MORAES JUNIOR

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include <iomanip>
#include <cctype>

using namespace std;

class ALUNO
{
    public:
        int PRONTUARIO;
        char NOME[50];
        float NOTA[4];
        int MATRICULADO;
};

void NOVOARQUIVO();
void CADASTRO();
void LISTAR();
void EDITAR();
void PESQUISAR();
void EXCLUIR();

int I;


void NOVOARQUIVO()
{
    ofstream arqalunosDADOS;
    arqalunosDADOS.open("arqalunos.txt", ios_base::trunc);
    arqalunosDADOS.close();
}


void CADASTRO()
{   ALUNO aluno;

    setlocale(LC_ALL, "");


    cout << " CADASTRAR ALUNO ";

    cout << "\n\n DIGITE O PRONTUÁRIO: ";
    cin  >> aluno.PRONTUARIO;
    cin.ignore(80, '\n');

    cout << " DIGITE O NOME: ";
    cin.getline(aluno.NOME, sizeof(aluno.NOME));
    cin.ignore(80, '\n');

    for(I = 0; I < 4; I++)
    {
        cout << " DIGITE A NOTA " << I+1 << " : ";
        cin  >> aluno.NOTA[I];
        cin.ignore(80, '\n');
    }

    aluno.MATRICULADO = 1;

    fstream arqalunosDADOS;
    arqalunosDADOS.open("arqalunos.txt", ios::out | ios::app | ios::binary);
    arqalunosDADOS.seekp(0, ios::end);
    arqalunosDADOS.write(reinterpret_cast<char*>(&aluno), sizeof(ALUNO));
    arqalunosDADOS.flush();
    arqalunosDADOS.close();

}


void EDITAR()
{   setlocale(LC_ALL, "");


    cout << " ALTERAR ALUNO \n";
    //
    int codEdit, posrgstro = -1, contador = 0;
    ALUNO aluno;

    cout << "\n DIGITE O PRONTUÁRIO DO ALUNO: ";
    cin  >> codEdit;
    cin.ignore(80, '\n');

    ifstream arqalunosDADOS("arqalunos.txt", ios::binary);
    arqalunosDADOS.seekg(0, ios::beg);

    while(arqalunosDADOS.read(reinterpret_cast<char*>(&aluno), sizeof(ALUNO)))
    {
        if(aluno.PRONTUARIO == codEdit && aluno.MATRICULADO == 1)
        {
            cout << "\n ALUNO A SER EDITADO \n";

            cout << "\n DIGITE O PRONTUÁRIO: ";
            cin  >> aluno.PRONTUARIO;
            cin.ignore(80, '\n');

            cout << " DIGITE O NOME: ";
            cin.getline(aluno.NOME, sizeof(aluno.NOME));

            for(I = 0; I < 4; I++)
            {
                cout << " DIGITE A NOTA " << I+1 << " : ";
                cin  >> aluno.NOTA[I];
                cin.ignore(80, '\n');
            }

            posrgstro = contador;
            break;
        }

        contador++;
    }

    arqalunosDADOS.close();

    if(posrgstro > -1)
    {
        char confirma;
        cout << "\n CONFIRMAR EDIÇÃO? (s/n): ";
        cin  >> confirma;
        cin.ignore(80, '\n');

        if(confirma == 'S' || confirma == 's')
        {
            fstream arqalunosDADOS("arqalunos.txt", ios::in | ios::out | ios::binary);

            arqalunosDADOS.seekp(posrgstro * sizeof(ALUNO), ios::beg);
            arqalunosDADOS.write((char*)&aluno, sizeof(ALUNO));
            arqalunosDADOS.flush();
            arqalunosDADOS.close();
        }
    }
    else
    {
        cout << " ALUNO NÃO ENCONTRADO \n";
    }
}


void LISTAR()
{   setlocale(LC_ALL, "");

    float soma = 0, media = 0;

    cout << " ALUNOS MATRICULADOS \n";

    fstream arqalunosDADOS;
    arqalunosDADOS.open("arqalunos.txt", ios::in | ios::app | ios::binary);
    arqalunosDADOS.seekg(0, ios::beg);

    ALUNO aluno;

    while(arqalunosDADOS.read(reinterpret_cast<char*>(&aluno), sizeof(ALUNO)))
    {
        if(aluno.MATRICULADO == 1)
        {
            cout << "\n PRONTUÁRIO: " << aluno.PRONTUARIO;
            cout << endl;
            cout << "\n NOME: " << aluno.NOME;
            cout << endl;
             for(I = 0; I < 4; I++)
                {
                    cout << "\n NOTA: " << aluno.NOTA[I] << endl;
                    soma += aluno.NOTA[I];
                }

                media = soma / 4;
                cout << "\n MÉDIA: " << media;
                soma = 0;
                cout << endl;
                 cout << "--------------------------------" <<endl;

        }
    }
    cout << endl;
    cout << " TECLE <ENTER> PARA VOLTAR AO MENU";
    cin.ignore(80, '\n');
    arqalunosDADOS.close();
}


void PESQUISAR()
{   setlocale(LC_ALL, "");

    float media, soma;
    char confirma;


    cout << " PESQUISAR ALUNO \n ";

    int pesqpront, posrgstro = -1, contador = 0;
    ALUNO aluno;


    ifstream arqalunosDADOS("arqalunos.txt", ios::binary);
    arqalunosDADOS.seekg(0, ios::beg);

        cout << "\n DIGITE O PRONTUÁRIO A SER PESQUISADO: ";
        cin  >> pesqpront;
        cin.ignore(80, '\n');

        while(arqalunosDADOS.read(reinterpret_cast<char*>(&aluno), sizeof(ALUNO)))
        {
            if(aluno.PRONTUARIO == pesqpront && aluno.MATRICULADO == 1)
            {
                cout << endl;
                cout << "\n PRONTUÁRIO: " << aluno.PRONTUARIO;
                cout << endl;
                cout << "\n NOME: " << aluno.NOME;
                cout << endl;
                for(I = 0; I < 4; I++)
                {
                    cout << "\n NOTA: " << aluno.NOTA[I] << endl;
                    soma += aluno.NOTA[I];
                }

                media = soma / 4;
                cout << "\n MÉDIA: " << media;
                soma = 0;
                cout << endl;
                posrgstro = contador;
            }

            else
                {
                  cout << "\n ALUNO NÃO ENCONTRADO \n ";
                }

        }






    arqalunosDADOS.close();
}


void EXCLUIR()
{   setlocale(LC_ALL, "");


    cout << " EXCLUIR ALUNO \n";

    int codExcluir, posrgstro = -1, contador = 0;
    ALUNO aluno;

    cout << "\n DIGITE O PRONTUÁRIO A SER EXCLUÍDO: ";
    cin  >> codExcluir;
    cin.ignore(80, '\n');

    ifstream arqalunosDADOS("arqalunos.txt", ios::binary);
    arqalunosDADOS.seekg(0, ios::beg);

    while(arqalunosDADOS.read(reinterpret_cast<char*>(&aluno), sizeof(ALUNO)))
    {
        if(aluno.PRONTUARIO == codExcluir && aluno.MATRICULADO == 1)
        {
            cout << endl;
            cout << " ALUNO A SER EXCLUÍDO \n";
            cout << endl;
            cout << "\n PRONTUÁRIO: " << aluno.PRONTUARIO;
            cout << endl;
            cout << "\n NOME: " << aluno.NOME;
            cout << endl;

            aluno.MATRICULADO = 0;
            posrgstro = contador;
            break;
        }

        contador++;
    }

    arqalunosDADOS.close();

    if(posrgstro > -1)
    {
        char confirma;
        cout << "\n CONFIRMAR EXCLUSÃO (s/n): ";
        cin  >> confirma;
        cin.ignore(80, '\n');

        if(confirma == 'S' || confirma == 's')
        {
            fstream arqalunosDADOS("arqalunos.txt", ios::in | ios::out | ios::binary);

            arqalunosDADOS.seekp(posrgstro * sizeof(ALUNO), ios::beg);
            arqalunosDADOS.write(reinterpret_cast<char*>(&aluno), sizeof(ALUNO));
            arqalunosDADOS.flush();
            arqalunosDADOS.close();
        }
    }
    else
    {
        cout << " ALUNO NÃO ENCONTRADO ";
    }
}


//ROTINA DE MENU

int main()
{   setlocale(LC_ALL, "");

    fstream arqalunosDADOS("arqalunos.txt", ios_base::in | ios_base :: binary);
    if(arqalunosDADOS.fail())
        NOVOARQUIVO();

    int I = 0, J;
    int opcao = 0;

    do
    {
        cout << setprecision(2);
        cout << setiosflags(ios::right);
        cout << setiosflags(ios::fixed);

        cout << "\n";
        cout << "   SISTEMA ESCOLAR   " << endl;
        cout << "\n";
        cout << "   MENU PRINCIPAL   " << endl;
        cout << "\n";
        cout << " 1. CADASTRAR ALUNO" << endl;
        cout << " 2. EDITAR ALUNO" << endl;
        cout << " 3. LISTAR ALUNOS" << endl;
        cout << " 4. PESQUISAR ALUNO" << endl;
        cout << " 5. EXCLUIR ALUNO" << endl;
        cout << " 6. SAIR" << endl;

        cout << " \n OPÇÃO: ";  cin >> opcao;
        cin.ignore(80, '\n');
        cout << endl << endl;


        if(opcao != 6)
        {
            switch (opcao)
            {
                case 1:
                    CADASTRO();break;

                case 2:
                    EDITAR();break;

                case 3:
                    LISTAR();break;

                case 4:
                    PESQUISAR();break;

                case 5:
                    EXCLUIR();break;
            }
        }
    }
    while(opcao != 6);

}

