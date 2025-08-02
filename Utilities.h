// Utilities.h
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>

namespace seneca {
    class Utilities {
        size_t m_widthField{1};                    // instance variable
        static char m_delimiter;                   // class variable

    public:
        void setFieldWidth(size_t newWidth);       // sets m_widthField
        size_t getFieldWidth() const;              // gets m_widthField

        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        static void setDelimiter(char newDelimiter); // sets the delimiter
        static char getDelimiter();                  // gets the delimiter
    };
}

#endif // SENECA_UTILITIES_H
