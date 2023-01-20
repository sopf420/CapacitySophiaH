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


    cout    <<" Hallo und Herzlich Willkommen in der Welt von CapyCity!\n"
            <<" In diesem kleinen Spiel kannst du der Erbauer deiner eigenen Stadt werden!\n"
            << " Die Idee dahinter stammt von erstaunlichen Ingeneuren,\n"
            <<" welche einen grossen Schritt fuer umweltfreundliche Energieerzeugung erreichen wollten,\n"
            << " denn Cpapacity ist keine normale City.\n"
            << " Sie erfuellt nur den Zweck, Energie zu erzeugen und die Menschen damit zu versorgen!\n"
            << " Mihilfe der Technologien der Windkraft, von Wasserwerken und Solapanels kannst du deine Stadt gestalten.\n"
            << " Mal sehen was dein Ideenreichtum der Stadt Capacity bringt.\n\n"
            <<" Da du die Welt bereits betreten hast, hast du den Umfang deiner Stadt bereits auf " << argv[1] << "mal" << argv[2] <<" festgelegt.\n"
            <<" Ich hoffe damit bist du zufrieden. Wenn ja, legen wir los!\n\n"
            << " Was willst du als erstes tun?\n";
     
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
                    cout << "Die gewaehlte Flaeche ist bereits besetzt oder ist ausserhalb deines Baubereichs!\n\n";
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
            << "Ein Platz fuer ein Wasserkraftwerk kostet: " << WasserPlatzieren().getPrice() << "$\n"
            << "Um dein Wasserwerk zu bauen brauchst du: ";

        for (auto& whichMat : WasserPlatzieren().materials) {
            cout << "[" << w * whichMat.second << " " << whichMat.first.getName() << "] ";
            matCost += whichMat.second * whichMat.first.getPrice();
        }

        cout << endl
            << "Deine Wasserkraftwerke Kosten insgesamt:  "
            << w * (WasserPlatzieren().getPrice() + matCost) << "$\n";


        // Windkraftwerk
        matCost = 0;

        cout << endl
            << i << " Windkraftwerke\n"
            << "Ein einzelnes Windkraftwerk kostet: " << WindPlatzieren().getPrice() << "$\n"
            << "Um dein Windkraftwerk zu bauen brauchst du: ";

        for (auto& whichMat : WindPlatzieren().materials) {
            cout << "[" << i * whichMat.second << " " << whichMat.first.getName() << "] ";
            matCost += whichMat.second * whichMat.first.getPrice();
        }

        cout << endl
            << "Deine Windkraftwerke Kosten insgesamt:  "
            << i * (WindPlatzieren().getPrice() + matCost) << "$\n";

        // Solarpanel
        matCost = 0;

        cout << endl
            << s << " Solarpanel\n"
            << "Ein einzelnes Solarpanel kostet: " << SolarPlatzieren().getPrice() << "$\n"
            << "Um dein Solapanel zu bauen brauchst du: ";

        for (auto& whichMat : SolarPlatzieren().materials) {
            cout << "[" << s * whichMat.second << " " << whichMat.first.getName() << "] ";
            matCost += whichMat.second * whichMat.first.getPrice();
        }

        cout << endl
            << "Deine Solarpanel Kosten insgesamt:  "
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


Gebaeude* buildingMenu() {
    string auswahlBau;

    cout << "Was für ein Gebaeude willst du denn bauen?";

    cout << endl
        << "1: Ein Wasserkraftwerk\n"
        << "2: Ein Windkraftwerk\n"
        << "3: Ein Solarpanel\n"
        << "4: Zurueck zum Hauptmenue\n";
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
        cout << "Scherzkeks. Bitte eine Zahl von 1 bis 4:\n";
        return buildingMenu();
    }
}

void menu() {
    string choice;

    CapycitySim CapycitySim;

    cout << endl
        << "1: Ein Gebaeude erstellen!\n"
        << "2: Gebaeude loeschen.\n"
        << "3: Aktueller Lageplan\n"
        << "4: Beenden\n";

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
            cout << "Auf Wiedersehen und bis bald!";
            exit(0);
        }
    }
    else {
        cout << "Scherzkeks. Bitte eine Zahl von 1 bis 4:\n";
        menu();
    }
}
