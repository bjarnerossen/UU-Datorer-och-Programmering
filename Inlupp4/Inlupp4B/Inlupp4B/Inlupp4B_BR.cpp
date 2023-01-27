/*
 Kurs: Datorer och programmering, Sommar 2022
 Inlämningsuppgift: 4B
 Namn: Bjarne Rossen
 Personummer: 970121-1659
 */
 
#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
// Globala konstanter:
// Tips: Använd de globala konstanterna ANTAL_BOKSTAVER och ANTAL_SPRAK
// istället för värdena 26 och 4 i programmet.

const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP innehåller bokstavsfrekvensen i %
// för fyra språk. TOLK_HJALP[0][0]  r frekvensen av
// bokstaven a för engelska. TOLK_HJALP[0][25]  r frekvensen av
// bokstaven z för engelska.
// Arrayen är en GLOBAL KONSTANT och skall alltså  ej skickas
// som parameter till den funktion som behöver den.

const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER] =
       {{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
         7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
         0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
         1.89,0.03},
        {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
         7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
         1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
         0.30,0.15},
        {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
         3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
         0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
         0.45,0.00},
        {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
         8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
         0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
         0.69,1.24}};

// switch statement för att få indexet till språket.
string get_index(int i){
    switch(i){
        case 0:
            return "engelska";
        case 1:
            return "franska";
        case 2:
            return "svenska";
        case 3:
            return "tyska";
        default:
            return "undefined";
    }
}
// Globala variabler är ej tillåtna

//--------------------------------------------------------
// Funktionsdeklarationer:

// Funktionen berakna_histogram_abs
int berakna_histogram_abs(string fil, double frek[]);

// Funktionen abs_till_rel
void abs_till_rel(int letter_count, double frek[]);

// Funktionen plotta_histogram_rel
void plotta_histogram(double frek[]);

// Funktionen tolkning
void tolkning(double frek[]);

// Funktionen namn_pa_fil
string namn_pa_fil();

// Funktionen inlasning
string inlasning(string filnamn);

//--------------------------------------------------------
// Huvudprogram:
int main()
{
    // Deklarera variabler
    string fil;
    double frek [ANTAL_BOKSTAVER] = {};
    int letter_count;

    fil = inlasning(namn_pa_fil());
    if(fil == "") return 0;
    
    // Anrop av funktionerna i huvudprogramet
    letter_count = berakna_histogram_abs(fil, frek);
    abs_till_rel(letter_count, frek);
    tolkning(frek);
    plotta_histogram(frek);
    
  return 0;
}
//--------------------------------------------------------
// Funktionsdefinitioner:

// Funktionen beräkrnar ett histogram utifrån en textfil,
// och sedan eturnerar hur många totala bokstäver som förekom.
int berakna_histogram_abs(string fil, double frek[]){
    int letter_count = 0;
    for(int i = 0; i < fil.length(); i++){
        if(fil[i] >= 'a') fil[i] -= 'a';
        else fil[i] -= 'A';
        if(fil[i] >= 0 && fil[i] < 26){
            frek[fil[i]]++;
            letter_count++;
        }
    }
    cout << "Totala antalet bokstäver: " << letter_count << endl;
    return letter_count;
}

// Funktionen räknar om histogramets absoluta värden till relativa
void abs_till_rel(int letter_count, double frek[]){
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        frek[i] = (frek[i] / letter_count) * 100;
    }
}

void plotta_histogram(double frek[]){
    char bokstav = 'A';
    cout << "Bokstavsfördelning:" << endl << endl;
    for(int i = 0; i < ANTAL_BOKSTAVER; i++){
        cout << bokstav << " ";
        for(int j = 0; j < nearbyint(frek[i]); j++){
            cout << '*';
        }
        cout << endl;
        bokstav++;
    }
}

void tolkning (double frek[]){
    double kvadratsumma[ANTAL_SPRAK] = {};
    int mest_sannolik = 0;
    for (int i = 0; i < ANTAL_SPRAK; i++){
        for(int j = 0; j < ANTAL_BOKSTAVER; j++){
            kvadratsumma[i] += pow(frek[j] - TOLK_HJALP[i][j], 2);
        }
        cout << get_index(i) + " har kvadratsumma= "   << kvadratsumma[i] << endl;
        if(kvadratsumma[i] < kvadratsumma[mest_sannolik]) mest_sannolik = i;
    }
    cout << "Det är mest troligt att språket är " + get_index(mest_sannolik) << endl << endl;
}

// Funktionen läser in ett filnamn.
string namn_pa_fil(){
    string filnamn = "";
    cout << "Ange filnamn:" << endl;
    cin >> filnamn;
    return filnamn;
}

// Funktionen läser in en fil baserat på ett filnamn.
string inlasning(string filnamn){
    string text = "";
    string rad;
    ifstream fil(filnamn);
    if(!fil.is_open()) {
        cout << "Det finns ingen fil med namnet " + filnamn << endl;
        return "";
    }
    while(getline(fil, rad)) text.append(rad);
    fil.close();
    return text;
}

