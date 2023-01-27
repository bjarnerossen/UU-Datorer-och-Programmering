/*
 Kurs: Datorer och programmering, Sommar 2022
 Inlämningsuppgift: 6B
 Namn: Bjarne Rossen
 Personummer: 970121-1659
 */

#include <fstream>
#include <iostream>
#include <string>
using namespace std;


// -- Klass deklarationer --

// En klass som lagrar vädret och kan hantera enskilda kviton
class Transaktion
 {
 private:
   string  datum;
   string  typ;
   string  namn;
   double  belopp;
   int     antal_kompisar;
   string *kompisar;

  public:
   Transaktion(); // Konstruktor
   ~Transaktion(); // Destruktor
   Transaktion& operator=( const Transaktion& t); // Överlagrad tilldelningsoperator
   string hamtaNamn() const;
   double hamtaBelopp() const;
   int    hamtaAntalKompisar() const;
   bool   finnsKompis(const string &namnet) const; // Kontroll om kompis finns eller ej
   bool   lasIn(istream &is); // Inläsningen från txtfil
   void   skrivUt(ostream &os) const; // utskrift
   void   skrivTitel(ostream &os) const;
   void   skrivHjalp(ostream &os); // Tillagd
 };

 // Lagrar sammanslagna transaktiondata som har deltagit i sammanhanget.
class Person
{
  private:
  string namn;
   double betalat_andras; // ligger ute med totalt
   double skyldig;        // skyldig totalt

 public:
   Person(); // Konstuktor
   Person(const string &namn, double betalat_andras, double skyldig); // Överlagrad konstruktur
   string hamtaNamn();
   double hamtaBetalat();
   double hamtaSkyldig();
   void skrivUt(ostream &os);// Utskrift
};

class PersonLista
 {
 private:
   int     antal_personer;
   Person *personer;

 public:
   PersonLista();
   ~PersonLista();
   void   laggTill(Person ny_person);
   void   skrivUtOchFixa(ostream &os);
   double summaSkyldig() const;
   double summaBetalat() const;
   bool   finnsPerson(const string &namn);
 };

  class TransaktionsLista
 {
 private:
   int          antal_transaktioner;
   Transaktion *transaktioner;

 public:
   TransaktionsLista(); // konstruktor
   ~TransaktionsLista(); // Destruktor
   void   lasIn(istream & is);
   void   skrivUt(ostream & os);
   void   laggTill(Transaktion & t); //lägger till en transaktion i slutet av arrayen
   double totalKostnad() const;
   double liggerUteMed(const string &namnet); // Beräknar hur mycket en person har betalat
   double arSkyldig(const string &namnet); // Beräknar hur mycket en person är skyldig
   PersonLista FixaPersoner();
 };



 // -- Ankallelse av Main - Huvudprogram --
 int main ()
 {
    cout << "Startar med att läsa från en fil." << endl;

  TransaktionsLista transaktioner;
  ifstream     is("resa.txt");
  transaktioner.lasIn(is);

  int operation = 1;
  while (operation != 0)
    {
      cout << endl;
      cout << "Välj i menyn nedan:" << endl;
      cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
      cout << "1. Skriv ut information om alla transaktioner." << endl;
      cout << "2. Läs in en transaktion från tangentbordet." << endl;
      cout << "3. Beräkna totala kostnaden." << endl;
      cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
      cout << "5. Hur mycket ligger en viss person ute med?" << endl;
      cout << "6. Lista alla personer mm och FIXA" << endl;

      cin >> operation;
      cout << endl;

      switch (operation)
        {
          case 1:
            {
              Transaktion transaktion;
              transaktion.skrivTitel(cout);
              transaktioner.skrivUt(cout);
              break;
            }
          case 2:
            {
              Transaktion transaktion;
              cout << "Ange transaktion i följande format" << endl;
              transaktion.skrivHjalp(cout);
              transaktion.lasIn(cin);
              transaktioner.laggTill(transaktion);
              break;
            }
          case 3:
            {
              cout << "Den totala kostnanden för resan var "
                   << transaktioner.totalKostnad() << endl;
              break;
            }
          case 4:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ar_skyldig = transaktioner.arSkyldig(namn);
              if (ar_skyldig == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " är skyldig " << ar_skyldig << endl;
              break;
            }
          case 5:
            {
              cout << "Ange personen: ";
              string namn;
              cin >> namn;
              double ligger_ute_med = transaktioner.liggerUteMed(namn);
              if (ligger_ute_med == 0.)
                cout << "Kan inte hitta personen " << namn << endl;
              else
                cout << namn << " ligger ute med " << ligger_ute_med << endl;
              break;
            }
          case 6:
            {
              cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
              PersonLista lista = transaktioner.FixaPersoner();
              lista.skrivUtOchFixa(cout);
              break;
            }
        }
    }

  std::ofstream os("transaktioner.txt");
  transaktioner.skrivUt(os);

  return 0;
}

