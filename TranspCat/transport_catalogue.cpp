#include "transport_catalogue.h"
#include "geo.h"

#include <string_view>


void TransportCatalogue::AddStop(const std::string& name, const Coordinates& coord) {
	stops_.push_back(Stop{ name, coord });
	stopname_to_stop_[name] = &stops_.back();
}
const Stop* TransportCatalogue::FindStop(const std::string_view name) const {
	if (!stopname_to_stop_.count(name)) {
		return nullptr;
	}
	
	return stopname_to_stop_.at(name);
}