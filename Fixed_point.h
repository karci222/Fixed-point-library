//
// Created by Karol on 20. 2. 2019.
//

#ifndef APPROXIMATIONTESTS_FIXED_POINT_H
#define APPROXIMATIONTESTS_FIXED_POINT_H

#include <stdint-gcc.h>

/**
 * My custom 16 bit fixed point type
 *
 * Representation is as follows: s4.11
 * 1st bit is a sign bit, 4 bits are for integer part (-16, 15)
 * 11 bits are used to represent fractional part.
 */

class Fixed_point {

private:
    uint16_t number;
    uint16_t integer_bits;
    uint16_t fractional_bits;

public:
    Fixed_point();
    Fixed_point(double number);
    Fixed_point(double number, uint16_t integer_bits, uint16_t fractional_bits);
    Fixed_point(uint16_t number, uint16_t integer_bits, uint16_t fractional_bits);
    uint16_t getNumber() const;
    void setNumber(uint16_t number);
    uint16_t getFractionalPart() ;
    uint16_t getIntegerPart() ;
    double getDoubleValue() const ;
    Fixed_point absoluteValue() const ;
    Fixed_point operator+(const Fixed_point &fxp) const;
    Fixed_point operator-(const Fixed_point &fxp) const;
    Fixed_point operator>>(const int &shiftr) const;
    Fixed_point operator<<(const int &shiftl) const;
    bool operator>(const Fixed_point &number) const;
    bool operator<(const Fixed_point &number) const;
    bool operator<=(const Fixed_point &number) const;
    bool operator>=(const Fixed_point &number) const;
    bool operator==(const Fixed_point &number) const;
    Fixed_point operator*(const Fixed_point &fxp) const;
    Fixed_point(uint16_t number);
    int isNegative() const ;
    uint16_t getInteger_bits() const;
    void setInteger_bits(uint16_t integer_bits);
    uint16_t getFractional_bits() const;
    void setFractional_bits(uint16_t fractional_bits);
    double largestNum();
    int getLeadingOnes();

private:
    uint16_t convert_fraction(double number);
};

#endif //APPROXIMATIONTESTS_FIXED_POINT_H
