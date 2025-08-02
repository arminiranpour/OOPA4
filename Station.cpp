// Station.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

namespace seneca {

    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;

    Station::Station(const std::string& record) {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        m_id = ++id_generator;

        m_itemName = util.extractToken(record, next_pos, more);
        m_serialNumber = std::stoul(util.extractToken(record, next_pos, more));
        m_quantity = std::stoul(util.extractToken(record, next_pos, more));
        m_description = util.extractToken(record, next_pos, more);
//hi

    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0)
            --m_quantity;
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::right << std::setw(3) << std::setfill('0') << m_id << " | ";
        const int nameWidth = 14;
        os << std::left << std::setw(nameWidth) << std::setfill(' ') << m_itemName << " | ";

        os << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::setfill(' ') << m_quantity << " | ";
            os << m_description;
        }

        os << std::endl;
    }

}
