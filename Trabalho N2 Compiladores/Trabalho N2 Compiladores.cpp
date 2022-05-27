#include <iostream>
#include <fstream>
using namespace std;
const string palavrasReservadas[] = { "break","char","const","continue","default","do","double","else","float","for","if","int","long","return","void","while" };

bool VerificarLetra(char c) {
    if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122))) {
        return true;
    }
    else {
        return false;
    }
}
bool VerificarNumero(char c) {
    if ((c >= 48) && (c <= 57)) {
        return true;
    }
    else {
        return false;
    }
}
void ImprimirToken(string tipo,string token) {
    cout << "(" << tipo << "," << token << ");";
}

bool VerificarPalavraReservada(string t) {
    for (int i = 0; i < 16; i++)
    {
        if (t==palavrasReservadas[i])
        {
            return true;
            break;
        }
    }
    return false;
}



int main() {
    ifstream leitura;
    ofstream escrita;
    char aux;
    int estado = 1;
    string token;
    int c = 0;
    int max = 1;

    token = "";
    //const string caminho = "C:\\Users\\HerikSarmento\\Desktop\\fonte.txt";
    leitura.open("fonte.txt", ios::in);
    while (!leitura.eof()) {
        leitura.get(aux);
        if (leitura.eof())
        {
            aux = ' ';
        }
        switch (estado)
        {
        case 1:
            if (aux == ' ') {
                estado = 1;
            }
            else if (VerificarLetra(aux)) {
                estado = 2;
                token = token + aux;
            }
            else if (VerificarNumero(aux)){
                estado = 3;
                token = token + aux;
            }
            else if (aux == '"') {
                estado = 4;
            }
            else if (aux == 39) { // Aspas simples
                estado = 5;
            }

            break;

        case 2:
            if (VerificarLetra(aux) || VerificarNumero(aux)) {
                estado = 2;
                token = token + aux;
            }
            else if (((aux >= 32) && (aux <= 33)) || ((aux >= 40) && (aux <= 47)) || ((aux >= 59) && (aux <= 62))) { // Após um identificador pode ter os seguintes simbolos ' ' '!' '(' ')' '*' '+' ',' '-' '.' '/' ';' '<' '=' '>' 
                if (VerificarPalavraReservada(token)){ // Verificação se é uma palavra reservada
                    ImprimirToken(token, "");
                }
                else {                                //Não é uma palavra reservada então é um identificador  
                    ImprimirToken("id", token);
                    if (aux != ' '){
                        token = aux;
                        ImprimirToken(token, "");
                        token = "";
                    }
                }
                token = "";
                estado = 1;
            }
            break;

        case 3:
            if (VerificarNumero(aux)) {
                estado = 3;
                token = token + aux;
            }
            else if ((aux == ' ') || ((aux >= 41) && (aux <= 47)) || ((aux >= 58) && (aux <= 62))) {  // Após um numero pode ter os seguintes simbolos: ' ' ')' '*' '+' ',' '-' '.' '/' ':' ';' '<' '=' '>' 
                ImprimirToken("numero", token);
                estado = 1;
                token = "";
                if (aux != ' ')
                {
                    token = aux;
                    ImprimirToken(token, "");
                    token = "";
                }
            }
            else {                                  //Letra após o numero é um erro
                cout << "(erro,);";
                estado = 1;
                token = "";
            }

            break;

        case 4:
            if (aux != '"') {
                token = token + aux;
            }
            else {
                ImprimirToken("literal", token);
                estado = 1;
                token = "";
            }
            break;

        case 5:
            if (aux != 39) {
                token = token + aux;
                c++;
                if (aux == 92) {  // Caso seja contra barra '\' pode ter dois caracteres, caso não apenas um 
                    max = 2;
                }
            }
            else {
                if (c == max) {
                    ImprimirToken("char", token);
                    max = 1;
                }
                else {
                    ImprimirToken("erro", "");
                    
                }
                token = "";
                estado = 1;
                c = 0;
            }
                break;

            }
            //leitura.get(aux);
        }
        leitura.close();

    }
