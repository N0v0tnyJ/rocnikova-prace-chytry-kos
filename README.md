# rocnikova-prace-chytry-kos
Cílem práce je navrhnout a sestrojit funkční automatizovaný odpadkový koš na bázi mikrokontroléru Arduino UNO. Koš bezdotykově detekuje přiblížení ruky uživatele pomocí ultrazvukového senzoru a automaticky otevírá víko prostřednictvím servomotoru, čímž zvyšuje hygienický standard při vyhazování odpadků. Zařízení dále nabízí manuální režim ovládání (trvalé otevření/zavření) a přehlednou světelnou i zvukovou signalizaci aktuálního stavu.

Použitý hardware a komponenty
Řídicí jednotka: Arduino UNO R3 (případně Arduino Nano)

Senzor přiblížení: Ultrazvukový modul HC-SR04

Pohon víka: Micro servomotor SG90 (9g)

Ovládání: Mikrospínací tlačítko (manuální režim)

Stavová indikace: Zelená a červená LED dioda (s rezistory 220–330 Ω), piezo bzučák

Ostatní: Nepájivé pole (breadboard), DuPont propojovací kabely, konstrukce koše

Hlavní funkce
Automatický režim: Bezdotyková detekce přiblížení na nastavenou vzdálenost a plynulé otevření/zavření víka.

Manuální režim: Přepnutí do trvale otevřeného nebo zavřeného stavu pomocí fyzického tlačítka.

Stavová signalizace: Vizuální (LED) a akustická (bzučák) zpětná vazba při změně stavu nebo otevření víka.

Postup realizace
Fáze 1 – Virtuální prototyp (Wokwi): Návrh zapojení a testování jednotlivých modulů (ultrazvukový senzor, servomotor, indikace, tlačítko) v online simulátoru.

Fáze 2 – Fyzický prototyp: Zapojení reálných komponent na nepájivém poli a odladění mechaniky víka.

Fáze 3 – Konstrukce a dokumentace: Zabudování elektroniky do modelu koše a vypracování technické zprávy k obhajobě.
