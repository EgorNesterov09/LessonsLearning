#pragma once

#include <strung>
#include <vector>
#include <deque>
#include <unordered_map>
#include <string_view>

struct Stop {
    std::string name;
    Coordinates coord;
};
struct Bus {
    std::string name;
    std::vector<Stop*> route;
    bool is_ring;
    size_t unique_stops;
};

class TransportCatalogue {
	// Реализуйте класс самостоятельно
public:
    AddStop
    FindStop
    AddBus
    FindBus
    
private:       
    std::deque<Stop> stops_; //номенклатура остановок
    std::unordered_map<std::string_view, Stop*> stopname_to_stop_; //указатель на остановку по ее имени
        
    std::deque<Bus> buses_; //номенклатура маршрутов
    std::unordered_map<std::string_view, Bus*> busname_to_bus_; //указатель на автобус по номеру маршрута
    /*
    struct HasherForDistanceMap {
        size_t operator() (std::pair<Stop*, Stop*> p) {
           return p.first * 37 + p.second;
        }
    }
    */
    
    
    //std::unordered_map<std::pair<Stop*, Stop*>, double, HasherForDistanceMap> distances //храним расстояния между оставками     
};