// -----------------------------------------------------
// Klassdefinitioner

 //  -- Transaktion -- :

//Konstruktur
 Transaktion::Transaktion()
 {
   //Nollstälning av befinitliga variabler
   namn="";
   datum="";
   typ="";
   belopp = 0.0;
   antal_kompisar = 0;
   kompisar = 0;
 }


// Överlagrad tilldelningsoperator
 Transaktion& Transaktion::operator=( const Transaktion& t)
{
  if (this != &t)
    {
      delete[] kompisar;
      datum          = t.datum;
      typ            = t.typ;
      namn           = t.namn;
      belopp         = t.belopp;
      antal_kompisar = t.antal_kompisar;
      kompisar       = new string[antal_kompisar];
      for (int i=0; i < antal_kompisar; i++)
    kompisar[i] = t.kompisar[i];
    }
  return *this;
}
// Destruktor
 Transaktion::~Transaktion()
 {
     delete[] kompisar; // Avalloklerar mionne
     kompisar = 0; // Återställer kompisar till 0
 }
// Selektorer
// Som hämtar infomration om befintliga variabler
string Transaktion::hamtaNamn() const
{
  return namn;
}

double Transaktion::hamtaBelopp() const
{
  return belopp;
}

int Transaktion::hamtaAntalKompisar() const
{
  return antal_kompisar;
}

// Kontrollerar om kompisen finns
bool Transaktion::finnsKompis(const string &namnet) const
{

  for (int i= 0; i < antal_kompisar ; i++)
  {
    if(kompisar[i] == namnet)
    {
      return true;
  }
  }
return false;

}

// Läser data om en transaktion, ankallas av while loop
bool Transaktion::lasIn(istream &is)
{
  // Inläsning
 is >> datum >> typ >> namn >> belopp >> antal_kompisar;

  kompisar = new string[antal_kompisar]; // Allokerar minne för en ny array

 for (int i=0; i < antal_kompisar; i++)
 {
   is >> kompisar[i]; // Storrar varje namn i is genom användning av for loop
 }

 
 return !is.eof();
}

// Skriver ut alla data om klassen.
void Transaktion::skrivUt(ostream &os) const
{
  
 os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << antal_kompisar << "\t";
  for (int i =0; i < antal_kompisar; i++)
  {
    os << "\t" << kompisar[i] ;
    }
  os << endl ;
}
// Skriver titeln som beskriver kolumnen.
void Transaktion::skrivTitel(ostream &os) const
{
  os << "Datum" << "\t" << "Typ" << "\t" << "Namn" << "\t" << "Belopp" << "\t" << "Antal och lista av kompisar" << "\t" << endl;
  // Skrev om main, tror tillropet var felaktigt för att få till det alternativ 1.
}

// Förklara hur man sak ska skriva in en ny transaktion från tagentbordet.
void Transaktion::skrivHjalp(ostream &os)
{
  os << "Datum (yymmdd) typ av transaktion namn belopp antal och lista på kompisar " << endl;
}


// ----------------------------------------------------------------------------------------
//    -- Person -- :

// Konstruktur
Person::Person()
{
  namn ="";
  betalat_andras=0.0;
  skyldig = 0.0;
}
// Överlagrad konstuktur
Person::Person(const string &namn, double betalat_andras, double skyldig)
{
  this -> namn = namn ; // Använder pekare hittade inget annat sätt när man har samma variabelnamn som input
  this -> betalat_andras = betalat_andras;
  this -> skyldig  = skyldig;
}

// Selektorer
// Tar ut relevant information
string Person::hamtaNamn()
{
  return namn;
}

double Person::hamtaBetalat()
{
    return betalat_andras;
}

double Person::hamtaSkyldig()
{
  return skyldig;
}

// Skriver ut hur mycket personen har betalat, hur mycket man är skyldig och och mycket pengar man ska få alternativt betala
void Person::skrivUt(ostream &os)
{
cout << namn << " ligger ute med: " << betalat_andras << " kr och är skyldig " << skyldig << " kr. ";
  if (skyldig < betalat_andras)
  {
    cout << "Skall ha " << ( betalat_andras - skyldig ) << " kr från potten!" << endl;
  }
  else
  {
  cout << "Skall lägga till " << ( skyldig - betalat_andras ) <<" kr till potten!"<< endl;
  }
}

// -- PersonLista -- :
//Konstrukor, nollställning
PersonLista::PersonLista()
{
  antal_personer = 0;
  personer = 0;
}
// Destruktur
PersonLista::~PersonLista()
{
    delete[] personer; // avallokering
    personer = 0;
}


