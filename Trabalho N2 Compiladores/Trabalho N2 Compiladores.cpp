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
    const string palavrasreservadas[] = { "break","char","const","continue","default","do","double","else","float","for","if","int","long","return","void","while" };
    const string PALAVRASRESERVADAS[] = { "BREAK","CHAR","CONST","CONTINUE","DEFAULT","DO","DOUBLE","ELSE","FLOAT","FOR","IF","INT","LONG","RETURN","VOID","WHILE" };
    for (int i = 0; i < 16; i++)
    {
        if ((t==palavrasreservadas[i])||(t==PALAVRASRESERVADAS[i]))
        {
            return true;
            break;
        }
    }
    return false;
}
bool VerificarOperador(char c) {
    const char op[] = { '+','-','*', '/','=','&','!','|','>','<','%'};
    for (int i = 0; i < 11; i++)
    {
        if (c == op[i])
        {
            return true;
            break;
        }
    }
    return false;
}
bool VerificarOperador(string c) {
    const string op[] = { "+" ," - ","*", "/","=","&","!","|",">","<","%"};
    for (int i = 0; i < 11; i++)
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
    const string rel[] = { "==","+=","-=","!=","/=",">=","<=","++","--","||","&&"};
    for (int i = 0; i < 11; i++)
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
    const char id[] = {'(',')','{','}',';',',','[',']'};
    for (int i = 0; i < 8; i++)
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
int VerificarComando(string t) {
    if (t == "include") {
        return 2;
    }else if (t == "if") {
        return 4;
    }
    else if (t == "else") {
        return 5;
    }
    else if (t == "endif") {
        return 6;
    }
    else if (t == "define") {
        return 7;
    }
}
bool VerificarLogica(string t,string id[], int v[]) {
    string id1, id2,op,aux;
    id1 = id2 = op = aux = "";
    int n1, n2;
    bool primeiroid=false;
    int estado = 1;
    for (int i = 0; i < t.length(); i++)
    {
        switch (estado)
        {   
        case 1:
            if (VerificarLetra(t[i])) {
                estado = 2;
            }
            else if(VerificarNumero(t[i])) {
                estado = 3;
            }
            else { //Operador
                estado = 4;
            }
            aux += t[i];
            break;
        
        case 2:
            if ((VerificarNumero(t[i]))||(VerificarLetra(t[i]))) {
                aux += t[i];
            }
            else {
                if (id1 != "") {
                    id2 = aux;
                }
                else {
                    id1 = aux;
                }
                aux = "";
                i--;
                estado = 1;
            }
            break;

        case 3:
            if (VerificarNumero(t[i])) {
                aux += t[i];
            }
            else {
                if (id1 != "") {
                    id2 = aux;
                }
                else {
                    id1 = aux;
                }
                aux = "";
                i--;
                estado = 1;
            }
            break;

        case 4:
            if (VerificarOperador(t[i])) {
                aux += t[i];
            }
            else {
                op = aux;
                i--;
                estado = 1;
                aux = "";
            }
            break;
        }
        if (i == (t.length()-1)) { //no ultimo for ele finaliza o valor que está sendo lido
            if (estado != 3) {
                if (id1 != "") {
                    id2 = aux;
                }
                else {
                    id1 = aux;
                }
            }
            else {
                if (id1 != "") {
                    n2 = stoi(aux);
                    id2 = "numero";
                }
                else {
                    n1 = stoi(aux);
                    id1 = "numero";
                }
            }
        }
    }

    if (id1 == id[0]) {
        n1 = v[0];
    }else if (id1 == id[1]) {
        n1 = v[1];
    }
    else {
        //erro
    }

    if (id2 == id[0]) {
        n2 = v[0];
    }
    else if (id2 == id[1]) {
        n2 = v[1];
    }
    else {
        //erro
    }

    if (op == ">") {
        if (n1 > n2) {
            return true;
        }
    }
    else if (op == "<") {
        if (n1 < n2) {
            return true;
        }
    }
    else if (op == ">=") {
        if (n1 >= n2) {
            return true;
        }
    }
    else if (op == "<=") {
        if (n1 <= n2) {
            return true;
        }
    }
    else if (op == "!=") {
        if (n1 != n2) {
            return true;
        }
    }
    else if (op == "==") {
        if (n1 == n2) {
            return true;
        }
    }
    return false;
}


int main() {
    ifstream leitura;
    fstream escrita;
    char aux = ' ';
    int estado = 1;
    int linha = 1;
    int c = 0;
    string token;
    string textoBib;
    token = "";
    bool auth = false;
    list <string> identificadores;
    bool erro, verificador;
    erro = verificador = true;
    list <int> LinhaInclude;
    list <int> LinhaIncludeRepetidos;
    //LinhaIncludeRepetidos.push_back(0);
    list <string> Includes;
    list <string> TextoIncludes;
    list <string> ::iterator itString;
    list <int> ::iterator itInt;
    list <int> ::iterator itInt2;
    string id[2];
    int valor[2];
    bool preIf;
    //Pre compilador
    leitura.open("fonteMaster.txt", ios::in);
    while (!leitura.eof())  // Vai identificar os includes e salvar na lista o nome e em qual linha ele se encontra
    {
        if (!erro) {

            for (itString = Includes.begin(); itString != Includes.end(); ++itString)
            {
                if (token == *itString) {
                    verificador = true;
                    break;
                }
                else {
                    verificador = false;
                }
            }
            if (!verificador) {
                Includes.push_back(token);
                LinhaInclude.push_back(linha);
            }
            else {
                LinhaIncludeRepetidos.push_back(linha);
            }

        }
        token = "";
        verificador = true;
        erro = false;
        while (!leitura.eof()) {
            if (auth == true) {
            leitura.get(aux);
            }
            auth = true;

            if (aux == '#') {
                estado = 1;
                break;
            }
            else if (aux == '\n') {
                linha++;
            }
        }
        if (!leitura.eof()) {
            while (verificador) {
                if (auth == false) {
                    break;
                }
                if (!erro) {
                    leitura.get(aux);
                }
                if (leitura.eof()) {
                    aux = ' ';
                    verificador = false;
                }
                if (aux == '#') {
                    auth = false;
                    break;
                }
                switch (estado) {
                case 0:
                    cout << "erro";
                    verificador = false;
                    break;

                case 1:
                    while (VerificarLetra(aux))
                    {
                        token = token + aux;
                        leitura.get(aux);
                        if (leitura.eof()) {
                            aux =' ';
                        }
                    }
                    estado = VerificarComando(token);  
                    token = "";
                    break;

                case 2:
                    if (aux != ' ') {
                        if ((aux == '<') || (aux == '"')) {
                            estado = 3;
                        }
                        else {
                            estado = 0;
                        }
                    }
                    break;

                case 3:
                    if ((aux == '>') || (aux == '"')) {
                        verificador = false;
                    }
                    else {
                        token += aux;
                    }
                    break;

                case 4:
                    if ((aux != '\n')&&(aux!=' ')) {
                        token = token + aux;
                    }
                    else {
                        auth = false;
                        if (VerificarLogica(token, id, valor)) {
                            preIf = true;
                        }
                        else {
                            preIf = false;
                        }
                    }
                    break;

                case 7:
                    if (VerificarLetra(aux)) {
                        token = token + aux;
                    }
                    else if ((token!="")&&(VerificarNumero(aux))){
                        token = token + aux;
                    }
                    else if (aux == ' '){
                        id[c] = token;
                        estado = 8;
                        token = "";
                    }
                    break;

                case 8:
                    if (VerificarNumero(aux)) {
                        token = token + aux;
                    }
                    else if((aux==' ')||(aux=='\n')) {
                        valor[c] = stoi(token);
                        c = c + 1;
                        estado = 1;
                        token = "";
                        auth = false;
                    }
                    break;
                }
            }
        }
    }
    leitura.close();
    if (!Includes.empty()) {
        for (itString = Includes.begin(); itString != Includes.end(); ++itString)
        {
            textoBib = "";
            leitura.open(*itString, ios::in);
            leitura.get(aux);
            while (!leitura.eof()) {
                textoBib += aux;
                leitura.get(aux);
            }
            TextoIncludes.push_back(textoBib);
            leitura.close();
        }
        itInt = LinhaInclude.begin();
        if (LinhaIncludeRepetidos.empty()) {
            LinhaIncludeRepetidos.push_back(0);
        }
        itInt2 = LinhaIncludeRepetidos.begin();
        itString = TextoIncludes.begin();
        leitura.open("fonteMaster.txt", ios::in);
        escrita.open("fonte.txt", ios::out);
        linha = 1;
        while (!leitura.eof()) {
            getline(leitura, token);
            if ((linha != *itInt)&&(linha!=*itInt2)) {   
                escrita << token << endl;
            }
            else if (linha==*itInt2) {        //Apenas para apagar a linha do include da biblioteca já registrada
                if (itInt2 != LinhaIncludeRepetidos.end()) {
                    ++itInt2;
                }
                if (itInt2 == LinhaIncludeRepetidos.end()) {
                    --itInt2;
                }
            }
            else {
                escrita << *itString << endl;
                if (itString != TextoIncludes.end()) {
                    ++itInt;
                    ++itString;
                }
                if (itString == TextoIncludes.end()) {
                    --itInt;
                    --itString;
                }

            }
            linha++;
        }
    }
    else {
        leitura.open("fonteMaster.txt", ios::in);
        escrita.open("fonte.txt", ios::out);
        getline(leitura, token);
        escrita << token << endl;
        while (!leitura.eof())
        {
            getline(leitura, token);
            escrita << token << endl;
        }
    }
    leitura.close();
    escrita.close();
    aux = ' ';
    token = "";

    //Final do pre compilador
    
    escrita.open("saida.txt", ios::out);    //limpando o arquivo de saida antes de começar a mandar os tokens
    escrita.close();
    estado = 1;
    leitura.open("fonte.txt", ios::in);
    while (!leitura.eof()) {
       
        if (auth) {         // Ao finalizar um token um caractere pode ficar sem ser analisado para que isso não ocorra só lerá o proximo caractere no proximo loop
            leitura.get(aux);
        }
        auth = true;
        if (leitura.eof())  //  É necessário pois quando encontrar o final do arquivo a variavel aux que está recebendo não atualizará fazendo com que o ultimo caractere se repita
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
            else if (VerificarOutrosCaracteres(aux))     // Resto dos caracteres ( ) , ; {  } [ ]
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
                    token = "";
                    estado = 1;
                }
                else {                                 // Não é uma palavra reservada então é um identificador 
                    estado = 9;
                }
                auth = false;
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
            if ((token == "/")&&(aux=='/')) {   // É um comentário com "//"
                estado = 7;
                token = "";
            }
            else if ((token == "/") && (aux == '*')) {  // É um comentário com "/*"
                estado = 8;
                token = "";
            }
            else {
                if (VerificarOperador(aux)) {
                    token = token + aux;
                }
                else {
                    if ((VerificarOperadorRelacional(token)||VerificarOperador(token))){
                        ImprimirToken(token, "");
                        estado = 1;
                        token = "";
                    }
                    else {
                        estado = 9;
                    }
                    auth = false;
                }
            }
            break;

        case 7:  // Comentário com "//"
            if (aux == '\n') {
                estado = 1;
                }
            break;

        case  8: // Comentário com "/*"
            if (aux == '*') {
                token = "";
                token = token + aux;
            }
            if ((token == "*") && (aux == '/')) {
                estado = 1;
                token = "";
            }
            break;
        
        case 9:  // Tudo que não conseguiu ser identificado nos outros cases será impresso como um identificador
            ImprimirToken("id", to_string(numeroLista(token, identificadores)));
            token = "";
            estado = 1;
            auth = false;
            break;
            }
        }
        leitura.close();

        list <string> ::iterator it;
        escrita.open("tabelaSimbolos.txt", ios::out);
        c = 0;
        escrita <<" ID  |  NOME" <<endl;
        for (it = identificadores.begin(); it !=identificadores.end(); ++it)
        {
            if ((c >= 0) && (c <= 9)){                              //Formatação dos espaços para que a tabela fique alinhada
                escrita << " " << c << "   |  " << *it << endl;
            }else if ((c >= 10) && (c <= 99)) {
                escrita << " " << c << "  |  " << *it << endl;
            }else {
                escrita << " " << c << " |  " << *it << endl;
            }
            c++;
        }
        escrita.close();  
    }
