#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>

using namespace std;

struct Aluno {
    int codigo;
    string nome;
    string sobrenome;
};

struct ListaDePresenca {
    int codigoAluno;
    int quantidadeDeAusencias;
    int quantidadeDeAulas;
};

struct Notas {
    int codigoAluno;
    float avaliacoes[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int quantidadeDeNotas;
};

void exibeMenu();

void gerenciarOpcaoA(Aluno aluno[], Notas notas[], ListaDePresenca listaDePresenca[]);

void gerenciarOpcaoB(ListaDePresenca listaDePresenca[]);

void gerenciarOpcaoC(Notas notas[]);

bool gerenciarOpcaoD(Notas notas[], ListaDePresenca listaDePresenca[]);

bool imprimirArquivo(ofstream &saida, Notas *notas, ListaDePresenca * listaDePresenca);

int totalDeAlunosCadastrados = 0;
const int MAXIMO_DE_ALUNOS = 5;
Aluno aluno[MAXIMO_DE_ALUNOS];
ListaDePresenca listaDePresenca[MAXIMO_DE_ALUNOS];
Notas notas[MAXIMO_DE_ALUNOS];

int main(){

    char opcao = ' ';

    while( opcao != 'E' ) {
        exibeMenu();
        cin >> opcao;
        opcao = toupper(opcao);

        if(opcao == 'A'){
            gerenciarOpcaoA(aluno, notas, listaDePresenca);
        } else if (opcao == 'B') {
            gerenciarOpcaoB(listaDePresenca);
        } else if (opcao == 'C') {
            gerenciarOpcaoC(notas);
        } else if (opcao == 'D') {
            if( gerenciarOpcaoD(notas, listaDePresenca) ){
                cout << endl << "*** Fim do relatorio ***" << endl;
            } else {
                cout << endl << "*** Relatorio sem dados ***" << endl;
            }
            string arquivo = "ESCOLA.txt";

            ofstream saida((arquivo).c_str(), ios::out);

            bool imprimirArquivoComSucesso;

            if(!saida){
                cerr << "Arquivo nao pode ser aberto\n";
                exit(1);
            } else {
                imprimirArquivoComSucesso = imprimirArquivo(saida,notas,listaDePresenca);
            }

            if(imprimirArquivoComSucesso) {
                cout << endl << "Arquivo imprimido com sucesso !" << endl;
            } else {
                cout << endl << "Erro ao imprimir arquivo !" << endl;
            }

        } else if (opcao != 'A' && opcao != 'B' && opcao != 'C' && opcao != 'D' && opcao != 'E') {
            cout << endl << "Opcao invalida !" << endl << endl;
        }
    }
	return 0;
}

void exibeMenu( ) {
    cout << "\n[Digite A para] Registrar aluno" << endl;
    cout << "[Digite B para] Fazer chamada" << endl;
    cout << "[Digite C para] Registrar notas" << endl;
    cout << "[Digite D para] Imprimir relatorio de notas e faltas da turma" << endl;
    cout << "[Digite E para] Sair" << endl << endl;
    cout << "Digite a opcao : " ;
}


void gerenciarOpcaoA(Aluno aluno[], Notas notas[], ListaDePresenca listaDePresenca[]){
    do {
        cout << endl << "Digite o codigo do aluno: ";
        cin >> aluno[totalDeAlunosCadastrados].codigo;
        listaDePresenca[totalDeAlunosCadastrados].codigoAluno = aluno[totalDeAlunosCadastrados].codigo;
        notas[totalDeAlunosCadastrados].codigoAluno = aluno[totalDeAlunosCadastrados].codigo;
        cin.ignore();

        if(aluno[totalDeAlunosCadastrados].codigo <= 0) {
            cout << endl << "Digite um codigo maior que 0 !" << endl;
        }

    } while ( aluno[totalDeAlunosCadastrados].codigo <= 0 );

    cout << "Digite o nome do aluno: ";
    getline(cin, aluno[totalDeAlunosCadastrados].nome);
    cout << "Digite o sobrenome do aluno: ";
    getline(cin, aluno[totalDeAlunosCadastrados].sobrenome);
    totalDeAlunosCadastrados++;
}

void gerenciarOpcaoB(ListaDePresenca listaDePresenca[]) {
    for( int c = 0; c < totalDeAlunosCadastrados; c++) {
        cout << endl << "Codigo do aluno: " << listaDePresenca[c].codigoAluno << endl;
        cout << "Digite a quantidade de ausencias: ";
        cin >> listaDePresenca[c].quantidadeDeAusencias;
        cout << "Digite a quantidade de aulas: ";
        cin >> listaDePresenca[c].quantidadeDeAulas;
        cin.ignore();
    }
}

void gerenciarOpcaoC(Notas notas[]) {
    for( int c = 0; c < totalDeAlunosCadastrados; c++) {
        cout << endl << "Codigo do aluno: " << notas[c].codigoAluno << endl;
        do {
            cout << "Digite a quantidade de notas para o aluno (entre 1 e 10): ";
            cin >> notas[c].quantidadeDeNotas;

            if(notas[c].quantidadeDeNotas <= 0 || notas[c].quantidadeDeNotas > 10) {
                cout << endl << "Digite uma nota maior entre 1 a 10 !" << endl;
            }

        } while(notas[c].quantidadeDeNotas < 1 || notas[c].quantidadeDeNotas > 10);

        const int totalDeNotas = notas[c].quantidadeDeNotas;

        for(int i = 0; i < totalDeNotas; i++){
            cout << "Digite a nota: ";
            cin >> notas[c].avaliacoes[i];
        }
    }
}

bool gerenciarOpcaoD(Notas notas[], ListaDePresenca listaDePresenca[]) {
    for( int c = 0; c < totalDeAlunosCadastrados; c++) {
        cout << endl << "Codigo do aluno: " << notas[c].codigoAluno << endl;
        cout << "Total de ausencias: " << listaDePresenca[c].quantidadeDeAusencias << endl;
        cout << "Total de aulas: " << listaDePresenca[c].quantidadeDeAulas << endl;
        const int totalDeNotas = notas[c].quantidadeDeNotas;
        for(int i = 0; i < totalDeNotas; i++){
            cout << "Nota: " << notas[c].avaliacoes[i] << endl;
        }
    }

    if (totalDeAlunosCadastrados > 0)
        return true;
    else
        return false;
}

bool imprimirArquivo(ofstream &saida, Notas *notas, ListaDePresenca * listaDePresenca){
    saida << "RELATÓRIO DE NOTAS E FALTAS DA TURMA";

    for( int c = 0; c < totalDeAlunosCadastrados; c++) {
        saida << endl << "CÓDIGO DO ALUNO: " << notas[c].codigoAluno << endl;
        saida << "TOTAL DE AUSÊNCIAS: " << listaDePresenca[c].quantidadeDeAusencias << endl;
        saida << "TOTAL DE AULAS: " << listaDePresenca[c].quantidadeDeAulas << endl;
        const int totalDeNotas = notas[c].quantidadeDeNotas;
        for(int i = 0; i < totalDeNotas; i++){
            saida << "NOTA: " << notas[c].avaliacoes[i] << endl;
        }
        saida.flush();
    }
	return true;
}
