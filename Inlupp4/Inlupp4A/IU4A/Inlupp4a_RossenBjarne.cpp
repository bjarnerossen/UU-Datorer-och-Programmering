// Programskal till inlämningsuppgift 4 - deluppgift A
// Hanterar fallet med 26 bokstäver A-Z
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;
// Använd gärna denna globala konstant i programmet
// istället för värdet 26
const int ANTAL_BOKSTAVER = 26;  //A-Z
// Globala variabler är ej tillåtna
//--------------------------------------------------------
// Funktionsdeklarationer:
// Använd exakt de funktionsnamn som finns nedan
int berakna_histogram_abs(string &rad, int dict[], int &letter_count);
void skriv_histogram_abs(int dict[], int &letter_count);
//--------------------------------------------------------
// Huvudprogram:
int main()
{
  // Deklarera variabler
    string rad;
    int dict[ANTAL_BOKSTAVER]; // Array med 26 bokstäver
    
    int letter_count = 0;
    
  // Läs in en rad med text från tangentbordet
    cout<<"Mata in en rad text: ";
    getline(cin,rad);
    cout << endl;
  
 // Funktionsdeklarationer:
    berakna_histogram_abs(rad, dict, letter_count);
    skriv_histogram_abs(dict, letter_count);
 
  // Anropa funktionen skriv_histogram_abs som skriver ut histogrammet
  
  return 0;
}
//--------------------------------------------------------
// Funktionsdefinitioner:
int berakna_histogram_abs(string &rad, int dict[], int &letter_count) {
    
    //Nollställ arrayen dict[] till noll:
    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
      dict[i] = 0;
    
    // Loopa igenom hela raden (strängen), tecken för tecken
    for (int i=0; i< (int) rad.length(); i++)
      {
        int index;
        
          // Användning av funktionen tolower för att göra alla bokstäver till så bokstäver
          rad[i] = tolower(rad[i]);
          
        // Om tecknet är en gemen
        if (rad.at(i) >= 'a' && rad.at(i) <= 'z')
      {
          // räkna ut platsen i arrayen
          index = rad.at(i) - 'a';
          // uppdatera räknaren på rätt plats
          dict[index]++;
          // uppdatera räknaren för total antal bokstäver
          letter_count++;
      }
    }
    
    // Return alla bokstäver
    return letter_count;
}

void skriv_histogram_abs(int dict[], int &letter_count) {
    //Skriv ut frekvensen i en tabell
    
    cout << "Totalt antal bokstäver: " << letter_count << endl;
    cout << "Bokstavsfördelning:" << endl << endl;
    
    // Loopa över alla platser i arrayen och skriva ut dem
    for (int i = 0; i < ANTAL_BOKSTAVER; i++)
      {
        // Konvertera platsen till ett teckenvärde
        char b = char (i+'A');
        cout << b << ": " << dict[i] <<endl;
      }
}

// TESTKÖRNINGAR

// TESTDATA 1

//Mata in en rad text: AbCdNNooPPwXyZ
//
//Totalt antal bokstäver: 14
//Bokstavsfördelning:
//
//A: 1
//B: 1
//C: 1
//D: 1
//E: 0
//F: 0
//G: 0
//H: 0
//I: 0
//J: 0
//K: 0
//L: 0
//M: 0
//N: 2
//O: 2
//P: 2
//Q: 0
//R: 0
//S: 0
//T: 0
//U: 0
//V: 0
//W: 1
//X: 1
//Y: 1
//Z: 1
//Program ended with exit code: 0

// TESTDATA 2

//Mata in en rad text: 1234ddddacccbb!?
//
//Totalt antal bokstäver: 10
//Bokstavsfördelning:
//
//A: 1
//B: 2
//C: 3
//D: 4
//E: 0
//F: 0
//G: 0
//H: 0
//I: 0
//J: 0
//K: 0
//L: 0
//M: 0
//N: 0
//O: 0
//P: 0
//Q: 0
//R: 0
//S: 0
//T: 0
//U: 0
//V: 0
//W: 0
//X: 0
//Y: 0
//Z: 0
//Program ended with exit code: 0

// TESTDATA 3

//Mata in en rad text: Denna rad innehåller ett å!
//
//Totalt antal bokstäver: 20
//Bokstavsfördelning:
//
//A: 2
//B: 0
//C: 0
//D: 2
//E: 4
//F: 0
//G: 0
//H: 1
//I: 1
//J: 0
//K: 0
//L: 2
//M: 0
//N: 4
//O: 0
//P: 0
//Q: 0
//R: 2
//S: 0
//T: 2
//U: 0
//V: 0
//W: 0
//X: 0
//Y: 0
//Z: 0
//Program ended with exit code: 0

// TESTDATA 4

//Mata in en rad text:
//
//Totalt antal bokstäver: 0
//Bokstavsfördelning:
//
//A: 0
//B: 0
//C: 0
//D: 0
//E: 0
//F: 0
//G: 0
//H: 0
//I: 0
//J: 0
//K: 0
//L: 0
//M: 0
//N: 0
//O: 0
//P: 0
//Q: 0
//R: 0
//S: 0
//T: 0
//U: 0
//V: 0
//W: 0
//X: 0
//Y: 0
//Z: 0
//Program ended with exit code: 0

// Redovisning av uppgiften i ord.
