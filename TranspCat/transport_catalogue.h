#pragma once

#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <set>
#include <string_view>

#include "geo.h"

struct Stop {
    std::string name;
    Coordinates coord;
};
struct Bus {
    std::string name;
    std::vector<Stop*> route;
};

class TransportCatalogue {
	// Реализуйте класс самостоятельно
public:
    void AddStop(Stop&& s);
    Stop* FindStop(const std::string_view name) const;
    void AddBus(Bus&& b);
    Bus* FindBus(const std::string_view name) const;

    const std::set<std::string_view>* GetBusesFromStop(const std::string_view stop) const;
private:       
    std::deque<Stop> stops_; //номенклатура остановок
    std::unordered_map<std::string_view, Stop*> stopname_to_stop_; //указатель на остановку по ее имени
        
    std::deque<Bus> buses_; //номенклатура маршрутов
    std::unordered_map<std::string_view, Bus*> busname_to_bus_; //указатель на автобус по номеру маршрута

    std::unordered_map<std::string_view, std::set<std::string_view>> stop_to_buses_;
    /*
    struct HasherForDistanceMap {
        size_t operator() (std::pair<Stop*, Stop*> p) {
           return p.first * 37 + p.second;
        }
    }
    */
    
    
    //std::unordered_map<std::pair<Stop*, Stop*>, double, HasherForDistanceMap> distances //храним расстояния между оставками     
};