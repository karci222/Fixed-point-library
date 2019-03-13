//
// Created by Karol on 20. 2. 2019.
//

#include <cmath>
#include <cstdio>
#include "Fixed_point.h"

Fixed_point::Fixed_point(double number) {
    this->fractional_bits = 11;
    this->integer_bits = 4;
    this->number = 0;
    uint16_t integerPart = (uint16_t) number;
    uint16_t fractionalPart = convert_fraction(number);



    if(number >= 0) {
        if (number > 15) {
            integerPart = 15;
            fractionalPart = (1 << 12) - 1;
        }

        this->number |= (integerPart << 11);
        this->number |= fractionalPart;
    }else{
        number = number * (-1);
        uint16_t integerPart = (uint16_t) number;
        uint16_t fractionalPart = convert_fraction(number);

        if (number > 15) {
            integerPart = 15;
            printf("Number was too big and had to be concatenated!");
            fractionalPart = (1 << 12) - 1;
        }

        this->number |= (integerPart << 11);
        this->number |= fractionalPart;

        this->number ^= 65536 - 1;
        this->number += 1;
    }
}


Fixed_point::Fixed_point(double number, uint16_t integer_bits, uint16_t fractional_bits) {
    this->integer_bits = integer_bits;
    this->fractional_bits = fractional_bits;
    this->number = 0;

    uint16_t integer_part = (uint16_t) number;
    uint16_t fractional_part = convert_fraction(number);

    if(integer_bits + fractional_bits != 15){
        printf("Wrong format");
    }



    if(number >= 0){
        if(number > ((1 << integer_bits) - 1)){
            integer_part = (uint16_t ) ((1<<integer_bits) - 1);
            fractional_part = (uint16_t) ((1<<this->fractional_bits) - 1);
        }

        this->number |= (integer_part << this->fractional_bits);
        this->number |= fractional_part;
    }else{
        number = number * (-1);
        integer_part = (uint16_t) number;
        fractional_part = convert_fraction(number);

        if(number > ((1 << integer_bits) - 1)){
            integer_part = (uint16_t ) ((1<<integer_bits) - 1);
            fractional_part = (uint16_t) ((1<<this->fractional_bits) - 1);
        }

        this->number |= (integer_part<< this->fractional_bits);
        this->number |= fractional_part;

        this->number ^= 65536 - 1;
        this->number += 1;
    }
}

Fixed_point::Fixed_point() {
    this->number = 0;
    this->fractional_bits = 11;
    this->integer_bits = 4;
}


Fixed_point::Fixed_point(uint16_t number) {
    this->number = number;
    this->fractional_bits = 11;
    this->integer_bits = 4;
}

Fixed_point::Fixed_point(uint16_t number, uint16_t integer_bits, uint16_t fractional_bits) {
    this->number = number;
    this->fractional_bits = fractional_bits;
    this->integer_bits = integer_bits;
}

uint16_t Fixed_point::convert_fraction(double number) {
    double integral;
    return  (uint16_t)round(modf(number, &integral) * (1 << this->fractional_bits));
}


uint16_t Fixed_point::getNumber() const {
    return number;
}

void Fixed_point::setNumber(uint16_t number) {
    this->number = number;
}

uint16_t Fixed_point::getFractionalPart() {
    if(!this->isNegative()){
        return this->number & (uint16_t )((1<<this->fractional_bits) - 1);
    }else{
        uint16_t num = this->number & (uint16_t )((1<<this->fractional_bits) - 1);
        uint16_t mask = (uint16_t )(((1<<(16 - this->fractional_bits))-1)<<this->fractional_bits);
        num |= mask;
        return num;
    }
}

uint16_t Fixed_point::getIntegerPart() {
    if(!this->isNegative()) {
        return this->number >> this->fractional_bits;
    }else{
        uint16_t num = this->number >> this->fractional_bits;
        uint16_t mask = (uint16_t )(((1<<(16 - this->integer_bits))-1)<<this->integer_bits);
        num |= mask;
        return num;
    }

}

double Fixed_point::getDoubleValue() const {
    if(!(this->isNegative())){
        double res = (double )this->number/(double )(1 << this->fractional_bits);
        return res;
    }else{
        uint16_t number = this->number ^ (uint16_t )(0xffff);
        number += 1;
        double result = (double)number/(double)(1<<this->fractional_bits);
        return result*(-1);
    }
}

Fixed_point Fixed_point::operator<<(const int &shiftl) const {
    uint16_t new_number = this->number << shiftl;

    return {new_number, this->integer_bits, this->fractional_bits};
}

