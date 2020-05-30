#ifndef WRITER_H
#define WRITER_H
#pragma once

#include <string>
#include <iostream>

class Writer
{
public:
    virtual ~Writer() = default;
    virtual void Write(std::string message) = 0;
};

class ConsoleWriter: public Writer
{
public:
    void Write(std::string message = "") override;
};

#endif // WRITER_H
