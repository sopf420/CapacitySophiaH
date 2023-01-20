#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <map>
using namespace std;

int length;
int width;

regex checkMenu("[1-4]");
regex numberCheck("[[:digit:]]+");

void menu();


class Gebaeude {
public:
    Gebaeude() {
        basePreis = 0;
        label = '0';
    }

    Gebaeude(
        int basePreis, char label) :basePreis(basePreis), label(label) {}

    int getPrice() const {
        return basePreis;
    }

    char getLabel() const {
        return label;
    }

protected:
    int basePreis;
    char label;
    string name;
};

class Material {
public:
    Material(string name, int preis) : name(name), preis(preis) {}
    string getName() const {
        return name;
    }
    int getPrice() const {
        return preis;
    }
private:
    string name;
    int preis;
};

class Holz : public Material {
public:
    Holz() : Material("Holz", 25) {}
};

class Metal : public Material {
public:
    Metal() : Material("Metall", 15) {}
};

class Plastik : public Material {
public:
    Plastik() : Material("Kunststoff", 5) {}
};

struct MaterialComparator {
    bool operator()(const Material& m1, const Material& m2) const {
        return m1.getName() < m2.getName();
    }
};

class WasserPlatzieren : public Gebaeude {
public:
    WasserPlatzieren() : Gebaeude(100, 'W') {
        materials = map<Material, int, MaterialComparator>({
            {Holz(), 2},
            {Metal(), 2},
            {Plastik(), 1}
            });
    }
    map<Material, int, MaterialComparator> materials;
};

class WindPlatzieren : public Gebaeude {
public:
    WindPlatzieren() : Gebaeude(50, 'I') {
        materials = map<Material, int, MaterialComparator>({
            {Plastik(), 2},
            {Metal(), 2}
            });
    }
    map<Material, int, MaterialComparator> materials;
};

class SolarPlatzieren : public Gebaeude {
public:
    SolarPlatzieren() : Gebaeude(250, 'S') {
        materials = map<Material, int, MaterialComparator>({
        {Plastik(), 3},
        {Metal(), 1}
            });
    }
    map<Material, int, MaterialComparator> materials;
};

Gebaeude* buildingMenu();

Gebaeude*** Area;

int main(int argc, char** argv) {

    length = stoi(argv[1]);
    width = stoi(argv[2]);

    /*Capybaras sind unglaubliche Ingenieure, erst kürzlich haben sie einen Durchbruch bei der umwelt -
    freundlichen Energie erlangt.Sie beschließen daher eine extra Stadt namens Capycity aufzubauen,
        welche ihren Fokus auf die Erzeugung von Energie legt und somit umgebende Städte vollständig ver -
        sorgen kann.
        Aktuell sind sie in der Lage mithilfe folgender Technologien Energie zu erzeugen :
    • Wasserkraftwerk
        • Windkraftwerk
        • Solarpanele*/

    cout << "Hallo und Herzlich Willkommen in der Welt von CapyCity!"
            <<"In diesem kleinen Spiel kannst du der Erbauer deiner eigenen Stadt werden!\n"
            << "Die Idee dahinter stammt von erstaunlichen Ingeneuren,\n"
            <<"welche einen grossen Schritt fuer umweltfreundliche Energie erreichten.\n"
            << "\n"
            <<"Da du die Welt bereits betreten hast, hast du den Umfang deiner Stadt bereits festgelegt auf " << argv[1] << "mal" << argv[2] <<".\n"
            <<"Ich hoffe damit bist du zufrieden. Wenn ja, legen wir los!\n\n"
            << "Was willst du als erstes tun?";

    Area = new Gebaeude * *[length];
    for (int x = 0; x < length; x++) {
        Area[x] = new Gebaeude * [width];
        for (int y = 0; y < length; y++) {
            Area[x][y] = nullptr;
        }
    }

    while (true) {
        menu();
    }
}

class CapycitySim {
public:
    void gebaeudeBau() {
        Gebaeude* auswahlBau = buildingMenu();

        if (auswahlBau == nullptr) {
            return;
        }

        int startX{ xPosition() };
        int startY{ yPosition() };
        int breite{ bauWidth() };
        int laenge{ bauenLength() };

        for (int i = startX; i < startX + breite; i++) {
            for (int j = startY; j < startY + laenge; j++) {
                if ((startX + breite) > width || (startY + laenge) > length || Area[j][i] != nullptr) {
                    cout << "Diese Flaeche ist bereits belegt oder ist ausserhalb des Baubereichs!\n\n";
                    return gebaeudeBau();
                }
                else {
                    Area[j][i] = auswahlBau;
                }
            }
        }
    }

    int xPosition() {
        string startX;

        cout << "Position X eingeben: \n";
        cin >> startX;
        if (regex_match(startX, numberCheck) && stoi(startX) < length) {
            return stoi(startX);
        }
        else {
            cout << "Zahl zwischen 0 und " << (length - 1) << " eingeben: \n";
            return xPosition();
        }
    }

    int yPosition() {
        string startY;

        cout << "Position Y eingeben: \n";
        cin >> startY;
        if (regex_match(startY, numberCheck) && stoi(startY) < width) {
            return stoi(startY);
        }
        else {
            cout << "Bitte Zahl zwischen 0 und " << (width - 1) << " eingeben: \n";
            return yPosition();
        }
    }

