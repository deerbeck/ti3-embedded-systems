<!--- Technische Informatik (FK04)"
Author: Benjamin Kormann			Date: <2022 Feb 03> 
Changes by:
<NAME> - <JJJJ MMM DD> - <comment> 

--->
<img style="float:right" src="images/hm-logo.png" height="100">  

**TI3-Embedded Systems: Versuch 02**

2023 Sommersemester | V 1.4 | Prof. Dr. Benjamin Kormann

***
# Zielsetzung: Farb-Bitmap-Bild zu Graustufen-Bitmap-Bild konvertieren

Das Ziel des Praktikums ist es, ein Programm zu schreiben, das aus einem Farb-Bitmap-Bild ein Graustufen-Bitmap-Bild erzeugt.

<p float="left">
  <img src="images/HM_cube_rgb.png" width="300" />
  <img src="images/HM_cube_gray.png" width="300" /> 
</p>

## Allgemeine Hinweise

Bevor Sie mit der Bearbeitung dieses Versuchs starten lesen Sie bitte die allgemeinen Hinweise auf der ersten Seite genau durch.

### Informationen zum Präsenzpraktikum

Sie haben Ihre eigenen Rechner mit der virtuellen Maschine eingerichtet, um Beispiele aus der Vorlesung auch zu Hause entwickeln können. Außerdem gibt Ihnen dieses Setup die Möglichkeit, mit der Bearbeitung der Praktikumsaufgaben bereits auf dem eigenen Rechner (virtuelle Maschine) zu beginnen. 

#### Vorbereitungen zu Hause

Es ist erforderlich, dass Sie den letzten Stand Ihrer Praktikumsaufgaben auch in GitLab hochgeladen haben. Stellen Sie dies nochmals sicher, indem Sie auf Ihrem privaten Rechner im Git Repository mit

```
git push
```

den aktuellen Stand ins GitLab übertragen. 

#### Vorbereitungen im Labor

Die Praktikumsaufgaben werden je nach Gruppeneinteilung in den Laboren E303 und E308 durchgeführt. Dazu werden Raspberry Pis eingesetzt. 

##### Besonderheiten im Labor E303

Suchen Sie sich einen Arbeitsplatz aus. An jedem Arbeitsplatz ist ein Raspberry Pi angeschlossen und per Netzwerk verfügbar. Eventuell müssen Sie die Stromversorgung noch am Raspberry Pi anschließen. Starten Sie den Desktop Rechner an Ihrem Arbeitsplatz und melden Sie sich unter Windows mit folgender Kennung an:

```
Benutzername: pi01
Passwort: raspi
```

Es handelt sich bei dieser Kennung um eine Praktikumskennung. Es sind auch noch weitere Kennungen pi01, pi02, ..., pi20 verfügbar. Nutzen Sie am besten die Kennung, die zu Ihrer Sitzplatznummer passt. Legen Sie demnach keine persönlichen Dokument unter diesem Account ab, sondern nutzen Sie diesen ausschließlich zur Bearbeitung der Praktikumsaufgabe.

Nach der Anmeldung können Sie sich mit dem Windows Programm VNCViewer mit dem Raspberry Pi verbinden. Starten Sie dazu den VNCViewer und tippen Sie die IP-Adresse des Raspberry Pis ein. Die IP-Adresse steht auf dem Gehäuse des Raspberry Pis. Nachdem die Verbindung zum Raspberry Pi hergestellt wurde melden Sie sich mit

```
Benutzername: pi
Passwort: rpiXX
```

an. Beim Passwort entspricht das XX der Nummer des Raspberry Pis (bspw. 36). Die Benutzername/Passwort Kombination ist sowohl für VNC als auch für die Anmeldung am Raspberry Pi erforderlich. Sie sind nun auf dem Raspberry angemeldet und können darin arbeiten wie in Ihrer eigenen virtuellen Maschine. 

##### Besonderheiten im Labor E308

Suchen Sie sich einen Arbeitsplatz aus. In dem Labor sind die Raspberry Pis an einem zentralen Ort verfügbar. Es ist nicht erforderlich, dass Sie sich einen Raspberry Pi direkt an den Arbeitsplatz stellen.

Starten Sie den Desktop Rechner an Ihrem Arbeitsplatz und melden Sie sich unter Windows mit folgender Kennung an:

```
Benutzername: pi
Passwort: raspi
```

