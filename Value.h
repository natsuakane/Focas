#pragma once

#include <string>
#include "ValueType.h"
#include "Exceptions.h"

struct Value {
public:
    Value(long v, int lineno) {
        valueType = Integer;
        longValue = v;
        this->lineno = lineno;
    }
    Value(char v, int lineno) {
        valueType = CharNum;
        charValue = v;
        this->lineno = lineno;
    }
    Value(double v, int lineno) {
        valueType = Float;
        doubleValue = v;
        this->lineno = lineno;
    }
    Value(void* v, int lineno) {
        valueType = PtrVal;
        ptrValue = v;
        this->lineno = lineno;
    }

    long GetLong() {
        if(valueType != Integer) throw std::runtime_error(UnsuitableType("Integer", ValueTypeNames[valueType], lineno));
        return longValue;
    }
    char GetChar() {
        if(valueType != CharNum) throw std::runtime_error(UnsuitableType("Char", ValueTypeNames[valueType], lineno));
        return charValue;
    }
    double GetDouble() {
        if(valueType != Float) throw std::runtime_error(UnsuitableType("Float", ValueTypeNames[valueType], lineno));
        return doubleValue;
    }
    void* GetPtr() {
        if(valueType != PtrVal) throw std::runtime_error(UnsuitableType("Pointer", ValueTypeNames[valueType], lineno));
        return ptrValue;
    }

    ValueType GetValueType() {
        return valueType;
    }

    ~Value() {

    }

private:
    union {
        long longValue;
        char charValue;
        double doubleValue;
        void* ptrValue;
    };

    ValueType valueType;
    int lineno;

};