/*

   AUTOR: MAYRON REIS LACERDA RIBEIRO
   ESTUDANTE ENGENHARIA DE COMPUTAÇÃO IFMG - CAMPUS BAMBUÍ

   TRABALHO DE CONCLUSÃO DE CURSO - PARTE 4 DE XX
   ==================================================================================================
   LEITOR CARTÃO - CIRCUITO
   CS 4
   MOSI 51
   MISO 50
   SCK 52
   ==================================================================================================
   OS DADOS QUE ESTÃO SENDO SALVOS SÃO: TEMPO (HHMMSS), LATITUDE, NORTEOUSUL, LESTEOUOESTE
   QUALIDADE DO SINAL, ALTITUDE, METROS
   ==================================================================================================
*/

//============================================BIBLIOTECAS============================================
#include <SPI.h>          // Biblioteca de comunicação SPI Nativa
#include <SD.h>           // Biblioteca de comunicação com cartão SD Nativa
//============================================VARIÁVEIS==============================================

char caracter;
String palavra, gravacao = "", vetGPS[15];
const int chipSelect = 4, ledGravacao;
int i = 0;
float tempo;
long controle_tempo = 0;
long intervalo_gravacao = 1000;
bool cartaoOk = true;

File dataFile;// Objeto responsável por escrever/Ler do cartão SD

//===============================================//==================================================
void setup() {
  pinMode(ledGravacao, OUTPUT);
  Serial.begin(9600);

  if (!SD.begin(chipSelect)) {
    //Serial.println("Erro na leitura do arquivo não existe um cartão SD ou o módulo está conectado corretamente ?");
    cartaoOk = false;
    return;
  }
}

void loop() {
  if (cartaoOK == false){
    digitalWrite(ledGravacao, HIGH);
  }else{
    digitalWrite(ledGravacao, LOW);
  }
  while (Serial.available() > 0) {
    caracter = (byte)Serial.read();
    //Serial.println(caracter);

    if (caracter != '*') {
      if (caracter != ',') {
        palavra += caracter;
      } else {
        vetGPS[i] = palavra;
        palavra = "";
        i++;
      }
    } else {
      i = 0;
      palavra = "";
    }
  }
  tempo = millis();//INICIA O MILLIS
  gravacao = String(vetGPS[1]) + ";" + String(vetGPS[2]) + ";" + String(vetGPS[3]) + ";" + String(vetGPS[4]) + ";" + String(vetGPS[5]) + ";" + String(vetGPS[6]) + ";" + String(vetGPS[9]) + ";" + String(vetGPS[10]);
  Gravacao();
}

//===============================================FUNCOES===============================================
void Gravacao() {
  if (tempo - controle_tempo > intervalo_gravacao) {
    controle_tempo = tempo;    // Salva o tempo atual

    if (cartaoOk) {
      dataFile = SD.open("teste2.csv", FILE_WRITE);
    }

    if (dataFile) {
      Serial.println(gravacao);
      dataFile.println(gravacao);
      dataFile.close();
    }
  }
}
