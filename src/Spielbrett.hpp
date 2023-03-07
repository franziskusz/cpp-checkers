
/**
 * Deklarationen der Klassen Spielbrett, Position und Zug
 * Interface für das Hauptprogramm
 */

#ifndef Spielbrett_hpp
#define Spielbrett_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <array>

/** Klasse Spielbrett
 * \brief Klasse, welche den Aufbau des Spielbrettes und zentrale Informationen darüber verwaltet
 * Erstellt die Objekte der Klasse Spielbrett
 * Hat einen Default (Spielstart) und einen Copy Konstruktor (für die Speicherfunktion)
 */
class SpielBrett
{
    public: // Positionen der schwarzen und weißen Felder
        const SpielBrett& vorgaenger; //Referenz auf das Vorgängerobjekt
        std::string spielerNamen[2];
        int zugZahl = 1;   // Zähler für die Züge evtl Modulo um SpielerZug zu bestimmen
        int geschlageneFigurenB; // Zähler für die geschlagenen Figuren von B
        int geschlageneFigurenW; // Zähler für die geschlagenen Figuren von W
        std::array<std::array<char, 8>, 8> brett;// 8x8 Matrix als Spielfeld

        SpielBrett(); //Start Konstruktor
        SpielBrett(const SpielBrett& spielBrett); // copy constructur für Neue Züge und Laden des vorherigen Zuges

        /** void initBrett()
         * \Funktion, initialisiert das Array Brett
         * @see ausgabeBrett
         * @pre Es muss eine Instanz der Klasse SpielBrett geben
         * @post initialisiertes Spielfeld
         * @since 08.02.2020
         * @author Franziskus Zillmann
         */
        void initBrett(); // Initialisierung des Brettes
            int x;
            int y;

        /** void ausgabeBrett()
         * \Funktion, welche das zuvor initialisierte Array um ein User Interface erweitert und es ausgibt
         * @see initBrett
         * @pre das Brett muss initalisiert sein
         * @post grafische Ausgabe des Spielfeldes
         * @since 08.02.2020
         * @author Franziskus Zillmann
         */
        void ausgabeBrett(); // Deklaration der Ausgabe Funktion
};

/** Klasse Pos
 * \brief prüft ob die eingegebenen Positionen gültig sind
 *
 * Verantwortlich für Fehlerausgaben die die gewählten Positionen
 *
 */
class Pos
{ // Deklaration der Struktur für die Positionen der Figuren
    public:
        Pos(std::string s); //Konstruktor
        void print(); // Testausgabe
        int x;
        int y;
};

enum ZugTyp {LAUFEN,SCHLAGEN}; // Zugtypen

/** Klasse Ungültiger Zug
 * \brief Fehlerklasse
 *
 * Verantwortlich für Fehlerausgaben der Zuganwendungen
 *
 */
class UngueltigerZug {};


/** Klasse Zug
 * \brief prüft, ob die Zugkoordinaten gültige Züge ergeben
 * Unterscheidet anhand der Eingaben zwischen den Zugtypen Laufen und Schlagen
 * Wendet anschließend die Funktion Zug::anwenden an
 *
 */
class Zug
{ // Deklaration der Klasse Zug

     public:
         Pos start,ziel;
         char spielerChar[2];
         char aktiverSpielerChar;
         char passiverSpielerChar;
         ZugTyp typ;

         Zug(std::string s); //Konstruktor

         void print(); // debug

        /** SpielBrett* anwenden()
         * \Funktion, welche den Zug auf das SpielBrett anwendet und
         *
         * @param SpielBrett& Referenz auf das Objekt der Klasse SpielBrett
         * @see initBrett
         * @return Pointer auf das aktuelleste Spielbrett-Objekt
         * @pre Zug muss möglich sein
         * @post Zug ist angewandt, altes Spielbrett = Vorgänger, auf neuem Spielbrett wird gespielt
         * @since 17.02.2020
         * @author Franziskus Zillmann
         */
         SpielBrett* anwenden(SpielBrett&); //Deklaration der Zug anwenden Funktion
};

#endif /* Spielbrett_hpp */
