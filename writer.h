#ifndef WRITER_H
#define WRITER_H
#pragma once

#include <string>
#include <iostream>


///
/// \brief The Writer class
/// Абстрактный класс отвечающий за вывод сообщений путем вызова метода Write.
///
class Writer
{
public:
    virtual ~Writer() = default;
    virtual void Write(std::string message) = 0;
};


///
/// \brief The ConsoleWriter class
/// Реализация класса Write, отвечающая за вывод сообщения на консоль.
class ConsoleWriter: public Writer
{
public:
    void Write(std::string message = "") override;
};

#endif // WRITER_H
