#include "stat_reader.h"
#include "transport_catalogue.h"
#include "geo.h"

#include <iostream>
#include <set>

void ParseAndPrintStat(const TransportCatalogue& tansport_catalogue, std::string_view request,
                       std::ostream& output) {
    // Реализуйте самостоятельно
    if (request.find("Bus") != request.npos) {
        std::string_view query_descripton = request.substr(3);
        auto pos_1 = query_descripton.find_first_not_of(' ');
        auto pos_2 = query_descripton.find_last_not_of(' ');
        std::string_view s = query_descripton.substr(pos_1, pos_2 + 1 - pos_1);

        auto b = tansport_catalogue.FindBus(s);
        if (!b) {
            output << "Bus " << s << ": not found" << std::endl;
        }
        else {
            size_t R = b->route.size();
            std::set<Stop*> uniq(b->route.begin(), b->route.end());
            size_t U = uniq.size();
            double L = 0;
            for (size_t i = 1; i < b->route.size(); ++i) {
                L += ComputeDistance(b->route[i - 1]->coord, b->route[i]->coord);
            }
            output << "Bus " << s << ": " << R << " stops on route, " << U << " unique stops, " << L << " route length" << std::endl;
        }
    }
    
}