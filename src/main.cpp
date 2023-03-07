#include <iostream>
#include <vector>
#include <string>
#include <csignal>

#include "Spielbrett.hpp"

/** Hauptprogramm
 * Menüstruktur und Spielablauf
 */

bool WinCon = false; // wird durch die Eingabe von 'exit' auf true gesetzt

void SpielStart(); // Zentrale Funktion für Ein- und Ausgaben

int main()
{
    SpielStart();
    return 0;
}

/** void Spielstart()
 * \Funktion, verwaltet den Spielablauf
 *
 * @see zug.anwenden
 * @pre Hauptprogramm gestartet
 * @post Spielende
 * @since 10.02.2020
 * @author Franziskus Zillmann
 */
void SpielStart() // organisiert den Spielablauf mit einer Verschachtelung von Schleifen, könnte auch einfach "Spiel" heißen
{
    std::string zugEingabe;
    SpielBrett* spielBrett = new SpielBrett();
    // Hier entsteht ein Pointer Objekt spielBrett der Klasse SpielBrett
    // Vorlesung 14 S. 14: Zeiger spielBrett auf dem Stack, das Objekt kommt auf den Heap
    // Objekt wird erst mit Ende der Laufzeit gelöscht (wichtig, da es als letzte Instanz für das Laden fungiert)

    std::cout << "Willkommen beim Spiel Dame!\n";
    std::cout << "Gewünschte Züge bitte in der Form A3B4 eingeben.\n";
    std::cout << "A3 bezeichnet die Startposition, B4 die Zielposition.\n";
    std::cout << "A3B4 wäre ein gültiger erster Zug für Spieler 1.\n";
    std::cout << "Geben Sie '-' ein, um den letzten Speicherstand zu laden\n";
    std::cout << "Sehen Sie keine Möglichkeit eines gültigen Zuges mehr, geben Sie 'exit' ein um aufzugeben.\n";
    std::cout << "Spieler 1, bitte geben Sie Ihren Namen ein: ";
    std::cin >> spielBrett->spielerNamen[0];
    std::cout << "Spieler 2, bitte geben Sie Ihren Namen ein: ";
    std::cin >> spielBrett->spielerNamen[1];
    spielBrett->ausgabeBrett();
    std::cout << "Geben sie 'exit' ein um aufzugeben.\n";

    /* Debug Testausgabe
    Pos("X5");
    Pos("A9");
    Pos("A3");
    */

    while(!WinCon) // solange die WinCondition (Aufgabe eines Spielers) nicht erfüllt ist, läuft das Spiel in einer Schleife
    {

        do // Verschachtelung von do/while Schleife mit try/catch Schleife
        // ungültige Ausgaben führen zurück zur Eingabe des Zuges
        {
            std::cout << spielBrett->spielerNamen[(spielBrett->zugZahl+1)%2] << " bitte wählen Sie Ihren Zug " << (spielBrett->zugZahl+1)/2 << ": ";
            std::cin >> zugEingabe;
            // Aufgeben
            if(zugEingabe=="exit")
            {
                WinCon=true;
                std::cout << spielBrett->spielerNamen[(spielBrett->zugZahl+1)%2] << ", Sie haben aufgegeben.\n";
                std::cout << spielBrett->spielerNamen[(spielBrett->zugZahl)%2] << ", Sie haben gewonnen.\n";
                break;
            }

            // Laden des vorherigen Zuges
            if(zugEingabe=="-")
            {
                spielBrett=const_cast<SpielBrett*>(&(spielBrett->vorgaenger));
                /*
                 Bei der Eingabe von '-' wird das Spielbrett auf seinen Vorgänger zurückgesetzt.

                 Dafür wird ein neues Spielbrett mit dem copy constructor angelegt, welches den Vorgänger des aktuellen Spielbretts als Argument bekommt
                 Der Copy Constructor kopiert nur konstante Typen, was  die hier verwendeten Spielbrett-Pointer-Objekte nicht sind
                 Deswegen wird das Objekt mit const_cast weitergegeben.

                 "const_cast makes it possible to form a reference or pointer to non-const type that is actually referring
                 to a const object or a reference or pointer to non-volatile type that is actually referring to a volatile object."

                 * = Pointer declaration
                 &(...) = 'adress of' zu der Memory Adresse des Vorgängers des aktuellen Spielbretts zeigt.
                 <...> = Es wird ein Spielbrett-Pointer-Typ verwendet

                 */
                std::cout << "Der letzte Speicherstand wurde geladen.\n";
                spielBrett->ausgabeBrett(); // Das vorige Brett wird ausgegeben -> erneute Eingabe
            }
            else
            {
                try // Versuch der Implementierung der try/catch Fehlerbehebung
                {
                    Zug zug = Zug(zugEingabe);
                    //zug.print(); // Debug Testausgabe
                    SpielBrett* neuesSpielBrett = zug.anwenden(*spielBrett); // Das neue Spielbrett ist das vorige plus Zuganwendung
                    spielBrett = neuesSpielBrett; // Von jetzt an wird mit dem jeweils nächsten Brett gespielt
                    //std::cout << erfolg; // Debug Testausgabe
                    //std::cout << "Zuglog = " << &zug.zugLog << std::endl; // Debug Testausgabe
                }
                catch(int posFehler) //int pos Fehler kommt aus der Klasse Position
                {
                    std::cout << "Ungültige Position\n";
                    std::cout << "Bitte geben Sie die Koordinaten (A1-H8) einer Ihnen gehörenden Figuren ein\n";
                }
                catch(UngueltigerZug)
                {
                    std::cout << "Ungueltiger Zug\n";
                }
            }
        } while(true);
    };
}
