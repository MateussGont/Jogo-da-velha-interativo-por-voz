// MV-Texto-em-Fala.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

auto autenticacao = SpeechConfig::FromSubscription("27edbf21b6b1455988079ca444011e56", "brazilsouth"); // DECLARAÇÃO DA AUTENTICAÇÃO DO RECURSO
auto requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE TEXTO EM FALA DO RECURSO
auto audio_config = AudioConfig::FromDefaultMicrophoneInput(); // DECLARAÇÃO DA ENTRADA DO MICROFONE
auto requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); // DECLARAÇÃO DO OBJETO DE REQUISIÇÃO DE FALA EM TEXTO DO RECURSO

// PROCEDIMENTO QUE REQUISITA DA API A TRANSFORMAÇÃO DE UM TEXTO EM FALA
void texto_em_fala(string Texto)
{
    cout << Texto + "\n";
    requisicao_textofala->SpeakTextAsync(Texto).get(); // REQUISIÇÃO DA SINTETIZAÇÃO DE TEXTO EM FALA
}
// FUNÇÃO QUE REQUISITA DA API O RECONHECIMENTO DE UMA FALA E A TRANSFORMAÇÃO DESSA FALA EM UM TEXTO
string fala_em_texto() {
    auto resultado = requisicao_falatexto->RecognizeOnceAsync().get(); // REQUISIÇÃO DO RECONHEIMENTO DE FALA EM TEXTO
    cout << resultado->Text + "\n";
    return resultado->Text; //CONVERSÃO DO RESULTADO DO RECONHECIMENTO EM TEXTO
}

class Jogo {
private:
    //Esquema grafico para representar o jogo;
    char tabuleiro[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };

public:
    char turno;// guarda X e O para alternar os turnos e marcar na tela;
    bool empate = false;//Variavel utilizada como condição de parada caso o empate seja identificado;

    void tela() {
        cout << "\n---------------------------------\n\n";
        cout << "\t " << tabuleiro[0][0] << " | " << tabuleiro[0][1] << " | " << tabuleiro[0][2] << "\n";
        cout << "\t " << tabuleiro[1][0] << " | " << tabuleiro[1][1] << " | " << tabuleiro[1][2] << "\n";
        cout << "\t " << tabuleiro[2][0] << " | " << tabuleiro[2][1] << " | " << tabuleiro[2][2] << "\n\n";

    }
    //Procedimento que tem como finalidade alternar a vez de cada Jogador
    // logo apos escolher uma posição
    void vez() {
        tela();
        int lin = -1, col = -1;
        //Verifica de quem é o turno pelo ultimo jogado
        if (turno == 'X') {
            texto_em_fala("Vez do jogador 1 ");
        }

        else if (turno == 'O') {
            texto_em_fala("Vez do Jogador 2 ");
        }

        int marcar = 0;
        string falamarcar = fala_em_texto();
        if (falamarcar == ("1.") || falamarcar == ("Um.")) {
            marcar = 1;
        }
        else if (falamarcar == ("2.")||falamarcar == ("Dois.")) {
            marcar = 2;
        }
        else if (falamarcar == ("3.") || falamarcar == ("Tres.")) {
            marcar = 3;
        }
        else if (falamarcar == ("4.") || falamarcar == ("Quatro.")) {
            marcar = 4;
        }
        else if (falamarcar == ("5.") || falamarcar == ("Cinco.")) {
            marcar = 5;
        }
        else if (falamarcar == ("6.")|| falamarcar == ("Seis.")) {
            marcar = 6;
        }
        else if (falamarcar == ("7.") || falamarcar == ("Sete.")) {
            marcar = 7;
        }
        else if (falamarcar == ("8.") || falamarcar == ("Oito.")) {
            marcar = 8;
        }
        else if (falamarcar == ("9.") || falamarcar == ("Nove.")) {
            marcar = 9;
        }
        else {
            marcar = 0;
        }

        switch (marcar) {
        case 1: lin = 0; col = 0; break;
        case 2: lin = 0; col = 1; break;
        case 3: lin = 0; col = 2; break;
        case 4: lin = 1; col = 0; break;
        case 5: lin = 1; col = 1; break;
        case 6: lin = 1; col = 2; break;
        case 7: lin = 2; col = 0; break;
        case 8: lin = 2; col = 1; break;
        case 9: lin = 2; col = 2; break;
        default:
            texto_em_fala("Posicao invalida! Tente Novamente!\n\n");
            vez();
            break;

        }

        if (col == -1 && lin == -1) {
            vez();
        }
        else if (turno == 'X' && tabuleiro[lin][col] != 'X' && tabuleiro[lin][col] != 'O' && col != -1 && lin != -1) {
            tabuleiro[lin][col] = 'X';
            turno = 'O';
        }

        else if (turno == 'O' && tabuleiro[lin][col] != 'X' && tabuleiro[lin][col] != 'O' && col != -1 && lin != -1) {
            tabuleiro[lin][col] = 'O';
            turno = 'X';
        }

        else {
            texto_em_fala("Espaço ocupado! Tente novamente!\n");
            vez();
        }
        
    }

