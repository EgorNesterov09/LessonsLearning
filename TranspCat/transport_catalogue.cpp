#include "transport_catalogue.h"
#include "geo.h"

#include <string_view>


void TransportCatalogue::AddStop(Stop&& s) {
	stops_.push_back(std::move(s));
	stopname_to_stop_[stops_.back().name] = &stops_.back();
}
const Stop* TransportCatalogue::FindStop(const std::string_view name) const {
	if (!stopname_to_stop_.count(name)) {
		return nullptr;
	}	
	return stopname_to_stop_.at(name);
}