// Utilities.cpp
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
#include "Utilities.h"

namespace seneca {

    char Utilities::m_delimiter = '|';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        if (next_pos >= str.length()) {
            more = false;
            return "";
        }

        size_t end_pos = str.find(m_delimiter, next_pos);
        std::string token;

        if (end_pos == std::string::npos) {
            token = str.substr(next_pos);
            more = false;
        } else {
            if (end_pos == next_pos) {
                more = false;
                throw std::runtime_error("Delimiter found at next_pos");
            }
            token = str.substr(next_pos, end_pos - next_pos);
            next_pos = end_pos + 1;
            more = true;
        }

        // Trim whitespace
        size_t first = token.find_first_not_of(' ');
        size_t last = token.find_last_not_of(' ');
        if (first == std::string::npos || last == std::string::npos)
            token = "";
        else
            token = token.substr(first, last - first + 1);

        if (m_widthField < token.length())
            m_widthField = token.length();

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }
}