    int bauWidth() {
        string breite;

        cout << "Wie breit soll denn die Flaeche werden?: \n";
        cin >> breite;
        if (regex_match(breite, numberCheck) && stoi(breite) > 0 && stoi(breite) <= width) {
            return stoi(breite);
        }
        else {
            cout << "Die Breite muss zwischen 1 und " << width << " liegen!\n";
            return bauWidth();
        }
    }

    int bauenLength() {
        string laenge;

        cout << "Und wie lang soll die Flaeche sein?: \n";
        cin >> laenge;
        if (regex_match(laenge, numberCheck) && stoi(laenge) > 0 && stoi(laenge) <= length) {
            return stoi(laenge);
        }
        else {
            cout << "Die Laenge muss zwischen 1 und " << length << " liegen!\n";
            return bauenLength();
        }
    }

    void buildingPlan() {
        int w = 0;
        int i = 0;
        int s = 0;

        for (int x = 0; x < length; x++) {
            for (int y = 0; y < width; y++) {
                if (Area[x][y] == nullptr) {
                    cout << "[ ]";
                }
                else {
                    cout << "[" << Area[x][y]->getLabel() << "]";
                    if (Area[x][y]->getLabel() == 'W') {
                        w++;
                    }
                    if (Area[x][y]->getLabel() == 'I') {
                        i++;
                    }
                    if (Area[x][y]->getLabel() == 'S') {
                        s++;
                    }
                }
            }
            cout << endl;
        }

        // Wasserkraftwerk
        int matCost = 0;

        cout << endl
            << w << " Wassserkraftwerke\n"
            << "Ein einzelnes Wasserkraftwerk kostet: " << WasserPlatzieren().getPrice() << "$\n"
            << "Fuer die Wasserkraftwerke werden benoetigt: ";

        for (auto& whichMat : WasserPlatzieren().materials) {
            cout << "[" << w * whichMat.second << " " << whichMat.first.getName() << "] ";
            matCost += whichMat.second * whichMat.first.getPrice();
        }

        cout << endl
            << "Die Gesamtkosten der Wasserkraftwerke betragen:  "
            << w * (WasserPlatzieren().getPrice() + matCost) << "$\n";


        // Windkraftwerk
        matCost = 0;

        cout << endl
            << i << " Windkraftwerke\n"
            << "Ein einzelnes Windkraftwerk kostet: " << WindPlatzieren().getPrice() << "$\n"
            << "Fuer die Windkraftwerk werden benoetigt: ";

        for (auto& whichMat : WindPlatzieren().materials) {
            cout << "[" << i * whichMat.second << " " << whichMat.first.getName() << "] ";
            matCost += whichMat.second * whichMat.first.getPrice();
        }

        cout << endl
            << "Die Gesamtkosten der Wasserkraftwerke betragen:  "
            << i * (WindPlatzieren().getPrice() + matCost) << "$\n";

        // Solarpanel
        matCost = 0;

        cout << endl
            << s << " Solarpanel\n"
            << "Ein einzelnes Solarpanel kostet: " << SolarPlatzieren().getPrice() << "$\n"
            << "Fuer die Solarpanel werden benoetigt: ";

        for (auto& whichMat : SolarPlatzieren().materials) {
            cout << "[" << s * whichMat.second << " " << whichMat.first.getName() << "] ";
            matCost += whichMat.second * whichMat.first.getPrice();
        }

        cout << endl
            << "Die Gesamtkosten der Wasserkraftwerke betragen:  "
            << s * (SolarPlatzieren().getPrice() + matCost) << "$\n";

        menu();
    }

    void deleteArea() {
        int startX{ xPosition() };
        int startY{ yPosition() };
        int breite{ bauWidth() };
        int laenge{ bauenLength() };

        for (int i = startX; i < min(width, startX + breite); i++) {
            for (int j = startY; j < min(length, startY + laenge); j++) {
                Area[j][i] = nullptr;
            }
        }
        menu();
    }
};

void menu() {
    string choice;

    CapycitySim CapycitySim;

    cout << endl
        << "1 - Gebaeude setzen\n"
        << "2 - Bereich loeschen\n"
        << "3 - Aktueller Bauplan\n"
        << "4 - Exit\n";

    cin >> choice;

    if (regex_match(choice, checkMenu)) {
        switch (stoi(choice)) {
        case 1:
            //Gebäude setzen    
            CapycitySim.gebaeudeBau();
            break;
        case 2:
            //Bereich löschen
            CapycitySim.deleteArea();
            break;
        case 3:
            //Print Blauplan
            CapycitySim.buildingPlan();
            break;
        case 4:
            //Beenden des Programms
            cout << "Bye Bye";
            exit(0);
        }
    }
    else {
        cout << "Nur Zahlen von 1 - 4 erlaubt!\n";
        menu();
    }
}

Gebaeude* buildingMenu() {
    string auswahlBau;

    cout << "Was für ein Gebaeude willst du denn bauen?";

    cout << endl
        << "1 - Das Wasserkraftwerk\n"
        << "2 - Das Windkraftwerk\n"
        << "3 - Die Solarpanele\n"
        << "4 - Zurueck zum Hauptmenue\n";
    cin >> auswahlBau;

    if (regex_match(auswahlBau, checkMenu)) {
        switch (stoi(auswahlBau)) {
        case 1:
            return new WasserPlatzieren();
            break;
        case 2:
            return new WindPlatzieren();
            break;
        case 3:
            return new SolarPlatzieren();
            break;
        default:
            return nullptr;
        }
    }
    else {
        cout << "Nur Zahlen von 1 - 4 erlaubt!\n";
        return buildingMenu();
    }
}