// Workstation.cpp
#include <iostream>
#include "Workstation.h"

namespace seneca {

    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string& record) : Station(record) {}

    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }

bool Workstation::attemptToMoveOrder(std::ostream& os) {
    if (m_orders.empty())
        return false;

    CustomerOrder& order = m_orders.front();
    const std::string& item = getItemName();

    // Only move if item is not required, already filled, or unfillable
    if (!order.requiresItem(item) || order.isItemFilled(item) || getQuantity() == 0) {
        if (m_pNextStation) {
            *m_pNextStation += std::move(order);
        } else {
            if (order.isOrderFilled())
                g_completed.push_back(std::move(order));
            else
                g_incomplete.push_back(std::move(order));
        }
        m_orders.pop_front();
        return true;
    }

    // Otherwise: the item is required and unfilled, and stock > 0,
    // so we let it stay at this station for another iteration
    return false;
}





    void Workstation::setNextStation(Workstation* station) {
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const {
        os << getItemName() << " --> ";
        if (m_pNextStation)
            os << m_pNextStation->getItemName();
        else
            os << "End of Line";
        os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        // Optional: Debugging output
        //std::cout << "DEBUG: Order added to " << getItemName() << ": " << newOrder.getName() << std::endl;

        m_orders.push_back(std::move(newOrder));
        return *this;
    }

}
