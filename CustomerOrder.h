// CustomerOrder.h
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>

namespace seneca {

    class Station; // forward declaration

    class CustomerOrder {
        struct Item {
            std::string m_itemName;
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            Item(const std::string& src) : m_itemName(src) {}
        };

        std::string m_name;
        std::string m_product;
        size_t m_cntItem{};
        Item** m_lstItem{nullptr};

        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const std::string& record);
        CustomerOrder(const CustomerOrder& other) {
            throw std::runtime_error("Copy not allowed");
        }
        CustomerOrder& operator=(const CustomerOrder&) = delete;
        CustomerOrder(CustomerOrder&& other) noexcept;
        CustomerOrder& operator=(CustomerOrder&& other) noexcept;
        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
        bool requiresItem(const std::string& itemName) const;
        const std::string& getName() const { return m_name; } // helpful for debugging
    };

}

#endif // SENECA_CUSTOMERORDER_H