Nach der Anmeldung können Sie sich mit dem Windows Programm VNCViewer mit einem Raspberry Pi verbinden. Bevor Sie sich mit einem Raspberry Pi verbinden, lassen Sie sich von dem Praktikumsbetreuer einen Raspberry Pi zuweisen. Sie erhalten einen Namen (bspw. `lmc-rpi36`) sowie eine zugehörige IP-Adresse (bspw. `172.22.206.75`). Starten Sie nun den VNCViewer und tippen Sie die IP-Adresse des Raspberry Pis ein. Nachdem die Verbindung zum Raspberry Pi hergestellt wurde melden Sie sich mit

```
Benutzername: pi
Passwort: rpiXX 
```

an. Beim Passwort entspricht das XX der Nummer des Raspberry Pis (bspw. 36). Die Benutzername/Passwort Kombination ist sowohl für VNC als auch für die Anmeldung am Raspberry Pi erforderlich. Sie sind nun auf dem Raspberry angemeldet und können darin arbeiten wie in Ihrer eigenen virtuellen Maschine. 

#### Umgebung zur Bearbeitung einrichten

Unabhängig vom Labor sind Sie nun erfolgreich auf einem Raspberry Pi angemeldet. Nun müssen Sie Ihre Quellen aus GitLab auf den Raspberry Pi laden. Dazu müssen sowohl die ssh Authentifizierung sowie die Git Konfiguration ausgeführt werden. Starten Sie das Terminal in der Symbolleiste und führen Sie die folgenden Kommandos aus:

```
cd
rm -rf .ssh
ssh-keygen -t rsa -b 2048
cat .ssh/id_rsa.pub
```

Kopieren Sie nun den öffentlichen Schlüssel in Ihr GitLab Profil. Dazu loggen Sie sich im Browser in https://gitlab.lrz.de mit Ihren Zugangsdaten ein und fügen den SSH Key hinzu. Diese Konfiguration haben Sie auch bereits auf Ihrem eigenen Rechner einmal durchgeführt.

Grundsätzlich können Sie nun bereits mit Git und GitLab arbeiten. Da die Raspberry Pis nicht personalisiert sind müssen Sie den Benutzernamen noch konfigurieren, sonst erscheint in den `commit` Nachrichten ein fremder Name. Dazu führen Sie im Terminal die folgenden Kommandos aus:

```
git config --global user.name "John Doe"
git config --global user.email jd@example.com
```

Anstatt John Doe verwenden Sie natürlich Ihren Namen und ebenso setzen Sie bei jd@example.com Ihre E-Mail Adresse ein. Nun können Sie den aktuellen Stand aus GitLab laden:

```
git clone git@......
```

Selbstverständlich müssen Sie sich nun die richtige `clone`-Adresse aus Ihrem GitLab Projekt kopieren und in das oben angegebene Kommando einsetzen.


### Verwendung von CI/CD

Für die Bearbeitung des Praktikumsversuchs wird Ihnen neben der Versionsverwaltung Git die sog. Continuous Integration (CI) Funktionalität von GitLab zur Verfügung gestellt. Diese bewirkt, dass Sie ihren entwickelten Softwarestand in Ihr eigenes Repository in GitLab pushen können und anschließend werden automatisiert Tests auf Ihren Quelltext ausgeführt. Darüber haben Sie die Möglichkeit, selbst festzustellen, ob Ihre Implementierung noch grundlegende Fehler enthält. Wichtig dabei zu wissen ist, dass erfolgreiche Tests noch keine Garantie dafür sind, dass Ihr Programm am Ende keine Fehler enthält. Aber es werden grundsätzliche Aspekte geprüft. Hierzu wird empfohlen, dass Sie in dem PDF-Dokument *Einführung in das Versionsverwaltungssystem Git und das LRZ GitLab* die Abschnitte 3.4.2 vollständig lesen.

### Abgabe des Versuchs

Jeder Praktikumsteilnehmer muss den eigenen Versuch beim jeweiligen Praktikumsbetreuer vorstellen und Fragen zu der Lösung beantworten. Dabei ist es auch wichtig, dass *Ihre eigene Lösung in Ihrem eigenen Git Repository in GitLab* (`git push`) vorhanden ist.

### Abnahmekriterien

