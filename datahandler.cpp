#include <iostream>
#include "datahandler.h"

using namespace std;

DataHandler::DataHandler(const DataHandler &h)
{
    if(h.data == nullptr)
        return;

    data = h.data;
    refCounter = h.refCounter;
    (*refCounter)++;
}

DataHandler& DataHandler::operator=(const DataHandler &h)
{
    if(h.data == nullptr)
    return *this;

    data = h.data;
    refCounter = h.refCounter;
    (*refCounter)++;

    return *this;
}

DataHandler::~DataHandler()
{
    if (data == nullptr)
        return;

    (*refCounter)--;

    if((*refCounter) == 0)
    {
        delete refCounter;
        delete data;
    }
}

Data* DataHandler::operator ->()
{
    ensureUnique();
    return data;
}

const Data* DataHandler::operator ->() const
{
    ensureInitialized();
    return data;
}

void DataHandler::ensureInitialized() const
{
    if (data == nullptr)
    {
      data = new Data;
      refCounter = new int(1);
    }
}

void DataHandler::ensureUnique()
{
    ensureInitialized();

    if (*refCounter > 1)
    {
        (*refCounter)--;
        data = new Data(*data);
        refCounter = new int(1);
    }
}



