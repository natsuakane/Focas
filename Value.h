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
    Value(void* v, int lineno) {
        valueType = PtrVal;
        ptrValue = v;
        this->lineno = lineno;
    }

    int GetInt() {
        if(valueType != IntNum) throw std::runtime_error(UnsuitableType("Int", ValueTypeNames[valueType], lineno));
        return intValue;
    }
    long GetLong() {
        if(valueType != LongNum) throw std::runtime_error(UnsuitableType("Long", ValueTypeNames[valueType], lineno));
        return longValue;
    }
    char GetChar() {
        if(valueType != CharNum) throw std::runtime_error(UnsuitableType("Char", ValueTypeNames[valueType], lineno));
        return charValue;
    }
    float GetFloat() {
        if(valueType != FloatNum) throw std::runtime_error(UnsuitableType("Float", ValueTypeNames[valueType], lineno));
        return floatValue;
    }
    double GetDouble() {
        if(valueType != DoubleNum) throw std::runtime_error(UnsuitableType("Double", ValueTypeNames[valueType], lineno));
        return doubleValue;
    }
    void* GetPtr() {
        if(valueType != PtrVal) throw std::runtime_error(UnsuitableType("Pointer", ValueTypeNames[valueType], lineno));
        return ptrValue;
    }

    ~Value() {
        
    }

private:
    union {
        int intValue;
        long longValue;
        char charValue;
        float floatValue;
        double doubleValue;
        void* ptrValue;
    };

    ValueType valueType;
    int lineno;

};