#pragma once

#include <cstdlib>
#include <cstdint>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <ctime>
#include <iomanip>

using namespace std;

typedef string String;
typedef FILE File;

String webpage = " ";

String Version = " ";
String  Temperature = " ";
String Name = " ";


typedef struct {

    uint8_t ano;
    uint8_t mes;
    uint8_t dia;

    uint8_t hora;
    uint8_t minuto;
    uint8_t segundo;

}TIME_VAL;

typedef struct {
    char id;
    char estado; // 1-trabalhando 0-em casa
    const char* nome;
    char* n_arquivo;
    unsigned long entrada;
    //lv_obj_t* btn;
    uint16_t algo;
    File arquivo;

}PESSOA_TYP;


typedef struct
{
    uint8_t data[3];
    uint8_t operacao; // 1-entrada  2-saida.
    uint32_t timeStamp;
}BATIDA_TYP;

typedef union
{
    uint8_t bytes[1612];
    struct
    {
        uint32_t checksum;
        uint8_t versao;
        uint16_t qtd_bat;
        uint8_t data;
        BATIDA_TYP bat[200];
    };
}ARQUIVO_TYP;

ARQUIVO_TYP arquivo;

PESSOA_TYP funcionario[10];

void horario_batidas_dia(ARQUIVO_TYP batidas, unsigned int dia_do_mess, unsigned int numero_da_batida, unsigned int& h, unsigned int& m, unsigned int& s);
unsigned int batidas_dia(ARQUIVO_TYP batidas, uint8_t dia_do_mes);

String HTML_Header() {
    String page;
    page = "<!DOCTYPE html>";
    page += "<html lang = 'en'>";
    page += "<head>";
    page += "<title>Web Server</title>";
    page += "<meta charset='UTF-8'>"; // Needed if you want to display special characters like the ° symbol
    page += "<style>";
    page += "body {width:75em;margin-left:auto;margin-right:auto;font-family:Arial,Helvetica,sans-serif;font-size:16px;color:blue;background-color:#A9C2CD;text-align:center;}"; //text-align:center;
    page += "footer {padding:0.08em;background-color:cyan;font-size:1.1em;}";
    page += "table {font-family:arial,sans-serif;border-collapse:collapse;width:70%;}"; // 70% of 75em!
    page += "table.center {margin-left:auto;margin-right:auto;}";
    page += "td, th {border:1px solid #dddddd;text-align:left;padding:8px;}";
    page += "tr:nth-child(even) {background-color:#dddddd;}";
    page += "h4 {color:slateblue;font:0.8em;text-align:left;font-style:oblique;text-align:center;}";
    page += ".center {margin-left:auto;margin-right:auto;}";
    page += ".topnav {overflow: hidden;background-color:grey;}";
    page += ".topnav a {float:left;color:blue;text-align:center;padding:0.6em 0.6em;text-decoration:none;font-size:1.3em;}";
    page += ".topnav a:hover {background-color:deepskyblue;color:white;}";
    page += ".topnav a.active {background-color:lightblue;color:blue;}";
    page += ".notfound {padding:0.8em;text-align:center;font-size:1.5em;}";
    page += ".left {text-align:left;}";
    page += ".medium {font-size:1.4em;padding:0;margin:0}";
    page += ".ps {font-size:0.7em;padding:0;margin:0}";
    page += ".sp {background-color:silver;white-space:nowrap;width:2%;}";
    page += "</style>";
    page += "</head>";
    page += "<body>";
    page += "<div class = 'topnav'>";
    page += "<a href='/'>Home</a>";
    page += "<a href='/dir'>Directory</a>";
    page += "<a href='/upload'>Upload</a> ";
    page += "<a href='/download'>Download</a>";
    page += "<a href='/stream'>Stream</a>";
    page += "<a href='/delete'>Delete</a>";
    page += "<a href='/rename'>Rename</a>";
    page += "<a href='/system'>Status</a>";
    //page += "<a href='/format'>Format FS</a>";
    page += "<a href='/newpage'>New Page</a>";
    page += "<a href='/logout'>[Log-out]</a>";
    page += "</div>";
    return page;
}

String HTML_Footer() {
    String page;
    page += "<br><br><footer>";
    page += "<p class='medium'>ESP Asynchronous WebServer Example</p>";
    page += "<p class='ps'><i>Copyright &copy;&nbsp;D L Bird 2021 Version " + Version + "</i></p>";
    page += "</footer>";
    page += "</body>";
    page += "</html>";
    return page;
}


