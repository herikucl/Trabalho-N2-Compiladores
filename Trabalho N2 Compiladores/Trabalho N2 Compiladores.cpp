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
    bool verificador;
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
    int estado=1;
    string token;
    
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
            else if (VerificarLetra(aux)){
                estado = 2;
                token = token + aux;
            }
            else if (VerificarNumero(aux))
            {
                estado = 3;
                token = token + aux;
            }
            break;
        case 2:
            if (VerificarLetra(aux) || VerificarNumero(aux)) {
                estado = 2;
                token = token + aux;
            }
            else if (aux == ' ') { //Finalização da cadeia
                if (VerificarPalavraReservada(token)) // Verificação se é uma palavra reservada
                {
                    ImprimirToken(token,"");
                }
                else {                                //Não é uma palavra reservada então é um identificador  
                    ImprimirToken("id", token);
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
            else if (aux== ' ') {
                ImprimirToken("numero", token);
                estado = 1;
                token = "";
            }
            else {
                cout << "(erro,);";
                estado = 1;
                token = "";
            }
            
            break;


        default:
            
            break;
        }
        //leitura.get(aux);
    }
    leitura.close();

}