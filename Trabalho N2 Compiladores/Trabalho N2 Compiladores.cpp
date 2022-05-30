#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

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
    ofstream escrita;
    escrita.open("saida.txt", ios::app);
    escrita << "[" << tipo << "," << token << "];";
    escrita.close();
}
bool VerificarPalavraReservada(string t) {
    const string palavrasReservadas[] = { "break","char","const","continue","default","do","double","else","float","for","if","int","long","return","void","while" };
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
bool VerificarOperador(char c) {
    const char op[] = { '+','-','*', '/','=','&','!','|','>','<'};
    for (int i = 0; i < 10; i++)
    {
        if (c == op[i])
        {
            return true;
            break;
        }
    }
    return false;
}
bool VerificarOperadorRelacional(string r) {
    const string rel[] = { "==","+=","-=","!=",">=","<=","++","--","||","&&"};
    for (int i = 0; i < 10; i++)
    {
        if (r == rel[i])
        {
            return true;
            break;
        }
    }
    return false;
}
bool VerificarOutrosCaracteres(char c) {
    const char id[] = {'(',')','{','}',';',','};
    for (int i = 0; i < 6; i++)
    {
        if (c == id[i])
        {
            return true;
            break;
        }
    }
    return false;
}
int numeroLista(string ab, list <string> &aa) {
    int c = 0;
    bool possui=false;
    list <string> ::iterator it;
    for (it = aa.begin(); it != aa.end(); ++it) {

        if (*it == ab) {
            possui = true;
            break;
        }
        else {
            possui = false;
        }
        c++;
    }
    if (possui != true) {
        aa.push_back(ab);
    }
    return c;
}



int main() {
    ifstream leitura;
    char aux=' ';
    int estado = 1;
    string token;
    token = "";
    bool auth=false;
    list <string> identificadores;
    ofstream auxEscrita;           
    auxEscrita.open("saida.txt", ios::out);    //limpando o arquivo de saida antes de começar a mandar os tokens
    auxEscrita.close();

    leitura.open("fonte.txt", ios::in);
    while (!leitura.eof()) {
        
        if ((aux >= 0) && (aux <= 31)) { // Caso o caractere lido seja algum espaço ou quebra de linha
            estado = 1;
            token = "";
            auth = true;
        }
        if (auth) {         // Ao finalizar um token um caractere pode ficar sem ser analisado para que isso não ocorra só lerá o proximo caractere no proximo loop
            leitura.get(aux);
        }
        auth = true;
        if (leitura.eof())  //  É necessário pois quando encontrar o final do arquivo a variavel aux que está recebendo não atualizará
        {
            aux = ' ';
        }   
        switch (estado)
        {
        case 1:
            if (aux == ' ') {
                estado = 1;
            }
            else if (VerificarLetra(aux)) { // Estado que fará a verificação se é um identificador ou palavra reservada
                estado = 2;
                token = token + aux;
            }
            else if (VerificarNumero(aux)){ // Estado que fará a verificação se é um numero
                estado = 3;
                token = token + aux;
            }
            else if (aux == '"') {          // string " " 
                estado = 4;
            }   
            else if (aux == 39) {           // char ' '
                estado = 5;
            }
            else if (VerificarOperador(aux)) {      // Operadores 
                estado = 6;
                token = token + aux;
            }
            else if (VerificarOutrosCaracteres(aux))     // Resto dos caracteres ( ) , ; {  }
            {
                token = token + aux;
                ImprimirToken(token, "");
                token = "";
            }

            break;

        case 2:
            if (VerificarLetra(aux) || VerificarNumero(aux)){
                estado = 2;
                token = token + aux;
            }
            else{ 
                if (VerificarPalavraReservada(token)){ // Verificação se é uma palavra reservada
                    ImprimirToken(token, "");          // Imprime a palavra reservada
                }
                else {                                 // Não é uma palavra reservada então é um identificador 
 
                    ImprimirToken("id", to_string(numeroLista(token, identificadores)));
                }
                token = "";
                estado = 1;
                if (aux != ' ') {
                    auth = false;
                }
            }
            break;

        case 3:
            if (VerificarNumero(aux)) {
                estado = 3;
                token = token + aux;
            }
            else {  
                ImprimirToken("numero", token);
                estado = 1;
                token = "";
                if (aux != ' ') {
                    auth = false;
                }
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
            }
            else {
                ImprimirToken("char", token);
                token = "";
                estado = 1;
                if (aux != ' ') {
                    auth = false;
                }
            }
                break;
        case  6:
            if ((token == "/")&&(aux=='/')) {
                estado = 7;
                token = "";
            }
            else if ((token == "/") && (aux == '*')) {
                estado = 8;
                token = "";
            }
            else {
                if (VerificarOperador(aux)) {
                    if (VerificarOperadorRelacional(token + aux)) {
                        token = token + aux;
                        ImprimirToken(token, "");
                    }
                    else {
                        ImprimirToken(token, "");
                        token = "";
                        token = token + aux;
                        ImprimirToken(token, "");
                    }
                }
                else {
                    ImprimirToken(token, "");
                    if (aux != ' ') {
                        auth = false;
                    }
                }
                token = "";
                estado = 1;
            }
            break;

        case 7:
            if (aux == '\n') {
                estado = 1;
                }
            break;

        case  8:
            if (aux == '*') {
                token = "";
                token = token + aux;
            }
            if ((token == "*") && (aux == '/')) {
                estado = 1;
                token = "";
            }
            break;

            }
        }
        leitura.close();

        list <string> ::iterator it;
        auxEscrita.open("tabelaSimbolos.txt", ios::out);
        int c = 0;
        auxEscrita <<" ID  | NOME" <<endl;
        for (it = identificadores.begin(); it !=identificadores.end(); ++it)
        {
                
            auxEscrita<<" "<<c<<" | "<<*it<<endl;
            c++;
        }
        auxEscrita.close();
        
    }
