// LineManager.cpp
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "LineManager.h"
#include "Utilities.h"

namespace seneca {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream in(file);
        if (!in)
            throw std::string("Unable to open [") + file + "] file.";

        Utilities util;
        std::string line;
        std::vector<std::pair<std::string, std::string>> links;

        while (std::getline(in, line)) {
            size_t next_pos = 0;
            bool more = true;
            std::string first = util.extractToken(line, next_pos, more);
            std::string second = more ? util.extractToken(line, next_pos, more) : "";
            links.emplace_back(first, second);
        }

        for (const auto& [first, second] : links) {
            auto it1 = std::find_if(stations.begin(), stations.end(),
                [&](Workstation* w) { return w->getItemName() == first; });
            if (it1 == stations.end())
                throw std::string("Cannot find station ") + first;

            if (!second.empty()) {
                auto it2 = std::find_if(stations.begin(), stations.end(),
                    [&](Workstation* w) { return w->getItemName() == second; });
                if (it2 == stations.end())
                    throw std::string("Cannot find station ") + second;

                (*it1)->setNextStation(*it2);
            }

            m_activeLine.push_back(*it1);
        }

        for (auto* candidate : m_activeLine) {
            bool isFirst = std::none_of(m_activeLine.begin(), m_activeLine.end(),
                [&](Workstation* ws) { return ws->getNextStation() == candidate; });
            if (isFirst) {
                m_firstStation = candidate;
                break;
            }
        }

        m_cntCustomerOrder = g_pending.size();
        // DO NOT CALL reorderStations() here! Let the tester call it.
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> ordered;
        Workstation* current = m_firstStation;

        while (current != nullptr) {
            ordered.push_back(current);
            current = current->getNextStation();
        }

        m_activeLine = std::move(ordered);
    }

    bool LineManager::run(std::ostream& os) {
        static size_t iteration = 0;
        os << "Line Manager Iteration: " << ++iteration << std::endl;

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto* station : m_activeLine)
            station->fill(os);

        for (auto* station : m_activeLine)
            station->attemptToMoveOrder(os);

        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }

    void LineManager::display(std::ostream& os) const {
        for (auto* station : m_activeLine)
            station->display(os);
    }

}
