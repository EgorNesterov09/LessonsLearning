#include <iostream>
#include <string>

#include "input_reader.h"
#include "stat_reader.h"

using namespace std;

int main() {
    TransportCatalogue catalogue;
    /*
    Stop s{ "123", Coordinates {123, 123} };
    catalogue.AddStop(s.name, s.coord);
    auto s1 = catalogue.FindStop("123");

    cout << s1->name << " " << s1->coord.lat << " " << s1->coord.lng << endl;
    */
    
    int base_request_count;
    cin >> base_request_count >> ws;

    {
        InputReader reader;
        for (int i = 0; i < base_request_count; ++i) {
            string line;
            getline(cin, line);
            reader.ParseLine(line);
        }
        reader.ApplyCommands(catalogue);
    }

    /*
    auto s1 = catalogue.FindStop("Tolstopaltsevo");
    cout << s1->name << " " << s1->coord.lat << " " << s1->coord.lng << endl;
    auto s2 = catalogue.FindStop("Marushkino");
    cout << s2->name << " " << s2->coord.lat << " " << s2->coord.lng << endl;
    
    auto b1 = catalogue.FindBus("256");
    cout << b1->name << ": ";
    for (const auto a : b1->route) {
        cout << a->name << " ";
    } cout << endl;

    auto b2 = catalogue.FindBus("750");
    cout << b2->name << ": ";
    for (const auto a : b2->route) {
        cout << a->name << " ";
    }
    */
    
    int stat_request_count;
    cin >> stat_request_count >> ws;
    for (int i = 0; i < stat_request_count; ++i) {
        string line;
        getline(cin, line);
        ParseAndPrintStat(catalogue, line, cout);
    } 
}