// Fyller person array
void PersonLista::laggTill(Person ny_person)
{
    Person *nyperson = 0;
    nyperson = new Person[antal_personer + 1]; // Allokellerar nytt minne
    for (int i = 0; i < antal_personer; i++)
    {
        nyperson[i]=personer[i]; // kopierar över personer till den nya
    }

    delete[] personer; // Avallokelra minne
    personer = nyperson; // Ansätter nytt värde för personer

    nyperson[antal_personer] = ny_person;     // lägg in transaktion sist i arrayen
    antal_personer++;      // öka antalet transaktioner i arrayen
}

// Skriver ut informationen om varje personobjekt i arrayen
void PersonLista::skrivUtOchFixa(ostream &os)
{
    for(int i = 0; i < antal_personer; i++)
    {
        personer[i].skrivUt(os);
    }

}

// Hämtar summan som personen är skyldig.
double PersonLista::summaSkyldig() const
{
 double skyldig = 0.0; // Nollställning av skyldig

  for (int i = 0; i < antal_personer; i++)
  {
    skyldig = skyldig + personer[i].hamtaSkyldig();
  }
  return skyldig;
}

// Summan av allt en person har betalat
double PersonLista::summaBetalat() const
{
  double betalat_andras= 0.0;

  for (int i = 0; i < antal_personer; i++ )
  {
    betalat_andras = betalat_andras + personer[i].hamtaBetalat();
  }

  return betalat_andras;
}

// Kontroll om givna namn finns
bool PersonLista:: finnsPerson(const string &namn)
{
   for(int i = 0; i < antal_personer; i++)
  {
    if (personer[i].hamtaNamn() == namn)
    {
      return true;
    }
  }
  return false;
  
}

// -- TransaktionsLista -- :

// Konstuktor
TransaktionsLista::TransaktionsLista()
{
  antal_transaktioner = 0;
  transaktioner=0;
}
// Destruktor
TransaktionsLista::~TransaktionsLista()
{
delete[] transaktioner; // Avallokering
transaktioner = 0;

}
// Inläsning från fil till klassen transaktion

 void TransaktionsLista::lasIn(istream & is)
 {
  // En inläsningsmetod i klassen TransaktionsLista.
  Transaktion t;
  
  // Så länge det går bra att läsa (filen ej slut)
  while (t.lasIn(is))
   {
     laggTill( t );
   }

 }

// Skriver ut med hjälp av skrivUt från Transaktion
 void TransaktionsLista::skrivUt(ostream & os)
 {
   for(int i= 0; i < antal_transaktioner; i++)
   {
     transaktioner[i].skrivUt(os);
   }
 cout << "Antal transaktioner är: " << antal_transaktioner << endl;
 }

// Lägger till en transaktion i slutet av arrayen nyTransaktion
 void TransaktionsLista::laggTill(Transaktion & t)
 {
    Transaktion *nyTransaktion = 0; // Nollställning
    nyTransaktion = new Transaktion[antal_transaktioner + 1]; // Allokering av minne

    for (int i = 0; i < antal_transaktioner ; i++)
    {
        nyTransaktion[i]=transaktioner[i]; // kopierar över personer till den nya
    }

    delete[] transaktioner; // Avallokellar minne
    transaktioner = nyTransaktion; // Ansätt nytt värde

    nyTransaktion[antal_transaktioner] = t;     // lägg in transaktion sist i arrayen
    antal_transaktioner++;          // öka antalet transaktioner i arrayen

 }

//Beräknar den totala kostnaden genom att returnera alla utgifter
double TransaktionsLista::totalKostnad() const
{
  double totalKostnad = 0.0;

  for(int i = 0; i< antal_transaktioner; i++)
  {
    totalKostnad += transaktioner[i].hamtaBelopp();
  }
  return totalKostnad;
}

