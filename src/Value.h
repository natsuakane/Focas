#pragma once

#include <string>
#include "ValueType.h"
#include "Exceptions.h"

struct Value {
public:
    Value(long v, int lineno) {
        valueType = Integer;
        value.longValue = v;
        this->lineno = lineno;
    }
    Value(char v, int lineno) {
        valueType = CharNum;
        value.charValue = v;
        this->lineno = lineno;
    }
    Value(double v, int lineno) {
        valueType = Float;
        value.doubleValue = v;
        this->lineno = lineno;
    }
    Value(std::string& v, int lineno) {
        valueType = StrVal;
        value.strValue = new std::string(v);
        this->lineno = lineno;
    }
    Value(void* v, int lineno) {
        valueType = PtrVal;
        value.ptrValue = v;
        this->lineno = lineno;
    }

    long GetLong() {
        if(valueType != Integer) throw std::runtime_error(UnsuitableType("Integer", ValueTypeNames[valueType], lineno));
        return value.longValue;
    }
    char GetChar() {
        if(valueType != CharNum) throw std::runtime_error(UnsuitableType("Char", ValueTypeNames[valueType], lineno));
        return value.charValue;
    }
    double GetDouble() {
        if(valueType != Float) throw std::runtime_error(UnsuitableType("Float", ValueTypeNames[valueType], lineno));
        return value.doubleValue;
    }
    std::string GetStr() {
        if(valueType != StrVal) throw std::runtime_error(UnsuitableType("String", ValueTypeNames[valueType], lineno));
        return *value.strValue;
    }
    void* GetPtr() {
        if(valueType != PtrVal) throw std::runtime_error(UnsuitableType("Pointer", ValueTypeNames[valueType], lineno));
        return value.ptrValue;
    }

    ValueType GetValueType() {
        return valueType;
    }

    ~Value() {
        if (valueType == StrVal) {
            delete value.strValue;
        }
    }

private:
    union ValueUnion {
        long longValue;
        char charValue;
        double doubleValue;
        std::string* strValue;
        void* ptrValue;

        ValueUnion() {

        }

        ~ValueUnion() {

        }
    } value;

    ValueType valueType;
    int lineno;

};