Fixed_point Fixed_point::operator>>(const int &shiftr) const {
    uint16_t new_number = 0;
    if(!(this->isNegative())) {
        new_number = this->number >> shiftr;
    }else{
        Fixed_point num = *this;
        new_number = num.absoluteValue().getNumber();
        new_number = new_number >> shiftr;
        new_number ^= 0xffff;
        new_number += 1;
    }

    return {new_number, this->integer_bits, this->fractional_bits};
}

Fixed_point Fixed_point::operator-(const Fixed_point &fxp) const {
    uint16_t op1 = this->number;
    uint16_t op2;
    if ((this->getFractional_bits() != fxp.getFractional_bits()) || (this->getInteger_bits() != fxp.getInteger_bits())){
        op2 = Fixed_point(fxp.getDoubleValue(), this->integer_bits, this->fractional_bits).getNumber();
    }else {
        op2 = fxp.getNumber();
    }

    op2 ^= 0xffff;
    op2 += 1;

    uint16_t result = op1 + op2;
    return {result, this->integer_bits, this->fractional_bits};
}

Fixed_point Fixed_point::operator+(const Fixed_point &fxp) const {
    uint16_t op1 = this->number;
    uint16_t op2;
    if ((this->getFractional_bits() != fxp.getFractional_bits()) || (this->getInteger_bits() != fxp.getInteger_bits())){
        op2 = Fixed_point(fxp.getDoubleValue(), this->integer_bits, this->fractional_bits).getNumber();
    }else {
        op2 = fxp.getNumber();
    }
    uint16_t result = op1 + op2;
    return {result, this->integer_bits, this->fractional_bits};
}



Fixed_point Fixed_point::absoluteValue() const {
    if(!(this->isNegative())){
        return {this->number, this->integer_bits, this->fractional_bits};
    }else{
        uint16_t number = this->number ^ (uint16_t )0xffff;
        number += 1;
        return {number, this->integer_bits, this->fractional_bits};
    }
}

bool Fixed_point::operator>(const Fixed_point &number) const {
    if ((this->getFractional_bits() != number.getFractional_bits()) || (this->getInteger_bits() != number.getInteger_bits())){
        printf("Wrong sizes! Numbers: %f\t %f\nInteger parts: %u\t %u\nFractional parts: %u\t %u\n", this->getDoubleValue(),
                number.getDoubleValue(),
                this->integer_bits,
                number.getInteger_bits(),
                this->fractional_bits,
                number.getFractional_bits());
    }
    if (!(this->isNegative()) && !(number.isNegative())){
        return this->number > number.getNumber();
    }else if ((this->isNegative()) && (number.isNegative())) {
        return this->number > number.getNumber();
    }else{
        return !(this->isNegative());
    }
}

bool Fixed_point::operator<(const Fixed_point &number) const {
    if ((this->getFractional_bits() != number.getFractional_bits()) || (this->getInteger_bits() != number.getInteger_bits())){
        printf("Wrong sizes! Numbers: %f\t %f\nInteger parts: %u\t %u\nFractional parts: %u\t %u\n", this->getDoubleValue(),
               number.getDoubleValue(),
               this->integer_bits,
               number.getInteger_bits(),
               this->fractional_bits,
               number.getFractional_bits());
    }
    if (!(this->isNegative()) && !(number.isNegative())){
        return this->number < number.getNumber();
    }else if ((this->isNegative()) && (number.isNegative())) {
        return this->number < number.getNumber();
    }else{
        return (this->isNegative()) != 0;
    }
}

int Fixed_point::isNegative() const {
    return (this->number & (uint16_t) 0x8000);
}

uint16_t Fixed_point::getInteger_bits() const {
    return integer_bits;
}

void Fixed_point::setInteger_bits(uint16_t integer_bits) {
    Fixed_point::integer_bits = integer_bits;
}

uint16_t Fixed_point::getFractional_bits() const {
    return fractional_bits;
}

void Fixed_point::setFractional_bits(uint16_t fractional_bits) {
    Fixed_point::fractional_bits = fractional_bits;
}

double Fixed_point::largestNum() {
    return (double )((1<<15)-1)/(double )(1 << this->fractional_bits);
}

Fixed_point Fixed_point::operator*(const Fixed_point &fxp) const {
    uint32_t op1, op2;
    uint32_t mask = 0xffff0000;

    op1 = (uint32_t) this->absoluteValue().getNumber();
    op2 = (uint32_t )fxp.absoluteValue().getNumber();

    uint32_t result = op1 * op2;
    result = result >> this->getFractional_bits();

    if(this->isNegative() != fxp.isNegative()){
        result ^= 0xffffffff;
        result += 1;
    }

    return Fixed_point((uint16_t) result, this->integer_bits, this->fractional_bits);
}