/*
 -------------------------------------------------------
 Testkörningar
 -------------------------------------------------------
 
 ------------------------------------------------------
 TEST 1
 ------------------------------------------------------
 
 Ange filnamn:
 doyle.txt
 Totala antalet bokstäver: 12885
 engelska har kvadratsumma= 1.75771
 franska har kvadratsumma= 96.1956
 svenska har kvadratsumma= 73.3371
 tyska har kvadratsumma= 116.072
 Det är mest troligt att språket är engelska

 Bokstavsfördelning:

 A ********
 B *
 C ***
 D ****
 E ************
 F **
 G *
 H ******
 I ********
 J
 K *
 L ****
 M ***
 N ******
 O ********
 P **
 Q
 R ******
 S ******
 T *********
 U ***
 V *
 W **
 X
 Y **
 Z
 Program ended with exit code: 0
 
 ------------------------------------------------------
 TEST 2
 ------------------------------------------------------
 
 Ange filnamn:
 goethe.txt
 Totala antalet bokstäver: 14027
 engelska har kvadratsumma= 107.856
 franska har kvadratsumma= 85.205
 svenska har kvadratsumma= 160.318
 tyska har kvadratsumma= 1.04313
 Det är mest troligt att språket är tyska

 Bokstavsfördelning:

 A *****
 B **
 C ****
 D *****
 E *****************
 F *
 G ***
 H ******
 I *********
 J
 K *
 L ***
 M ***
 N ***********
 O **
 P
 Q
 R ******
 S *******
 T ******
 U ****
 V *
 W **
 X
 Y *
 Z *
 Program ended with exit code: 0
 
 ------------------------------------------------------
 TEST 3
 ------------------------------------------------------
 
 Ange filnamn:
 lagerlof.txt
 Totala antalet bokstäver: 12221
 engelska har kvadratsumma= 86.6804
 franska har kvadratsumma= 145.722
 svenska har kvadratsumma= 8.88258
 tyska har kvadratsumma= 170.223
 Det är mest troligt att språket är svenska

 Bokstavsfördelning:

 A ***********
 B *
 C *
 D ******
 E **********
 F **
 G ****
 H ****
 I ****
 J *
 K ***
 L *****
 M ****
 N *********
 O ****
 P *
 Q
 R *******
 S *******
 T *********
 U **
 V ***
 W
 X
 Y
 Z
 Program ended with exit code: 0
 
 ------------------------------------------------------
 TEST4
 ------------------------------------------------------
 
 Ange filnamn:
 verne.txt
 Totala antalet bokstäver: 11417
 engelska har kvadratsumma= 112.425
 franska har kvadratsumma= 0.885142
 svenska har kvadratsumma= 149.256
 tyska har kvadratsumma= 90.491
 Det är mest troligt att språket är franska

 Bokstavsfördelning:

 A ********
 B *
 C ****
 D ****
 E *****************
 F *
 G *
 H *
 I *******
 J
 K
 L *****
 M ***
 N ********
 O *****
 P ***
 Q *
 R *******
 S ********
 T *******
 U ******
 V *
 W
 X *
 Y
 Z
 Program ended with exit code: 0
 
 ------------------------------------------------------
 TEST 5
 ------------------------------------------------------
 
 Ange filnamn:
 finnsInte.txt
 Det finns ingen fil med namnet finnsInte.txt
 Program ended with exit code: 0

-------------------------------------------------------
Rapport om uppgiften
-------------------------------------------------------

 Deluppgift B var mycket svårare än deluppgift A. Jag hade speciellt svårt med att lösa
 skickandet av alla arrayer mellan funktionerna. Det var hjälpsam att titta på de exempel
 vi fick och att gå igenom övningarnar. Således kunde jag komma fram till att arrayer som
 parametrar alltid är referenser och kan modifieras efter behov, sålänge man anropar dem i rätt ordning.
 Ett bra sätt att lösa uppgiften var att skriva pseudokod och försöka att översätta
 den till riktig kod.
 
 -------------------------------------------------------
 Frågor till uppgiften
 -------------------------------------------------------
  (1) I lösningsförslagen tipsar vi om att du ska skapa/ladda hem en fil med bara lite innehåll medan man testar sitt program. Varför, tror du?

    Syftet med en liten fil är att det blir enklare att kontrollera sina beräkningar
    och för att se om programmet ge det förväntade resultatet (debugging).
    Det gör det betydligt enklare att leta efter fel i sin kod som t.ex. en funktion eller beräkning.

  (2) Texten i filen lagerlof.txt innehåller de svenska bokstäverna å, ä och ö. Som programmet fungerar nu räknas inte dessa bokstäver med alls. Hur skulle man gå tillväga för att också inkludera å, ä och ö i histogrammet. Du behöver inte ge en program-lösning, men resonera kring hur man skulle kunna göra.

         Det som kunde göras är att utöka arrayernas frekvenser för Å, Ä och Ö och dessutom med fler platser för extrabokstäver.
         För bokstäverna å, ä och ö, som har ascii-värden högre än 127,vore en lösning att deklarera alla char som uns (unsigned)
         char för att rymma värdena 0 till 255.
*/
