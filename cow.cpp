#include <iostream>

#include "datahandler.h"

using namespace std;

// Пример использования нашего умного DataHandler`a в другом
// классе. У вас его будет использовать MyString.
class DataUser 
{
public:
    void read() const {dataHandler->read();}
    void write() {dataHandler->write();}

private:
    DataHandler dataHandler;
};

int main()
{
    // Ничего не происходит, у нас же ленивая инициализация.
    DataUser du1; 
    
    // Создали данные и обратились к ним на чтение.
    du1.read(); 
    
    // Привязываемся к созданным данным.
    DataUser du2(du1);
    
    // Новые данные не создаются, т. к. обращение на чтение.
    du2.read();

    // Идет обращение на запись, поэтому сначала создаем себе
    // копию.
    du2.write();
}

// Вывод:
// Data created
// Data read() 
// Data read() 
// Data copied
// Data write() 
// Data deleted
// Data deleted
