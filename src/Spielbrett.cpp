/** Spielbrett
 * Definitionen der Klassen Spielbrett, Position und Zug
 * Die zugehörigen Methoden bilden die Logik des Spiels und verarbeiten die Eingaben der Spieler
 */

#include "Spielbrett.hpp"

#include <stdio.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <iterator>



SpielBrett::SpielBrett() : vorgaenger(*this) // Start Konstruktor
/* *this = Dereferenzierter Pointer zum jeweiligen Spielbrett Objekt - hat also ein Spielbrett als Wert, keine Speicheradresse
 * Der Vorgänger des initialen Brettes ist das Brett selbst (damit die Eingabe von '-' im ersten Zug das Programm
 * nicht durcheinander bringt)
 */
{ // Konstruktor der Klasse Spielbrett zum Erzeugen des Spielfelds
    geschlageneFigurenW=0; // Initialisierung der Zähler für die Punkte
    geschlageneFigurenB=0;

    initBrett(); // Initalisierung des Spielbrettes
}

SpielBrett::SpielBrett(const SpielBrett& spielBrett) : zugZahl(spielBrett.zugZahl+1), vorgaenger(spielBrett) // copy constructor für neue Züge
{   // Die folgenden vier Variablen plus dem aktuellen Brett werden vom vorigen Spielbrett-Objekt übernommen
    geschlageneFigurenW=spielBrett.geschlageneFigurenW;
    geschlageneFigurenB=spielBrett.geschlageneFigurenB;
    spielerNamen[0]=spielBrett.spielerNamen[0];
    spielerNamen[1]=spielBrett.spielerNamen[1];

    std::copy(std::begin(spielBrett.brett), std::end(spielBrett.brett), std::begin(brett));
}

    void SpielBrett::initBrett()
    {
        for (y = 0; y < 8; y++)
        {        // Durch die Zeilen iterieren
            for (x = 0; x < 8; x++)
            {     // Durch die Spalten iterieren
                if ((((x + y) % 2) == 0) && (y < 3))
                {    // Modulo für abwechselnde Färbung
                    brett[y][x] = 'B';  // schwarze Figuren
                }
                else if ((((x + y) % 2) == 0) && (y > 4))
                {
                    brett[y][x] = 'W';  // weiße Figuen
                }
                else if (((x + y) % 2) == 0)
                {
                    brett[y][x] = '0';  // schwarze Felder
                }
                else
                {
                    brett[y][x] = ' '; // weiße bzw. leere Felder
                }
            }
        }
    }

    void SpielBrett::ausgabeBrett()
    { // Funktion die alle Felder des Spielbretts ausgibt und ein simples Interface hinzufügt
        std::cout << spielerNamen[0] <<" spielt B\n (Punkte: " << geschlageneFigurenW << ")\n"; // Punkte
        std::cout << "   A B C D E F G H\n"; // UI: Benennung der Spalten mit den Buchstaben A-H

        for (y = 0; y < 8; y ++)
        { // Für jede Zeile ..
            std::cout << y+1; std::cout <<" "; std::cout <<"|"; // UI: Benennung der Zeilen mit den Zahlen 1-8
            for (x = 0; x < 8; x++)
            { // .. . jede Spalte
                std::cout << brett[y][x]; std::cout <<"|";
            }
            std::cout << std::endl;
        }
        // UI: Punkte Spieler 2
        std::cout << spielerNamen[1]<<" spielt W\n (Punkte: " << geschlageneFigurenB << ")\n";
        //std::cout << brett[0][0] << std::endl; // Debug Testausgabe
    }

// prüfen, ob die eingegebene Startposition gültig ist
Pos::Pos(std::string s)
{   // Todo: Exception handling verbessern
    int posFehler = 300;

    if(s.length()!=2) // Positionsangaben dürfen nicht länger sein als zwei Zeichen
    {
        std::cout << "Die Eingabe '" << s << "' bezeichnet keine gültige Position." << std::endl;
        throw posFehler;
    }
    x = s[0] - 'A'; // Konvertierung char zu int um die Eingaben auf das Array anwenden zu können
    y = s[1] - '0' -1;

    if(y<0||y>7) // Prüfen ob die Eingabe der Startposition innerhalb der Zeilen liegt
    {
        std::cout << "Der Zeilenwert '" << s[1] << "' ist ungültig." << std::endl;return;
    }
    if(x<0||x>7) // Prüfen ob die Eingabe der Startposition innerhalb der Spalten liegt
    {
        std::cout << "Der Spaltenwert '" << s[0] << "' (" << x << ") ist ungültig." << std::endl;return;
    }

}
    void Pos::print() // Ausgabemöglichkeit für Tests
    {
     std::cout << x << ", " << y << std::endl;
    }

    void Zug::print() // Ausgabemöglichekeit für Tests
    {
        start.print();
        ziel.print();
    }