int val1 = 1;
String valor1 = "1";
String valor2 = "2";
String valor3 = "3";
String valor4 = "4";

void tdia()
{
    unsigned int dia;
    for (dia = 0; dia <= 30; dia++)
    {
        continue;
    }
}

void Display_New_Page() {
    webpage = HTML_Header();  // Add HTML headers, note '=' for new page assignment
    webpage += "<h1>Dados ponto MAGVIA</h1> \n";

    webpage += "<style>";
    webpage += "table{margin-left:auto;margin-right:auto;}";
    webpage += "tr{height: 10px;width: 1000px;}";
    webpage += "td{height: 10px;width: 1000px;border:1px solid black;text-align: center;}";
    webpage += "th{height: 10px;width: 1000px;border:1px solid black;}";
    webpage += "</style>";

    webpage += "<table>";
    webpage += "<tr>";
    webpage += "<th>DIA</th>";
    webpage += "<th>ENTRADA 1</th>";
    webpage += "<th>SAIDA 1</th>";
    webpage += "<th>ENTRADA 2</th>";
    webpage += "<th>SAIDA 2</th>";
    webpage += "<th>ENTRADA 3</th>";
    webpage += "<th>SAIDA 3</th>";
    webpage += "</tr>";

    uint8_t k = 0;
    uint8_t j = 0;
    unsigned int hor =0, min =0, seg = 0;
    String valor[8];
   
     for (j = 1; j < 30; j++)
     {
         webpage += "<tr>";
         String dia = to_string(j);

         webpage += "<td>" + dia + "</td>"; 

          unsigned int qtd_bat_dia = batidas_dia(arquivo, j );  

          //std::cout << "qtd_bat_dia: " << qtd_bat_dia << std::endl;

         for (k = 0; k < qtd_bat_dia; k++)
         {
            // std::cout << "timestamp !!: " << arquivo.bat[k].timeStamp << std::endl;
            horario_batidas_dia(arquivo, j , k+1, hor, min, seg);

           // std::cout << " Hora: " << k << std::endl;

           webpage += "<td>" + to_string(hor) + ":" + to_string(min) + ":" + to_string(seg) + "</td>"; //entrada1

             
         }
         webpage += "</tr>";
     }
     
     webpage += "</table>";
     
     
}

    void convert_unix_to_data(uint32_t temp_atual, unsigned int& dia, unsigned int& mes, unsigned int& ano, unsigned int& hora, unsigned int& minuto, unsigned int& segundo){

        const unsigned int SEGUNDOS_POR_MINUTO = 60;
        const unsigned int SEGUNDOS_POR_HORA = 60 * SEGUNDOS_POR_MINUTO;
        const unsigned int SEGUNDOS_POR_DIA = 24 * SEGUNDOS_POR_HORA;
        const unsigned int ANO_INICIAL = 1970;


        // Ajuste do fuso horário para o Brasil (horário de verão não considerado)
        const int FUSO_HORARIO_BRASIL = 3; // Horário de Brasília (UTC-3)

        // Adiciona o ajuste do fuso horário ao timestamp
        temp_atual = ((temp_atual) - (FUSO_HORARIO_BRASIL * SEGUNDOS_POR_HORA));
        // Calcula o número de dias

        unsigned int dias = temp_atual / SEGUNDOS_POR_DIA;

        // Calcular o número de anos bissextos passados desde o ano inicial

        unsigned int anos_bissextos = (dias - 1) / 365 - (dias - 1) / 100 + (dias - 1) / 400;

        // Ajusta o número de dias para considerar os anos bissextos

        dias -= anos_bissextos;

        // Calcular o ano
        ano = ANO_INICIAL;
        while (true) {
        unsigned   int dias_no_ano = 365 + (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0));
            if (dias <= dias_no_ano) {
                break;
            }
            dias -= dias_no_ano;
            ano++;
        }

        // Calcular o mês e o dia, levando em conta quantidade de dias por mês 

        unsigned int dias_por_mes[] = { 31, 28 + (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        mes = 1;
        while (dias > dias_por_mes[mes - 1]) {
            dias -= dias_por_mes[mes - 1];
            mes++;
        }
        mes = mes - 3;      //Solução não otimizada  

        dia = dias-1;     //Solução não otimizada  

        // Calcular a hora, o minuto e o segundo
        unsigned int segundos_no_dia = temp_atual % SEGUNDOS_POR_DIA;
        hora = ((segundos_no_dia / SEGUNDOS_POR_HORA) ); 
        minuto = (segundos_no_dia % SEGUNDOS_POR_HORA) / SEGUNDOS_POR_MINUTO;
        segundo = segundos_no_dia % SEGUNDOS_POR_MINUTO;

    };

    unsigned int batidas_dia(ARQUIVO_TYP batidas,uint8_t dia_do_mes){                        //Retorna quantas batidas a pessao teve no dia

        unsigned int qtd_batida = 0;

        unsigned int dia =0, mes =0, ano =0, hora =0, minuto =0, segundo =0;

        for (int i = 0; i < batidas.qtd_bat; i++) {                                 // percorre os timestamp quantidade de vezes que foram batidas n total
       
            convert_unix_to_data(batidas.bat[i].timeStamp, dia, mes, ano, hora, minuto, segundo);   

           // std::cout << "Data Dentro da Função batidas_dia: " << dia <<  std::endl;
           // std::cout << "TimeStamp Dentro da Função batidas_dia: " << batidas.bat[i].timeStamp << std::endl;

            if (dia == dia_do_mes) {

                qtd_batida++;                                                          // se o timestamp do vetor bat[qtd_bat] estiver dentro do intervalo do timestamp correspondente ao dia X adiciona 1 na qtd_batida
            }  
        }
        return qtd_batida;

    }

    void horario_batidas_dia(ARQUIVO_TYP batidas, unsigned int dia_do_mess, unsigned int numero_da_batida, unsigned int& h, unsigned int& m, unsigned int& s) {             //Retorna a hora exata da batida em questão

        unsigned int aux = numero_da_batida;      
                                                        
        unsigned int dia = 0, mes = 0, ano = 0, hora = 0, minuto = 0, segundo = 0;
        
        for (int i = 0; i <= 185; i++) {

           convert_unix_to_data(batidas.bat[i].timeStamp, dia, mes, ano, hora, minuto, segundo);
                                                                                                                                       
           if (dia == dia_do_mess) {
               int aux2 = (i - 1) + aux;
               convert_unix_to_data(batidas.bat[aux2].timeStamp, dia, mes, ano, hora, minuto, segundo);

                       s = segundo;
                       m = minuto;
                       h = hora;

                       break;
                   }
               }   
           }
     
    

int main()
{

    int aux = 1688180401;
    
    uint32_t temp_atual = aux; // Exemplo de timestamp Unix

    unsigned int dia, mes, ano, hora, minuto, segundo;

    convert_unix_to_data(temp_atual, dia, mes, ano, hora, minuto, segundo);

    std::cout << "Data: " << dia << "/" << mes << "/" << ano << std::endl;
    std::cout << "Hora: " << hora << ":" << minuto << ":" << segundo << std::endl;

    uint16_t auxiliar = (((ano % 1000) % 100)); // retira só os dois ultimos digitos do ano para caber em uint8_t
    uint8_t last_n_year = auxiliar;   // Verificar se vai funcionar em uint8

    uint8_t day = dia;
    uint8_t month = mes;
    uint8_t year = last_n_year;
    uint8_t hour = hora;
    uint8_t minute = minuto;
    uint8_t second = segundo;

    TIME_VAL atual;

    atual.dia = day;
    atual.ano = year;
    atual.mes = month;
    atual.hora = hour;
    atual.minuto = minute;
    atual.segundo = second;

    arquivo.bat[0].timeStamp = (1688180401);

    unsigned int k = 0;
    for (k = 0; k < 174; k++)
    {
        arquivo.bat[k].timeStamp = (1688180401 + (k * 14400));

        if(k%2 == 0){
            arquivo.bat[k].operacao = 1;
        }else {
            arquivo.bat[k].operacao = 2;
        }     
        arquivo.qtd_bat++;
    }
 
    Display_New_Page();

    // criar arquivo html e inserir a variavel webpage

    fstream arquivo;

    // PESSOA_TYP *colaborador = &funcionario[0];

    arquivo.open("Test_DB_html.html", ios::out);

   // arquivo.read((char*)arquivo.bytes, 1612);

    if (arquivo.is_open()) {
        cout << "Foi possivel abrir o arquivo\n" << endl;
    }
    else {
        cout << "Não foi possivel abrir o arquivo\n" << endl;
    }

    arquivo << webpage;

    arquivo.close();

    return 0;
}