// Hur mycket en person har betalat (hur mycket pengar dom ligger ute med) tagen från Studium
double TransaktionsLista::liggerUteMed(const string &namnet)
{

 double summa = 0.0;
   for (int i = 0; i < antal_transaktioner; i++)
     if (transaktioner[i].hamtaNamn() == namnet)
       summa += transaktioner[i].hamtaBelopp() *
                (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
   return summa;
 }
// Hur mycket en person är skyldig
double TransaktionsLista::arSkyldig(const string &namnet)
{
  double skuld = 0.0;
    
    for(int i = 0; i < antal_transaktioner; i++)
    {
        if (transaktioner[i].finnsKompis(namnet)) // kontrollerar om namnet ingår finns mha finnsKompisar i transaktion
        skuld += (transaktioner[i].hamtaBelopp()/(transaktioner[i].hamtaAntalKompisar() + 1));
        // Tar belopp/(antal personer + 1) på för att se hur mycket varje enskild person e skyldig
    }
    
    return skuld ;
}

// Skapar och returnerar ett objekt, går igenom terransaktionlista, används för printen.
PersonLista TransaktionsLista::FixaPersoner()
{
  PersonLista Personlista;
  string namn;
  
     for(int i = 0; i < antal_transaktioner; i++)
    {
        namn = transaktioner[i].hamtaNamn();

        if(!Personlista.finnsPerson(namn))
        {
            Person pers(namn, liggerUteMed(namn), arSkyldig(namn));

            Personlista.laggTill(pers); // lägger till en ny person, börjar om iteration
        }

    }
    return Personlista;
}

/*
 -------------------------------------------------------
 Testkörningar
 -------------------------------------------------------
 
 -------------------------------------------------------
 TEST 1
 -------------------------------------------------------
 
 Startar med att läsa från en fil.

 Välj i menyn nedan:
 0. Avsluta. Alla transaktioner sparas på fil.
 1. Skriv ut information om alla transaktioner.
 2. Läs in en transaktion från tangentbordet.
 3. Beräkna totala kostnaden.
 4. Hur mycket ärr en viss person skyldig?
 5. Hur mycket ligger en viss person ute med?
 6. Lista alla personer mm och FIXA
 1

 Datum    Typ    Namn    Belopp    Antal och lista av kompisar
 190615    transp    Eva    6000    5        Bosse    Kristin    Paul    Torsten    Stina
 190721    mat    Eva    300    2        Bosse    Kristin
 190721    mat    Paul    400    2        Torsten    Stina
 190721    transp    Bosse    5000    3        Eva    Kristin    Paul
 190721    transp    Stina    5000    1        Torsten
 190722    boende    Kristin    200    1        Eva
 190722    mat    Eva    300    2        Kristin    Bosse
 190723    mat    Torsten    300    2        Paul    Stina
 190724    mat    Paul    200    1        Stina
 190725    transp    Eva    600    3        Bosse    Kristin    Paul
 Antal transaktioner är: 10
 
 -------------------------------------------------------
 TEST 2
 -------------------------------------------------------
 
 Startar med att läsa från en fil.

 Välj i menyn nedan:
 0. Avsluta. Alla transaktioner sparas på fil.
 1. Skriv ut information om alla transaktioner.
 2. Läs in en transaktion från tangentbordet.
 3. Beräkna totala kostnaden.
 4. Hur mycket ärr en viss person skyldig?
 5. Hur mycket ligger en viss person ute med?
 6. Lista alla personer mm och FIXA
 3

 Den totala kostnanden för resan var 18300
 
 -------------------------------------------------------
 TEST 3
 -------------------------------------------------------
 
 Välj i menyn nedan:
 0. Avsluta. Alla transaktioner sparas på fil.
 1. Skriv ut information om alla transaktioner.
 2. Läs in en transaktion från tangentbordet.
 3. Beräkna totala kostnaden.
 4. Hur mycket ärr en viss person skyldig?
 5. Hur mycket ligger en viss person ute med?
 6. Lista alla personer mm och FIXA
 4

 Ange personen: Bosse
 Bosse är skyldig 1350
 
 -------------------------------------------------------
 TEST 4
 -------------------------------------------------------
 
 Välj i menyn nedan:
 0. Avsluta. Alla transaktioner sparas på fil.
 1. Skriv ut information om alla transaktioner.
 2. Läs in en transaktion från tangentbordet.
 3. Beräkna totala kostnaden.
 4. Hur mycket ärr en viss person skyldig?
 5. Hur mycket ligger en viss person ute med?
 6. Lista alla personer mm och FIXA
 5

 Ange personen: Bosse
 Bosse ligger ute med 3750
 
 -------------------------------------------------------
 TEST 5
 -------------------------------------------------------

 Välj i menyn nedan:
 0. Avsluta. Alla transaktioner sparas på fil.
 1. Skriv ut information om alla transaktioner.
 2. Läs in en transaktion från tangentbordet.
 3. Beräkna totala kostnaden.
 4. Hur mycket ärr en viss person skyldig?
 5. Hur mycket ligger en viss person ute med?
 6. Lista alla personer mm och FIXA
 6

 Nu skapar vi en personarray och reder ut det hela!
 Eva ligger ute med: 5850 kr och är skyldig 1350 kr. Skall ha 4500 kr från potten!
 Paul ligger ute med: 366.667 kr och är skyldig 2500 kr. Skall lägga till 2133.33 kr till potten!
 Bosse ligger ute med: 3750 kr och är skyldig 1350 kr. Skall ha 2400 kr från potten!
 Stina ligger ute med: 2500 kr och är skyldig 1333.33 kr. Skall ha 1166.67 kr från potten!
 Kristin ligger ute med: 100 kr och är skyldig 2600 kr. Skall lägga till 2500 kr till potten!
 Torsten ligger ute med: 200 kr och är skyldig 3633.33 kr. Skall lägga till 3433.33 kr till potten!
 
 */
