#include <iostream>
#include "datahandler.h"

using namespace std;

DataHandler::DataHandler(const DataHandler &h)
{
    if (data == h.data)
        return;
    if (h.data == nullptr)
        return;
    if (h.refCounter == nullptr)
        return;

    (*h.refCounter)--;

    if((*h.refCounter) == 0)
    {
        delete h.refCounter;
        delete h.data;
    }

    data = h.data;
    refCounter = h.refCounter;
    (*refCounter)++;
}

DataHandler::~DataHandler()
{
    if (refCounter == nullptr)
        return;

    (refCounter)--;

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

        Data temp;
        *data = temp;
    }
}



