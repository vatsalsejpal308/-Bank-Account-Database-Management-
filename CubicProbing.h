#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>

class CubicProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    CubicProbing();
    
private:
    int size , capacity;
    std::vector<int> kTop;
    const std::vector<int> primes = {31 , 37 , 41};

    void saveBal(int bal);
    void saveBal(int bal , int count);
    void removeBal(int bal);
    int hashFunction(std::string id , int prime);
    
};

#endif // CUBICPROBING_H
