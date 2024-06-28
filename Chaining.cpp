#include "Chaining.h"

Chaining::Chaining(){
    size = 0;
    capacity = 100000;

    Account temp;
    temp.id = "";
    temp.balance = -1;

    bankStorage2d = std::vector<std::vector<Account>>(capacity);
}

void Chaining::createAccount(std::string id, int count) {
    Account newAccount;
    newAccount.id = id;
    newAccount.balance = count;

    bankStorage2d[hash(id)].push_back(newAccount);
    saveBal(count);
    size++;
}

std::vector<int> Chaining::getTopK(int k) {
    std::vector<int> kBalances;
    for(int i = 0 ; i < std::min(k, static_cast<int>(kTop.size())) ; i++){
        kBalances.push_back(kTop[i]);
    }

    return kBalances;
}

int Chaining::getBalance(std::string id) {
    int key = hash(id);
    for(int i = 0 ; i < bankStorage2d[key].size() ; i++){
        if(bankStorage2d[key][i].id == id){
            return bankStorage2d[key][i].balance;
        }
    }

    return -1;
}

void Chaining::addTransaction(std::string id, int count) {
    if(!doesExist(id)){
        createAccount(id , count);
    }else{
        int key = hash(id);
        for(int i = 0 ; i < bankStorage2d[key].size() ; i++){
            if(bankStorage2d[key][i].id == id){
                saveBal(bankStorage2d[key][i].balance , count);
                bankStorage2d[key][i].balance += count;
                break;
            }
        }
    }

}

bool Chaining::doesExist(std::string id) {
    int key = hash(id);
    for(int i = 0 ; i < bankStorage2d[key].size() ; i++){
        if(bankStorage2d[key][i].id == id){
            return true;
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id) {
    if(!doesExist(id)){
        return false;
    }else{
        int key = hash(id) , ind = 0;
        for(int i = 0 ; i < bankStorage2d[key].size() ; i++){
            if(bankStorage2d[key][i].id == id){
                ind = i;
                break;
            }
        }
        removeBal(bankStorage2d[key][ind].balance);
        bankStorage2d[key].erase(bankStorage2d[key].begin() + ind);
        size--;
        return true;
    }

}
int Chaining::databaseSize() {
    return size;
}

int Chaining::hash(std::string id) {
    int hashValue = hashFunction(id , primes[0]);
    return hashValue;
}

void Chaining::saveBal(int bal){
    if(kTop.empty()){
        kTop.push_back(bal);
        return;
    }else{
        int s = 0, e = kTop.size() - 1, mid;
        while(s <= e){
            mid = s + (e - s) / 2;
            if(kTop[mid] >= bal){
                s = mid + 1;
            }else{
                e = mid - 1;
            }
        }

        if(s == kTop.size()){
            kTop.push_back(bal);
        }else{
            kTop.insert(kTop.begin() + s, bal);
        }
    }
}


void Chaining::saveBal(int bal , int count){
    removeBal(bal);
    saveBal(bal + count);
}

void Chaining::removeBal(int bal){
    int s = 0 , e = kTop.size() - 1 , mid;
    while(s <= e){
        mid = s + (e - s) / 2;
        if(kTop[mid] == bal){
            kTop.erase(kTop.begin() + mid);
            break;
        }else if(kTop[mid] < bal){
            e = mid - 1;
        }else{
            s = mid + 1;
        }
    }
}

int Chaining::hashFunction(std::string id , int prime){
    int hashValue = 0;

    for(int i = 0 ; i < id.length() ; i++){
        hashValue = (hashValue * prime + id.at(i)) % 100000;
    }

    return hashValue;
}