// Überprüfen ob mit der Eingabe einer der beiden Zugtypen ausführbar ist
Zug::Zug(std::string s) : start(s.substr(0,2)), ziel(s.substr(2,2))
{
    if((abs(start.y-ziel.y)==1)&&(abs(start.x-ziel.x)==1)) // wenn der Zug auf das diagonal benachbarte Feld gehen soll, muss Zugtyp LAUFEN geprüft werden
    {
       typ = LAUFEN;
       return;
    }
    if((abs(start.y-ziel.y)==2)&&(abs(start.x-ziel.x)==2)) // wenn der Zug ein Feld überspringen soll, muss Zugtyp SCHLAGEN geprüft werden
    {
        typ = SCHLAGEN;
        return;
    }
    //Wenn beides nicht gilt, muss etwas anderes eingegeben werden
    std::cout << "Ungültiger Zug. Positionen nicht diagonal nebeneinander in Entfernung 1 oder 2." << std::endl;
    throw UngueltigerZug();
}

// Jetzt muss geprüft werden, ob der konkrete Zug möglich ist
// Dafür werden eine Reihe von Bedingungen überprüft und gebenenfalls eine neue Eingabe gefordert
SpielBrett* Zug::anwenden(SpielBrett& altesSpielBrett)
/* SpielBrett* ... = Ausgabetyp der Funktion
 * Die Funktion 'anwenden' der Klasse Zug wird auf die Referenz auf das aktuelle Spielbrettes angewendet
 * Dieses wird hier in altesSpielBrett genannt, da es bei erfolgreicher Durchführung des Zuges den alten Spielstand darstellt
 * Referenz ist wichtig, da hier nicht der Pointer auf dem Stack, sondern der tatsächliche Speicher benötigt wird
 */

{
    spielerChar[0] = 'B';
    spielerChar[1] = 'W';
    aktiverSpielerChar = spielerChar[(altesSpielBrett.zugZahl+1)%2];
    passiverSpielerChar = spielerChar[(altesSpielBrett.zugZahl)%2];

    // Zwei allgemeine Bedingungen: Gewählte Figur muss dem aktiven Spieler gehören und dieser muss sich vorwärts bewegen
    if(altesSpielBrett.brett[start.y][start.x]!=aktiverSpielerChar)
    {
        std::cout << "An dieser Stelle steht keine Figur " << aktiverSpielerChar << std::endl;
        throw UngueltigerZug();
    }

    else if((aktiverSpielerChar == 'B')&&!(start.y<ziel.y))
    {
        std::cout << "Bitte bewegen Sie sich vorwärts!" << std::endl;
        throw UngueltigerZug();
    }

    else if((aktiverSpielerChar == 'W')&&!(start.y>ziel.y))
    {
        std::cout << "Bitte bewegen Sie sich vorwärts!" << std::endl;
        throw UngueltigerZug();
    }

    SpielBrett* spielBrett = new SpielBrett(altesSpielBrett);

    /* Wurde ein gültiger Zug eingegeben, wird eine Kopie vom alten Spielbrett angelegt
     * Das neue Spielbrett ist ein Klon des alten Spielbrettes, übernimmt alle relevanten Werte
     * Bevor der Zug angewendet wird, wird der aktuelle Stand als "vorgänger" gesichert
     * damit später der dann "vorherige" Spielstand beim Laden abgerufen werden kann
     * new = dynamic memory allocation, erstellt pointer
     * Objekt entsteht auf Heap und muss theoretisch manuell entfernt werden
     * Für dieses Programm aber nicht wirklich relevant, da entstehender Speicher minimal ist
     * Wird das Programm beendet, werden alle Spielbrett-Objekte gelöscht
     */

    // Prüfen ob der konkrete Zug entsprechend seines Types durchführbar ist
    // Wenn ja, wird er auf das Spielbrett angewendet
    // TODO: Wenn Nein, zuvor erstelltes neues spielBrett vom Heap löschen
    // die "delete spielBrett;" Zeile habe ich später eingefügt
    //Alternativ könnte das neue Spielbrett auch erst der Prüfung der hier relevanten Bedingungen erstellt werden
    switch(typ)
    {
            case LAUFEN:
            {
                if(altesSpielBrett.brett[ziel.y][ziel.x]!='0')
                {
                    std::cout << "Laufen: Ziel ist nicht frei" << std::endl;
                    delete spielBrett;
                    throw UngueltigerZug();
                }
                // Eintragen des Zuges auf das Spielbrett
                spielBrett->brett[start.y][start.x]='0';
                spielBrett->brett[ziel.y][ziel.x]=aktiverSpielerChar;
                spielBrett->ausgabeBrett();

                break;
            }
            case SCHLAGEN:
            {
                int gegnerX = (start.x+ziel.x)/2;
                int gegnerY = (start.y+ziel.y)/2;
                if(spielBrett->brett[ziel.y][ziel.x]!='0')
                {
                    std::cout << "Schlagen: Ziel ist nicht frei" << std::endl;
                    delete spielBrett;
                    throw UngueltigerZug();
                }
                if(spielBrett->brett[gegnerY][gegnerX]!=passiverSpielerChar)
                {
                    std::cout << "Kein Gegner zum Schlagen" << std::endl;
                    delete spielBrett;
                    throw UngueltigerZug();
                }

                spielBrett->brett[start.y][start.x]='0';
                spielBrett->brett[ziel.y][ziel.x]=aktiverSpielerChar;
                spielBrett->brett[gegnerY][gegnerX]='0';

                if(aktiverSpielerChar=='W')
                {// Punktecounter nach dem Schlagen hochzählen
                    spielBrett->geschlageneFigurenB++;
                }
                else
                {
                    spielBrett->geschlageneFigurenW++;
                }

                spielBrett->ausgabeBrett();
            }
    }
    return spielBrett;
}
