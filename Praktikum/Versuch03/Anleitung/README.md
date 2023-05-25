<!--- Technische Informatik (FK04)"
Author: Benjamin Kormann			Date: <2022 Feb 03> 
Changes by:
<NAME> - <JJJJ MMM DD> - <comment> 

--->
<img style="float:right" src="images/hm-logo.png" height="100">  

**TI3-Embedded Systems: Versuch 03**

2023 Sommersemester | V 1.4 | Prof. Dr. Benjamin Kormann

***
# Zielsetzung: Digitale Bildverarbeitung - Filter

In der digitalen Bildverarbeitung ist eine wichtige Operation die Anwendung von Filter auf das digitale Bild. So gibt es Filter zum Weichzeichnen, Schärfen, Kantenhervorhebung und viele mehr. Ziel dieses Praktikums ist es, unterschiedliche Filter auf Graustufenbilder anzuwenden.

<p float="left">
  <img src="images/HM_cube_gray.png" width="300" />
  <img src="images/HM_cube_edge.png" width="300" /> 
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

Viele Filter basieren auf der diskreten 2-dimensionalen Faltung (engl. Convolution) (Erinnerung an Signale und Systeme). Bei dieser Faltung wird ein sog. Kernel über das Bild verschoben und mit den Pixeln verrechnet. Eine typische Filtermatrix zum Weichzeichnen ist die 3x3 Matrix

$`\frac{1}{9} \begin{bmatrix}1 & 1 & 1\\
1 & 1 & 1\\
1 & 1 & 1
\end{bmatrix}`$

und zum Schärfen die 3x3 Matrix

$`\begin{bmatrix}0 & -1 & 0\\
-1 & 5 & -1\\
0 & -1 & 0
\end{bmatrix}`$

Die Rechenvorschrift ist nicht die klassische Matrixmultiplikation, sondern eine elementweise Multiplikation (Hadamard-Produkt) mit anschließender Summation der Elemente (siehe Zahlenbeispiel).

Für die Berechnung eines Pixels im neuen Bild wird somit die Umgebung um diesen Pixel im Ausgangsbild benötigt. Die Problematik der Randpixel wird an der Stelle vermieden, indem diese Pixel im neuen Bild auf 0 gesetzt werden.

Falls der berechnete Pixelwert kleiner als 0 ist, wird der Wert auf 0 gesetzt. Falls er größer als 255 ist, wird es auf 255 gesetzt.

**Zahlenbeispiel:** 

Ausgangsbild mit Breite 12 und Höhe 4:
```
 180   185   190   195   200   205   210   215   220   225   230   235  
 120   125   130   135   140   145   150   155   160   165   170   175  
  60    65    70    75    80    85    90    95   100   105   110   115  
   0     5    10    15    20    25    30    35    40    45    50    55  
```

Mit dem 3x3 Kernel:
```
  0.8  -0.7  0.6   
 -0.5   0.4  0.3   
  0.2  -0.1  0.0  
```

Ergebnis:
```
  0     0     0     0     0     0     0     0     0     0     0     0  
  0   163   168   173   178   183   188   193   198   203   208     0  
  0   103   108   113   118   123   128   133   138   143   148     0  
  0     0     0     0     0     0     0     0     0     0     0     0  
```

Die Berechnung für einen Pixel lautet somit:

```
0.8*180 - 0.7*185 + 0.6*190 - 0.5*120 + 0.4*125 + 0.3*130 + 0.2*60 - 0.1*65 + 0.0*70 = 163
```

**Allgemeines:**

Die Dateien `ti_bmp.h` und `ti_bmp.c` sollen erweitert werden, die dann wiederum in der `main()`-Funktion genutzt werden. Die Funktionen `getBmpWidth()`, `getBmpHeight()`, `getBmpDataSize()`, `getBmpData()` aus dem letzten Praktikum werden benötigt.
Die Funktion `saveBmpGray()` aus dem ersten Praktikum ist bekannt und steht auch diesmal wieder zur Verfügung. Die aus den bisherigen Versuchen von Ihnen implementierten Funktionen kopieren Sie aus der `ti_bmp.c` Datei aus dem Verzeichnis des letzten Versuchs in die Datei `ti_bmp.c` des dritten Versuchs. **Überschreiben Sie nicht die gesamte Datei, sondern kopieren Sie nur den Quelltext der Implementierung der beiden Funktionen. Bearbeiten Sie alle im Quelltext hinterlegten TODO Kommentare.**