Bei der Abgabe werden die Praktikumsbetreuer nicht nur auf die Funktionalität, sprich das zu erreichende Ergebnis achten. Die erfolgreiche Abgabe unterliegt den folgenden Kriterien:
1. **Aufgabenstellung** ist funktional **erfüllt**
2. Die **Testfälle** laufen alle **erfolgreich** durch
3. **Fragen** zur Lösung und zu Konzepten in C **müssen beantwortet werden**
4. Sie haben ausreichend (mehr als 4) **commit Nachrichten** in Git erstellt
5. Der Quelltext besitzt einen **Dokumentationsgrad** von **mindestens 25 %** (Der Dokumentationsgrad bestimmt sich aus der Anzahl der Kommentarzeilen im Quelltext (Zeilen mit //) im Verhältnis zu der Gesamtanzahl Zeilen Quelltext.)

Die Punkte 4) und 5) werden automatisiert ermittelt. Bei dem Gespräch mit dem Praktikumsbetreuer stellen Sie neben Ihrer eigenen Lösung auch die Punkte 4) und 5) eigenständig mit vor.

Mit Hilfe der CI/CD Lösung von GitLab werden mit jedem `git push` automatisch die Testfälle ausgeführt und der Dokumentationsgrad aller .h- und .c-Dateien ermittelt. Zum Abrufen der Ergebnisse der ausgeführten Testfälle gehen Sie wie vor im **Abschnitt 3.4.2.2** im Einführungsdokument zu Git beschrieben. Für die Bewertung des Dokumentationsgrads wird das Tool `cloc` (Sie müssen dieses Tool nicht installieren. Es ist in GitLab hinterlegt. Quelle: https://github.com/AlDanial/cloc) verwendet, welches das Ergebnis als Artefakt der CI/CD-Pipeline zur Verfügung stellt. Lesen Sie dazu auch den **Abschnitt 3.4.2.3** im Einführungsdokument zu Git. Die folgende Beispielausgabe zeigt *einen zu geringen Gesamtdokumentationsgrad von 15,62 %*.

```
3 text files.
classified 3 files
       3 unique files.                              
       0 files ignored.

github.com/AlDanial/cloc v 1.81  T=0.02 s (165.0 files/s, 8798.4 lines/s)
-------------------------------------------------------------------------------
Language                     files        blank %      comment %           code
-------------------------------------------------------------------------------
C                                2          18.30          16.34            100
C/C++ Header                     1          14.29           0.00              6
-------------------------------------------------------------------------------
SUM:                             3          18.12          15.62            106
-------------------------------------------------------------------------------
```


# Aufgabenstellung

Die Funktion `saveBmpGray()` aus dem ersten Praktikum ist bekannt und steht auch diesmal wieder zur Verfügung. Die aus dem ersten Versuch von Ihnen implementierten Funktionen `genBackgroundImage()` und `drawCircles()` kopieren Sie aus der `ti_bmp.c` Datei aus dem Verzeichnis des ersten Versuchs in die Datei `ti_bmp.c` des zweiten Versuchs. **Überschreiben Sie nicht die gesamte Datei, sondern kopieren Sie nur den Quelltext der Implementierung der beiden Funktionen. Bearbeiten Sie alle im Quelltext hinterlegten TODO Kommentare.**


**Hinweise zu den Unit Tests in der GitLab Pipeline**

In dem zweiten Versuch werden die vier Unit Tests aus dem ersten Versuch wieder mit übernommen. Denn jede Erweiterung des Quelltextes soll keine Auswirkung auf die bereits realisierte Funktionalität aus Versuch 1 haben.
Mit Versuch 2 sind elf weitere Unit Tests hinzugekommen. Sie können nach jeder Aufgabe die erfolgreiche Ausführung der Unit Tests überprüfen und ggf. Ihre Implementierung anpassen. Die neuen Unit Tests lauten wie folgt:


| Unit Test                        | Aufgabe  | Überprüfung  |
|:---------------------------------|:---------|:----------|
| v2_aufg1_existBMPpositive        | 1        | Prüft den richtigen Rückgabewert bei vorhandener Datei    |
| v2_aufg1_existBMPnegative        | 1        | Prüft den richtigen Rückgabewert bei nicht vorhandener Datei    |
| v2_aufg2_getBMPWidthpositive     | 2        | Prüft den richtigen Rückgabewert bei 3 Beispieldateien    |
| v2_aufg2_getBMPWidthnegative     | 2        | Prüft den richtigen Rückgabewert bei nicht vorhandener Datei    |
| v2_aufg2_getBMPHeightpositive    | 2        | Prüft den richtigen Rückgabewert bei 3 Beispieldateien    |
| v2_aufg2_getBMPHeightnegative    | 2        | Prüft den richtigen Rückgabewert bei nicht vorhandener Datei    |
| v2_aufg2_getBMPDataSizepositive  | 2        | Prüft den richtigen Rückgabewert bei 3 Beispieldateien    |
| v2_aufg2_getBMPDataSizenegative  | 2        | Prüft den richtigen Rückgabewert bei nicht vorhandener Datei    |
| v2_aufg3_getBMPDatapositive      | 3        | Prüft den richtigen Rückgabewert bei 3 Beispieldateien    |
| v2_aufg3_getBMPDatanegative      | 3        | Prüft den richtigen Rückgabewert bei nicht vorhandener Datei   |
| v2_aufg4_convertRgb2Gray         | 4        | Prüft, ob die richtige Konvertierungsregel implementiert wurde    |


## Aufgabe 1: Implementieren von existBmp()

Das Hauptprogramm verwendet die Hilfsfunktion `existBmp()`, die das Vorhandensein der Bitmap-Datei überprüft, indem sie die Datei öffnet und wieder schließt. Nutzen Sie die Datei `HM_cube.bmp`.

Weitere Hilfsfunktionen sollen immer in sich abgeschlossen sein. Das bedeutet, dass die Hilfsfunktion immer die Datei öffnen und schließen muss und nicht mit einer bereits im Vorfeld geöffneten Datei arbeitet oder eine geöffnete Datei zurückgibt.

*Hinweis*: Die Hilfsfunktion `existBmp()` eignet sich sehr gut als Vorlage für weitere Hilfsfunktionen.

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Sie können nun die CI/CD Funktionalität zum automatisierten Test verwenden. Pushen Sie den aktuellen Stand in GitLab und betrachten Sie die Ergebnisse der Unit Tests in GitLab. Diese sollten grün (erfolgreich) sein.


## Aufgabe 2: Implementieren von drei Hilfsfunktionen

Bevor Sie mit der Bearbeitung der zweiten Aufgabe beginnen müssen Sie sich mit dem BMP Bildformat vertraut machen. Es gibt zahlreiche Formate zur Codierung von Bildern. Das BMP Format zählt zu den ältersten und einfachsten Formaten, da es ohne Komprimierung auskommt. Für die Verarbeitung des BMP Formats müssen Sie die Spezifikation verstehen. Machen Sie sich deshalb mit den Beschreibungen auf den folgenden Seiten vertraut:
- THE BMP FILE FORMAT: https://sites.ualberta.ca/~delliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm
- Windows Bitmap: https://de.wikipedia.org/wiki/Windows_Bitmap

Im Folgenden sollen die drei ersten Hilfsfunktionen erstellt werden:
```
int32_t getBmpWidth(char* filename);
int32_t getBmpHeight(char* filename);
uint32_t getBmpDataSize(char* filename);
```

Dabei soll `getBmpWidth()` die Breite des Bildes, `getBmpHeight()` die Höhe des Bildes und `getBmpDataSize()` die Größe des Datenblocks für die Pixeldaten zurückgeben.

Dafür müssen aus dem Header der Bitmap-Datei diese Informationen ausgelesen werden. Schauen Sie in der Header-Beschreibung nach, an welcher Position der Bitmap-Datei sich die jeweilige Information befindet und welcher Datentyp es ist.

Nutzen Sie `fseek()` und `fread()`, um die Informationen auszulesen.

Verwenden Sie die Hilfsfunktionen in der `main()`-Funktion und geben Sie die drei Werte aus.

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Sie können nun die CI/CD Funktionalität zum automatisierten Test verwenden. Pushen Sie den aktuellen Stand in GitLab und betrachten Sie die Ergebnisse der Unit Tests in GitLab. Diese sollten grün (erfolgreich) sein.


## Aufgabe 3: Implementieren von getBmpData()

Die nächste erforderliche Hilfsfunktion ist:
```
uint8_t getBMPData(char* filename, uint8_t* data);
```
Lesen Sie in der Quelltextdokumentation der Funktion in der Datei `ti_bmp.h` die Spezifikation der Rückgabewerte und berücksichtigen Sie dies bei der Implementierung. Die Funktion liest den Datenblock der Pixel aus. Dabei ist zu beachten, dass der Datenblock nicht unmittelbar nach dem Header in der Bitmap-Datei beginnt. An welcher Position in der Datei der Datenblock beginnt, ist im Header an der Stelle `bfOffBits` hinterlegt.

Beachten Sie, dass für den Übergabeparameter data ein entsprechend großer Array in der `main()`-Funktion angelegt werden muss (call-by-reference!).

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Sie können nun die CI/CD Funktionalität zum automatisierten Test verwenden. Pushen Sie den aktuellen Stand in GitLab und betrachten Sie die Ergebnisse der Unit Tests in GitLab. Diese sollten grün (erfolgreich) sein.



## Aufgabe 4: Implementieren der Bilddatenkonvertierung

Die nächste erforderliche Hilfsfunktion ist:
```
uint8_t* convertRgb2Gray(uint8_t* image, int datasize);
```

Diese Funktion nimmt ein Farbbild als Parameter `image` entgegen und soll daraus ein Graustufenbild der Größe `datasize` erzeugen. Dazu muss die Funktion den erforderlichen Speicherbereich mit `malloc()` selbst reservieren und das dynamisch erzeugte Bild als Rückgabewert der Funktion zurückliefern. Der Parameter `datasize` beschreibt die Größe des Graustufenbildes und entspricht somit der Anzahl der Pixel.

Für die Konvertierung eines Farbbildes in ein Graustufenbild muss aus den RGB-Kanälen des Farbbildes ein Graustufenwert ermittelt werden. Dazu ist folgende Berechnungsvorschrift umzusetzen:
```
gray = 0.299 * red + 0.587 * green + 0.114 * blue
```
Rufen Sie in der `main()`-Funktion die Konvertierung des Farbbildes auf und speichern Sie das so erzeugte Graustufenbild mit der Funktion `saveBmpGray()` ab.

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Sie können nun die CI/CD Funktionalität zum automatisierten Test verwenden. Pushen Sie den aktuellen Stand in GitLab und betrachten Sie die Ergebnisse der Unit Tests in GitLab. Diese sollten grün (erfolgreich) sein.


## Aufgabe 5: Anpassen des Dateinamens

Der Dateiname der Farb-Bitmap-Datei soll bei Programmaufruf als Kommandozeilenparameter übergeben werden (`int main(int argc, char* argv[]`). Wenn keine Datei angegeben wird, soll eine Fehlermeldung ausgegeben werden. 

Wenn die Datei vorhanden ist, wird das Graustufen-Bitmap-Bild erzeugt, wobei der ursprüngliche Dateiname um die Endung `_gray` ergänzt wird.

*Beispiel:*
```
Aus cat.bmp wird cat_gray.bmp
Aus dog.bmp wird dog_gray.bmp
```
Es gibt viele Möglichkeiten, den neuen Dateinamen aus dem ursprünglichen Namen zu erzeugen. Die Standardbibliothek der Programmiersprache C bietet hilfreiche Funktionen zur String-Bearbeitung an, z.B. `strlen, strcat, strchr, strcpy, ...`
Recherchieren Sie dazu in der Dokumentation (bspw. https://www.cppreference.com).

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Übertragen Sie jetzt final alle Änderungen auch in GitLab (push).

# ACHTUNG: Nicht vergessen

Der im Praktikum verwendete Raspberry Pi ist nicht personalisiert, d.h. wenn Sie nun das Labor verlassen kann jemand mit dem von Ihnen eingesetzten Raspberry Pi auf Ihr komplettes GitLab zugreifen, da Sie eine SSH Authentifizierung eingerichtet haben. Löschen Sie deshalb nun den privaten Schlüssel auf dem Raspberry Pi, indem Sie im Terminal die folgenden Kommandos eingeben:

```
cd
rm -rf .ssh
```

Löschen Sie ebenfalls das geklonte Verzeichnis. Normalerweise sollte dies ti3-es heißen und Sie können es im Terminal mit:

```
cd
rm -rf ti3-es
```

löschen. 

## Besonderheit im Labor E303

Nun können Sie den Raspberry Pi **herunterfahren und ausschalten**. **Ziehen** Sie auch die **Stromversorgung** vom Raspberry Pi **ab**.

## Besonderheit im Labor E308

Sie können sich nun vom Raspberry Pi abmelden. **Bitte nicht herunterfahren**.