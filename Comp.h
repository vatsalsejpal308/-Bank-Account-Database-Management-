#ifndef COMP_H
#define COMP_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Comp : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    Comp();
    
//private:
    int size , capacity;
    std::vector<int> kTop;
    std::vector<Account> bankStorage1d_1;
    std::vector<Account> bankStorage1d_2;
    const std::vector<int> primes = {31 , 37 , 41};

    void saveBal(int bal);
    void saveBal(int bal , int count);
    void removeBal(int bal);
    int hashFunction(std::string id , int prime);
    
};

#endif // COMP_H