**Hinweise zu den Unit Tests in der GitLab Pipeline**

In dem dritten Versuch werden die Unit Tests aus den ersten beiden Versuchen wieder mit übernommen. Denn jede Erweiterung des Quelltextes soll keine Auswirkung auf die bereits realisierte Funktionalität aus Versuch 1 und Versuch 2 haben.
Mit Versuch 3 werden zwei weitere Unit Tests hinzukommen. Sie können nach Umsetzung der Aufgabe 3 die erfolgreiche Ausführung der Unit Tests überprüfen und ggf. Ihre Implementierung anpassen. Die neuen Unit Tests lauten wie folgt:



| Unit Test                        | Aufgabe  | Überprüfung  |
|:---------------------------------|:---------|:----------|
| v3_aufg3_conv2Dpositive        | 3        | Prüft die richtige Anwendung der Convolution    |
| v3_aufg3_conv2Dborder        | 3        | Prüft die richtige Umsetzung der Randbehandlung der Convolution    |



## Aufgabe 1: Definition von Strukturen

Erweitern Sie die `ti_bmp.h` um zwei Strukturen. Die erste Struktur `Kernel` ist zum Speichern der Kernelinformationen gedacht. Sie beinhaltet den Kernelnamen `char name[32]` und die Werte der 3x3 Filtermatrix `float values[9]`. Die zweite Struktur `Image` ist zum Verwalten der Bitmap-Informationen gedacht. Sie beinhaltet die Breite `int32_t width`, die Höhe `int32_t height`, die Größe der Bilddaten `uint32_t datasize` und einen Zeiger auf die Bilddaten `uint8_t* data`.

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Sie können nun die CI/CD Funktionalität zum automatisierten Test verwenden. Pushen Sie den aktuellen Stand in GitLab und betrachten Sie die Ergebnisse der Unit Tests in GitLab. Alle bisherigen Unit Tests (Versuch 1 und Versuch 2) sollten erfolgreich sein.



## Aufgabe 2: Ausgabefunktion

Erstellen Sie die Funktion
```
void printfBmp(Image* img);
```

Die Funktion soll die Bilddaten formatiert ausgeben. Für größere Bilder ist das nicht sinnvoll, jedoch zur Überprüfung und zur Fehlersuche bei der Faltung ist eine Pixelausgabe sehr hilfreich.

Lassen Sie das Testbild `test.bmp` mit der Hilfsfunktion ausgeben. Die Ausgabe sollte sein:

```
Width: 12  Height: 4 
180     185     190     195     200     205     210     215     220     225     230     235
120     125     130     135     140     145     150     155     160     165     170     175
60      65      70      75      80      85      90      95      100     105     110     115
0       5       10      15      20      25      30      35      40      45      50      55
```

*Anmerkung*: der Ursprung dieser Bitmap-Datei ist links unten. Die Bilddaten beginnen mit der 0 und erhöhen sich um 5 bis zur 235.

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Sie können nun die CI/CD Funktionalität zum automatisierten Test verwenden. Pushen Sie den aktuellen Stand in GitLab und betrachten Sie die Ergebnisse der Unit Tests in GitLab. Alle bisherigen Unit Tests (Versuch 1 und Versuch 2) sollten erfolgreich sein.



## Aufgabe 3: Convolution Funktion

Erstellen Sie die Funktion
```
void conv2D(Image* src, Image* dst, Kernel* krnl);
```
Die Funktion führt die diskrete Faltung des Eingangsbildes `src` mit dem Kernel `krnl` durch und liefert das Ergebnisbild `dst` zurück.

Testen Sie die Funktion mit dem Testbild `test.bmp` und dem folgenden Dummy-Kernel 

```
  0.8  -0.7  0.6   
 -0.5   0.4  0.3   
  0.2  -0.1  0.0  
```

Die Ausgabe des Ergebnisbildes sollte sein:

```
Width: 12  Height: 4 
0       0       0       0       0       0       0       0       0       0       0       0
0       163     168     173     178     183     188     193     198     203     208     0
0       103     108     113     118     123     128     133     138     143     148     0
0       0       0       0       0       0       0       0       0       0       0       0
```

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Sie können nun die CI/CD Funktionalität zum automatisierten Test verwenden. Pushen Sie den aktuellen Stand in GitLab und betrachten Sie die Ergebnisse der Unit Tests in GitLab. Diese sollten nun alle grün (erfolgreich) sein.


## Aufgabe 4: Kernel einlesen

In der Textdatei `kernels.txt` sind mehrere Kernel mit Namen und Werten angegeben. Lesen Sie Textdatei ein und speichern Sie die Kernel in einem Array mit Hilfe der Struktur Kernel ab.

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Pushen Sie den aktuellen Stand in GitLab. Hier gibt es keine Unit Tests.


## Aufgabe 5: Anwenden der Kernel

Wenden Sie die einzelnen Kernel aus Aufgabe 4 auf Graustufenbilder an. Zur Verfügung stehen die Bilder `HM_cube_gray.bmp` und `HM_admin_gray.bmp`. Speichern Sie die Ergebnisbilder mit neuen Dateinamen, die den Filternamen beinhalten, ab. z.B. `HM_cube_gray_sharpen.bmp`.

> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Pushen Sie den aktuellen Stand in GitLab. Hier gibt es keine Unit Tests.


## Aufgabe 6: Parallelisierung der Convolution Anwendung

Ihre Lösung wendet nun alle aus der `kernels.txt` Datei eingelesenen Kernel auf das Ausgangsbild an und speichert die dabei neu generierten Bilder unter neuem Namen im Verzeichnis ab. 

In dieser Aufgabe soll nun die Anwendung der Convolution sowie das Speichern der erzeugten Bilder in jeweils einem Kind Prozess realisiert werden. Dazu werden die Funktionen `fork()` und `wait()` des Linux Betriebssystems benötigt. Binden Sie zuerst die dazu erforderlichen Header in der `versuch03.c` Datei ein. 

Die bisherige Lösung sollte in etwa die folgende Struktur besitzen:

```
for(int i = 0; i < kernelcount; i++)
{
	// Anwendung der Convolution
	conv2D(...);

	// Dateinamen erzeugen
	// ...

	// Bild speichern
	saveBmpGray(...);
}
```

Diese muss nun für die Parallelisierung wie folgt erweitert werden.

```
for(int i = 0; i < kernelcount; i++)
{
	// Für jede Kernel-Anwendung (Convolution) muss ein Kind Prozess erzeugt werden
	if (fork() == 0)
	{
		// Anwendung der Convolution
		conv2D(...);

		// Dateinamen erzeugen
		// ...

		// Bild speichern
		saveBmpGray(...);

		// Kind Prozess beenden
		exit(0);
	}
}

// Eltern Prozess muss auf das Ende aller Kind Prozesse warten (Zombie)
int status;
int pid;
while( (pid=wait(&status)) > 0)
{
	printf("Kind Prozess %d beendet: %d\n", pid, status);
}
```

Führen Sie das geänderte Programm aus und prüfen Sie, dass auch weiterhin die Bilddateien wie beabsichtigt erzeugt werden. Besprechen Sie mit Ihrer Praktikumsbetreuerin / Ihrem Praktikumsbetreuer das Verhalten des Programms?

**Anregungen zur Diskussion:**
* Warum ist die Ausgabe bei jeder Ausführung unterschiedlich?
* Welche Funktionalität übernimmt fork()?
* Wozu wird wait() im Eltern Prozess benötigt?
* Welche Rückgabewerte haben fork() und wait()?


> Nach Abschluss fügen Sie alle Änderungen dem Git Repository hinzu und versehen die Änderungen mit einer **aussagekräftigen** commit Nachricht.

> Übertragen Sie jetzt final alle Änderungen auch in GitLab (push). Es müssen nun alle Tests aus den Versuchen 1, 2 und 3 erfolgreich durchlaufen.

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


# Herzlichen Glückwunsch! 

**Sie haben das Praktikum in TI3-Embedded Systems nun vollständig bearbeitet.**