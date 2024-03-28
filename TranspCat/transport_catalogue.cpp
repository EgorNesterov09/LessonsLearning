#include "transport_catalogue.h"
#include "geo.h"

#include <string_view>
#include <set>


void TransportCatalogue::AddStop(Stop&& s) {	
	stops_.push_back(std::move(s));
	stopname_to_stop_[stops_.back().name] = &stops_.back();
	stop_to_buses_[stops_.back().name];
}
Stop* TransportCatalogue::FindStop(const std::string_view name) const {
	if (!stopname_to_stop_.count(name)) {
		return nullptr;
	}	
	return stopname_to_stop_.at(name);
}

void TransportCatalogue::AddBus(Bus&& b) {	
	buses_.push_back(std::move(b));
	busname_to_bus_[buses_.back().name] = &buses_.back();
	for (const auto& s : buses_.back().route) {
		stop_to_buses_.at(s->name).insert(buses_.back().name);
	}
}

const std::set<std::string_view>* TransportCatalogue::GetBusesFromStop(const std::string_view stop) const {
	if (!stop_to_buses_.count(stop)) {
		return nullptr;
	}
	return &(stop_to_buses_.at(stop));
}

Bus* TransportCatalogue::FindBus(const std::string_view name) const {
	if (!busname_to_bus_.count(name)) {
		return nullptr;
	}
	return busname_to_bus_.at(name);
}