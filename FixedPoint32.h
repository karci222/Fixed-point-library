//
// Created by Karol on 24. 1. 2020.
//

#ifndef APPROXIMATIONTESTS_FIXEDPOINT32_H
#define APPROXIMATIONTESTS_FIXEDPOINT32_H


#include <stdint-gcc.h>

class Fixed_point32{
private:
    uint32_t number;
    uint32_t integer_bits;
    uint32_t fractional_bits;
    uint32_t convert_fraction(double number);

public:
    Fixed_point32();
    Fixed_point32(double number);
    Fixed_point32(double number, uint32_t integer_bits, uint32_t fractional_bits);
    Fixed_point32(uint32_t number, uint32_t integer_bits, uint32_t fractional_bits);
    uint32_t getNumber() const;
    void setNumber(uint32_t number);
    uint32_t getFractionalPart() ;
    uint32_t getIntegerPart() ;
    double getDoubleValue() const ;
    Fixed_point32 absoluteValue() const ;
    Fixed_point32 operator+(const Fixed_point32 &fxp) const;
    Fixed_point32 operator-(const Fixed_point32 &fxp) const;
    Fixed_point32 operator>>(const int &shiftr) const;
    Fixed_point32 operator<<(const int &shiftl) const;
    bool operator>(const Fixed_point32 &number) const;
    bool operator<(const Fixed_point32 &number) const;
    bool operator<=(const Fixed_point32 &number) const;
    bool operator>=(const Fixed_point32 &number) const;
    bool operator==(const Fixed_point32 &number) const;
    Fixed_point32 operator*(const Fixed_point32 &fxp) const;
    Fixed_point32(uint32_t number);
    int isNegative() const ;
    uint32_t getInteger_bits() const;
    void setInteger_bits(uint32_t integer_bits);
    uint32_t getFractional_bits() const;
    void setFractional_bits(uint32_t fractional_bits);
    double largestNum();
    int getLeadingOnes();
};


#endif //APPROXIMATIONTESTS_FIXEDPOINT32_H
