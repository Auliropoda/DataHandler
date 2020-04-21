#include <iostream>
#include "datahandler.h"

using namespace std;

DataHandler::DataHandler(const DataHandler &h)
{
   data = h.data;
    refCounter = h.refCounter;

    if (refCounter  && *refCounter != 0)
        (*refCounter)++;
}

DataHandler::~DataHandler()
{
    if (refCounter == nullptr)
        return;

    (*refCounter)--;

    if((*refCounter) == 0)
    {
        delete refCounter;
        delete data;
    }
    refCounter = 0;
    data = 0;
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
    if((*refCounter) != 1)
    {
        Data coppy(*data);
        (*refCounter)--;
    }

}



