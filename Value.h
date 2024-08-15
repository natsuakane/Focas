#pragma once

#include <string>
#include "ValueType.h"
#include "Exceptions.h"

struct Value {
public:
    Value(int v, int lineno) {
        valueType = IntNum;
        intValue = v;
        this->lineno = lineno;
    }
    Value(long v, int lineno) {
        valueType = LongNum;
        longValue = v;
        this->lineno = lineno;
    }
    Value(char v, int lineno) {
        valueType = CharNum;
        charValue = v;
        this->lineno = lineno;
    }
    Value(float v, int lineno) {
        valueType = FloatNum;
        floatValue = v;
        this->lineno = lineno;
    }
    Value(double v, int lineno) {
        valueType = DoubleNum;
        doubleValue = v;
        this->lineno = lineno;
    }
    Value(std::string v, int lineno) {
        valueType = StringVal;
        strValue = v;
        this->lineno = lineno;
    }
    Value(void* v, int lineno) {
        valueType = PtrVal;
        ptrValue = v;
        this->lineno = lineno;
    }

    int GetInt() {
        if(valueType != IntNum) throw std::runtime_error(UnsuitableType("Int", lineno));
        return intValue;
    }
    long GetLong() {
        if(valueType != IntNum) throw std::runtime_error(UnsuitableType("Long", lineno));
        return longValue;
    }
    char GetChar() {
        if(valueType != IntNum) throw std::runtime_error(UnsuitableType("Char", lineno));
        return charValue;
    }
    float GetFloat() {
        if(valueType != IntNum) throw std::runtime_error(UnsuitableType("Float", lineno));
        return floatValue;
    }
    double GetDouble() {
        if(valueType != IntNum) throw std::runtime_error(UnsuitableType("Double", lineno));
        return doubleValue;
    }
    std::string GetStr() {
        if(valueType != IntNum) throw std::runtime_error(UnsuitableType("String", lineno));
        return strValue;
    }
    void* GetPtr() {
        if(valueType != IntNum) throw std::runtime_error(UnsuitableType("Pointer", lineno));
        return ptrValue;
    }

    ~Value() {}

private:
    union {
        int intValue;
        long longValue;
        char charValue;
        float floatValue;
        double doubleValue;
        std::string strValue;
        void* ptrValue;
    };

    ValueType valueType;
    int lineno;

};