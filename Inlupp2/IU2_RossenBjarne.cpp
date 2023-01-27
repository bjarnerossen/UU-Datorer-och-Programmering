#include <iostream>
using namespace std;

int main(){
    
    
    // Deklaration av variabler
    int startnummer = 0,
        starttid,
        maltid,
        sluttid = 0,
        antal = 0,
        vinnare = INT_MAX,
        vinnarnummer = 0,

    // Deklaration av starttid
        start_hour,
        start_minute,
        start_seconds,
    
    // Deklaration av måltid
        mal_hour,
        mal_minute,
        mal_seconds,
    
    // Deklaration av vinnartid
        vinnar_hour,
        vinnar_minute,
        vinnar_seconds;
        
    
    const int dygn = 24*60*60;           // En konstant variabel som räknar antal sekunder på ett dygn

    while (startnummer > 0) {
        cout << "Startnummer?: ";       // Ber användaren att mata in startnummer på tävlande
        cin >> startnummer;            // Sparar det numret i variabeln 'startnummer'
        cout << endl;
        antal++;

        cout << "Starttid?: ";                        // Ber användaren att mata in en starttid för startnumret
        cin >> start_hour >> start_minute >> start_seconds;                    // Sparar de värden som användaren har matat in i de olika variablerna
        starttid = start_hour * 3600 + start_minute * 60 + start_seconds;      // Räknar ut starttiden
        cout << endl;

        cout << "Måltid?: ";                         // Ber användaren att mata in en måltid för startnumret
        cin >> mal_hour >> mal_minute >> mal_seconds;                          // Sparar de värden som användaren har matat in i de olika variablerna
        maltid = mal_hour * 3600 + mal_minute * 60 + mal_seconds;              // Räknar ut måltiden
        cout << endl;

        
        
        if (starttid <= maltid){
            sluttid = maltid - starttid;
        }
        
        else if (starttid > maltid){               // Kollar om tiden går över 00 00 00, midnatt, dygnspassage
            sluttid = maltid + (dygn - starttid);
        }
    }

        if (sluttid < vinnare) {
            
           vinnare = sluttid;
           vinnarnummer = startnummer;
            
            // Räknar ut vinnartiden
            vinnar_hour = sluttid / 3600;
            vinnar_minute = sluttid / 60 - vinnar_hour * 60;
            vinnar_seconds = sluttid % 60;


            // Skriver ut resultaten/statistiken
            cout << endl;
            cout << endl;
            cout << endl;
            cout << "Vinnare är startnr: " << vinnarnummer << endl;
            cout << endl;
            cout << "Tim:" << vinnar_hour << " Min:  " << vinnar_minute << " Sek:  " << vinnar_seconds << endl;
            cout << endl;
            cout << "Antal tävlande: " << antal << endl;
            cout << endl;
        
            
        
            cout << "Programmet avslutas" << endl;
            return 0;
        }



}
