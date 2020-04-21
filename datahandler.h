#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <iostream>

using namespace std;

// Отвечает за хранение, создание и удаление наших ресурсов.
// Указатель на выделенный буфер, размер строки и тд. - все тут.
class Data
{
public:
    Data() {cout << "Data created\n";} // выделяем память
    Data(const Data&) {cout << "Data copied\n";} // делаем полную копию
    ~Data() {cout << "Data deleted\n";} // подчищаем

    void read() const {cout << "Data read() \n";}
    void write() {cout << "Data write() \n";}
};

// Отвечает за разделение ресурсов и ленивую инициализацию.
class DataHandler
{
public:
    DataHandler() = default;
    // Если у h есть данные, привязываемся к ним,
    // не забываем про счетчик ссылок. Можно еще по аналогии оператор "="
    // перегрузить.
    DataHandler(const DataHandler &h);
    // Если держим данные, уменьшаем счетчик ссылок, если больше никто на
    // эти данные не ссылается - удаляем.
    ~DataHandler();

    // Убеждаемся, что данные есть и спокойно возвращаем.
    const Data *operator ->() const;
    // Убеждаемся, что данные уникальны и спокойно возвращаем.
    Data *operator ->();

    //для себя

private:
    mutable int *refCounter = nullptr; // указатель на счетчик ссылок
    mutable Data *data = nullptr;

    // Проверяем, держим ли мы данные, если нет - создаем.
    void ensureInitialized() const;
    // Проверяем, что на эти данные (если они вообще есть) никто кроме
    // нас не ссылается, если нет - создаем себе копию.
    void ensureUnique();
};

#endif