    //Booleano com finalidade de verificar se ha um vencedor ou se o resultado final ]
    //é um empate
    bool verifica() {
        //Verifica condições de vitoria
        for (int i = 0; i < 3; i++) {
            if ((tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) || (tabuleiro[0][i] == tabuleiro[1][i]
                && tabuleiro[1][i] == tabuleiro[2][i]) || (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) ||
                (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])) {

                return true;
            }
        }
        //Verifica se exitem espaços livres
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O') {
                    return false;
                }
            }
        }
        //caso nenhuma retorne o jogo acaba e se tem um empate;
        empate = true;
        return true;
    }

};

int main()
{
    /*cout << "AZURE - SERVICO COGNITIVO DE FALA\n";
    string key = "", region = "";
    cout << "Informe a key do recurso: ";
    cin >> key;                 // ENTRADA DA CHAVE DO RECURSO
    cout << "Informe a regiao em que o recurso e hospedado: ";
    cin >> region;              // ENTRADA DA REGIÃO EM QUE O RECURSO FOI HOSPEDADO
    cout << "--------------------------------------------------------------\n";*/

    //autenticacao = SpeechConfig::FromSubscription(key, region);         //  AUTENTICAÇÃO DO RECURSO COM A CHAVE E REGIÃO INFORMADOS PELO USUÁRIO 
    setlocale(LC_ALL, "pt-BR");
    autenticacao->SetSpeechRecognitionLanguage("pt-BR");                //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA O RECONHECIMENTO DE FALA EM PORTUGUÊS 
    autenticacao->SetSpeechSynthesisLanguage("pt-BR");                  //  CONFIGURAÇÃO DA AUTENTICAÇÃO PARA A SINTETIZAÇÃO DE FALA EM PORTUGUÊS 
    autenticacao->SetSpeechSynthesisVoiceName("pt-BR-HeloisaRUS"); //pt-BR-Daniel  // CONFIGURAÇÃO DA AUTENTICAÇÃO COM UMA VOZ ESPECÍFICA 
    requisicao_textofala = SpeechSynthesizer::FromConfig(autenticacao); //  REDEFINIÇÃO DO OBJETO REQUISICAO_TEXTOFALA COM AS NOVAS CONFIGURAÇÕES 
    requisicao_falatexto = SpeechRecognizer::FromConfig(autenticacao, audio_config); //  REDEFINIÇÃO DO OBJETO REQUISICAO_FALATEXTO COM AS NOVAS CONFIGURAÇÕES


    try
    {
        Jogo jogo;
        texto_em_fala("\tJogo da Velha\n\n");
        texto_em_fala("Jogador 1 é o X --- Jogador 2 é o O [O]\n");
        jogo.turno = 'X';

        while (!jogo.verifica()) {
            //jogo.tela();
            jogo.vez();
            jogo.verifica();
        }

        if (jogo.turno == 'O' && !jogo.empate) {
            jogo.tela();
            texto_em_fala("Jogador 1 [X] venceu! \n\n");
            return 1;
        }
        else if (jogo.turno == 'X' && !jogo.empate) {
            jogo.tela();
            texto_em_fala("Jogador 2 [O] Venceu! \n\n");
            return 1;
        }
        else {
            jogo.tela();
            texto_em_fala("EMPATE!\n\n");
        }
        return 0;
    }
    catch (exception e)
    {
        cout << e.what();
    }
    return 0;
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln
