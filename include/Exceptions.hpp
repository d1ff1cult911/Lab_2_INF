#pragma once
#include <stdexcept>

class IndexOutOfRange : public std::out_of_range {
public:
    IndexOutOfRange() : std::out_of_range("Index out of range") {}
};