#include <iostream>
#include <fstream>
#include <list>
#include <string>

using namespace std;

// Arquivos utilizados e suas funções
// fonteMaster.txt   - Arquivo de entrada dos dados (codigo fonte)
// fonte.txt - Arquivo de entrada após ser tratado pelo pré-compilador 
// saida.txt - Arquivo de saida com os tokens 
// tabelaSimbolos - Arquivo com toda a tabela de simbolos gerada
// teste.h   - Biblioteca exemplo
// teste2.h  - Biblioteca exemplo


bool VerificarLetra(char c) { 
    if (((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122))) {
        return true;
    }
    else {
        return false;
    }
}// vai verificar se o char é uma letra e retornar true caso seja
bool VerificarNumero(char c) {
    if ((c >= 48) && (c <= 57)) {
        return true;
    }
    else {
        return false;
    }
}// vai verificar se o char é um numero retornar true caso seja
void ImprimirToken(string tipo,string token) {
    ofstream escrita;
    escrita.open("saida.txt", ios::app);
    escrita << "[" << tipo << "," << token << "];";
    escrita.close();
}// depois que um token é formado ele escreve no arquivo de saida um de cada vez
bool VerificarPalavraReservada(string t) {
    const string palavrasreservadas[] = { "break","char","const","continue","default","do","double","else","float","for","if","int","long","return","void","while" };
    const string PALAVRASRESERVADAS[] = { "BREAK","CHAR","CONST","CONTINUE","DEFAULT","DO","DOUBLE","ELSE","FLOAT","FOR","IF","INT","LONG","RETURN","VOID","WHILE" };
    for (int i = 0; i < 16; i++)
    {
        if ((t == palavrasreservadas[i]) || (t == PALAVRASRESERVADAS[i]))
        {
            return true;
            break;
        }
    }
    return false;
}// vai verificar se a string é uma palavra reservada e retornar true caso seja
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
}// vai verificar se o char é um operador (dos selecionados) e retornar true caso seja
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
}// mesma coisa da função acima só que recebendo string
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
}// vai verificar se a string é um operador relacional dos selecionados e retornar true caso seja
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
}// vai verificar se o char é um dos selecionados que não entram nas outras categorias e retornar true caso seja
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
}// vai atribuir um numero para um identificar caso não esteja na lista e caso o identificador já esteja retorna o numero atribuido anteriormente
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
}// vai analisar a string para ir para o case correto
bool VerificarLogica(string t,string id[], int v[]) {
    string id1, id2,op,aux;
    id1 = id2 = op = aux = "";
    int n1, n2;
    n1 = n2 = 0;
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
}//verifica se o #if é true ou false e retorna isto 



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
    list <string> ::iterator it;
    bool erro, verificador;
    erro = verificador = true;
    list <int> LinhaInclude;
    list <int> LinhaIgnorar;
    list <string> Includes;
    list <string> TextoIncludes;
    list <string> ::iterator itString;
    list <int> ::iterator itInt;
    list <int> ::iterator itInt2;
    string id[2];
    int valor[2];
    int linhasIf[3] = { 0,0,0 }; //linhas do if else endif sucessivamente
    bool preIf=true;
    //Pre compilador
    leitura.open("fonteMaster.txt", ios::in);
    while (!leitura.eof())  // Vai identificar os includes e salvar na lista o nome e em qual linha ele se encontra
    {
        if (!erro) {

            for (itString = Includes.begin(); itString != Includes.end(); ++itString)
            {
                if (token == *itString) {
                    verificador = true; // biblioteca já está na lista
                    break;
                }
                else {
                    verificador = false; // biblioteca não está na lista
                }
            }// analisa se o token (nome da biblioteca) está na lista dos includes

            if (!verificador) {
                Includes.push_back(token);      // inclue o nome da biblioteca na lista
                LinhaInclude.push_back(linha);  // inclue em qual linha está o include
            }
            else {
                LinhaIgnorar.push_back(linha); //linha a linha que está o include repetido para ignorar depois
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
            }//achou um # agora vai para o switch que analisará qual comando é
            else if (aux == '\n') {
                linha++;  
            }// sempre que le o \n sabe-se que vai pular pra proxima linha
        }// while que busca comandos do precompilador (começam com #)
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

                case 1:
                    while (VerificarLetra(aux))
                    {
                        token = token + aux;
                        leitura.get(aux);
                        if (leitura.eof()) {
                            aux =' ';
                        }
                    }// vai lendo as letras após o # e concatena elas na variavel token
                    estado = VerificarComando(token); //verifica que palavra é e direciona para o case correto
                    if (VerificarComando(token)==5){
                        linhasIf[1] = linha;
                    }//seta a linha atual como a linha do else
                    else if (VerificarComando(token) == 6) {
                        linhasIf[2] = linha;
                    }//seta a linha atual como a linha do endif
                    if (aux == '\n') {
                        linha++;
                    }
                    token = "";
                    break;

                case 2: // case do include
                    if (aux != ' ') {
                        if ((aux == '<') || (aux == '"')) {
                            estado = 3; 
                        }
                        else {
                            estado = 0;
                        }
                    }
                    break;

                case 3:// concatenando o nome da biblioteca até receber o caracter que finaliza " ou >
                    if ((aux == '>') || (aux == '"')) {
                        verificador = false;
                    }
                    else {
                        token += aux;
                    }
                    break;

                case 4:// case do if
                    if ((aux != '\n')&&(aux!=' ')) {
                        token = token + aux; // concatena a expressão logica do if
                    }
                    else { // finalizou o if
                        linhasIf[0] = linha; // seta a linha atual como a linha do if
                        erro = true;
                        auth = false;
                        preIf = VerificarLogica(token, id, valor); // seta se o if é true ou false
                    }
                    break;

                case 5: //case do else
                    erro = true;
                    auth = false;
                    break;


                case 6: //case do endif
                    erro = true;
                    auth = false;
                    break;
                
                //ambos os cases acima são apenas para fugir do while

                case 7: //case do define (definição da variavel)
                    if (VerificarLetra(aux)) {
                        token = token + aux;
                    }
                    else if ((token!="")&&(VerificarNumero(aux))){ //apenas aceita numero apos ter pelo menos uma letra
                        token = token + aux;
                    }
                    else if (aux == ' '){ //finalizou o nome da varivel 
                        id[c] = token;
                        estado = 8; 
                        token = "";
                    }
                    break;

                case 8://case do define (numero atribuido)
                    if (VerificarNumero(aux)) {
                        token = token + aux;//concatena os numeros
                    }
                    else if((aux==' ')||(aux=='\n')) {
                        valor[c] = stoi(token); // transforma o valor dos numero em inteiro
                        c = c + 1;
                        estado = 1;
                        token = "";
                        auth = false;
                        erro = true;
                        LinhaIgnorar.push_back(linha); //salva o define na lista de linhas a ignorar
                    }
                    break;
                }
            }
        }
    }
    leitura.close();
    if (LinhaIgnorar.empty()) {
        LinhaIgnorar.push_back(0);
    }//corrigir problema de ponteiro flutuante
    itInt2 = LinhaIgnorar.begin();
    if (!Includes.empty()) {
        for (itString = Includes.begin(); itString != Includes.end(); ++itString)
        {
            textoBib = "";
            leitura.open(*itString, ios::in);
            leitura.get(aux);
            while (!leitura.eof()) {
                textoBib += aux;
                leitura.get(aux);
            }//pega todo o texto da biblioteca e salva na variavel textoBib
            TextoIncludes.push_back(textoBib);//talva o texto da variavel na lista
            leitura.close();
        }
        itInt = LinhaInclude.begin();
        itString = TextoIncludes.begin();
        leitura.open("fonteMaster.txt", ios::in);
        escrita.open("fonte.txt", ios::out);
        linha = 1;
        while (!leitura.eof()) {
            getline(leitura, token);
            if (linha == linhasIf[0]) { //linha do if
                if ((preIf) && (linhasIf[1] == 0))
                {
                    for (int i = 0; i < (linhasIf[2] - (linhasIf[0] + 1)); i++)
                    {
                        getline(leitura, token);
                        escrita << token << endl;
                    }
                }//if true e não tem else
                else if ((preIf) && (linhasIf[1] != 0)) {
                    for (int i = 0; i < (linhasIf[1] - (linhasIf[0] + 1)); i++)
                    {
                        getline(leitura, token);
                        escrita << token << endl;
                    }
                    for (int i = 0; i < (linhasIf[2] - linhasIf[1]); i++)
                    {
                        getline(leitura, token);
                    }

                }//if true e tem else
                else if ((!preIf) && (linhasIf[1] == 0)) {
                    for (int i = 0; i < (linhasIf[2] - (linhasIf[0]+1)); i++)
                    {
                        getline(leitura, token);
                    }
                }//if false e não tem else
                else if ((!preIf) && (linhasIf[1] != 0)) {
                    for (int i = 0; i < (linhasIf[1] - linhasIf[0]); i++)
                    {
                        getline(leitura, token);
                    }
                    for (int i = 0; i < (linhasIf[2] - (linhasIf[1]+1)); i++)
                    {
                        getline(leitura, token);
                        escrita << token << endl;
                    }
                }//if false e tem else
                getline(leitura, token);
                linha = linhasIf[2];
            }

            else if (linha == *itInt2) {       //Linha que tem que ignorar
                if (itInt2 != LinhaIgnorar.end()) {
                    ++itInt2;
                }
                if (itInt2 == LinhaIgnorar.end()) {
                    --itInt2;
                }
            }
            else if (linha==*itInt) { // linha da biblioteca que tem que colar
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
            else { //caso não seja linha de comando ele apenas reescreve
                escrita << token << endl;
            }
            linha++;
        }
    }
    else {
        leitura.open("fonteMaster.txt", ios::in);
        escrita.open("fonte.txt", ios::out);
        linha = 1;
        while (!leitura.eof())
        {
            getline(leitura, token);
            if (linha == linhasIf[0]) { //linha do if
                if ((preIf) && (linhasIf[1] == 0))
                {
                    for (int i = 0; i < (linhasIf[2] - (linhasIf[0] + 1)); i++)
                    {
                        getline(leitura, token);
                        escrita << token << endl;
                    }
                }//if true e não tem else
                else if ((preIf) && (linhasIf[1] != 0)) {
                    for (int i = 0; i < (linhasIf[1] - (linhasIf[0] + 1)); i++)
                    {
                        getline(leitura, token);
                        escrita << token << endl;
                    }
                    for (int i = 0; i < (linhasIf[2] - linhasIf[1]); i++)
                    {
                        getline(leitura, token);
                    }

                }//if true e tem else
                else if ((!preIf) && (linhasIf[1] == 0)) {
                    for (int i = 0; i < (linhasIf[2] - (linhasIf[0] + 1)); i++)
                    {
                        getline(leitura, token);
                    }
                }//if false e não tem else
                else if ((!preIf) && (linhasIf[1] != 0)) {
                    for (int i = 0; i < (linhasIf[1] - linhasIf[0]); i++)
                    {
                        getline(leitura, token);
                    }
                    for (int i = 0; i < (linhasIf[2] - (linhasIf[1] + 1)); i++)
                    {
                        getline(leitura, token);
                        escrita << token << endl;
                    }
                }//if false e tem else
                getline(leitura, token);
                linha = linhasIf[2];
            }
            else if (linha == *itInt2) {        //linha que tem que ignorar
                if (itInt2 != LinhaIgnorar.end()) {
                    ++itInt2;
                }
                if (itInt2 == LinhaIgnorar.end()) {
                    --itInt2;
                }
            }
            else {  //caso não seja linha de comando ele apenas reescreve
                escrita << token << endl;
            }
            linha++;
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
            if ((aux >= 0)&&(aux<=32)) { //simbolos de escape
                estado = 1;
            }
            else if (VerificarLetra(aux)) { // Estado que fará a verificação se é uma palavra reservada
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
            else {
                token += aux;
                ImprimirToken("erro", token);
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
            if ((token == "/")&&(aux=='/')) {   // É um comentário de linha "//"
                estado = 7;
                token = "";
            }
            else if ((token == "/") && (aux == '*')) {  // É um comentário de bloco "/*"
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

        escrita.open("tabelaSimbolos.txt", ios::out);
        c = 0;
        escrita <<" ID  |  NOME" <<endl;
        for (it = identificadores.begin(); it !=identificadores.end(); ++it) //imprimindo todos identificadores em uma tabela
        {
            //Formatação dos espaços para que a tabela fique alinhada
            if ((c >= 0) && (c <= 9)){                              
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
