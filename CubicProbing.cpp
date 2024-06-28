#include "CubicProbing.h"

CubicProbing::CubicProbing(){
    size = 0;
    capacity = 250000;

    Account temp;
    temp.id = "";
    temp.balance = -1;

    bankStorage1d = std::vector<Account>(capacity , temp);
}

void CubicProbing::createAccount(std::string id, int count) {

    Account newAccount;
    newAccount.id = id;
    newAccount.balance = count;

    saveBal(count);

    int key = hash(id) , ind = 0;
    while(bankStorage1d[(key + 167 * ind * ind * ind + 13) % capacity].id != ""){
        ind++;
    }
    key = (key + 167 * ind * ind * ind + 13) % capacity;

    bankStorage1d[key] = newAccount;
    size++;

}

std::vector<int> CubicProbing::getTopK(int k) {
    std::vector<int> kBalances;
    for(int i = 0 ; i < std::min(k, static_cast<int>(kTop.size())) ; i++){
        kBalances.push_back(kTop[i]);
    }

    return kBalances;
}

int CubicProbing::getBalance(std::string id) {
    if(!doesExist(id)){
        return -1;
    }else{
        int key = hash(id) , ind = 0;
        while(bankStorage1d[(key + ind) % capacity].id != id){
            ind++;
        }
        key = (key + ind) % capacity;

        return bankStorage1d[key].balance;
    }

}

void CubicProbing::addTransaction(std::string id, int count) {
    if(!doesExist(id)){
        createAccount(id , count);
    }else{
        int key = hash(id) , ind = 0;
        while(bankStorage1d[(key + ind) % capacity].id != id){
            ind++;
        }
        key = (key + ind) % capacity;

        saveBal(bankStorage1d[key].balance , count);
        bankStorage1d[key].balance += count;
    }

}

bool CubicProbing::doesExist(std::string id) {
    int key = hash(id);
    for(int i = 0 ; i < capacity ; i++){
        if(bankStorage1d[(key + i) % capacity].id == id){
            return true;
        }
    }

    return false;
}

bool CubicProbing::deleteAccount(std::string id) {
    if(!doesExist(id)){
        return false;
    }else{
        int key = hash(id) , ind = 0;
        while(bankStorage1d[(key + ind) % capacity].id != id){
            ind++;
        }
        key = (key + ind) % capacity;

        removeBal(bankStorage1d[key].balance);

        bankStorage1d[key].id = "";
        bankStorage1d[key].balance = -1;

        size--;

        return true;
    }
}
int CubicProbing::databaseSize() {
    return size;
}

int CubicProbing::hash(std::string id) {
    int hashValue = hashFunction(id , primes[0]);

    return hashValue;
}

void CubicProbing::saveBal(int bal){
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


void CubicProbing::saveBal(int bal , int count){
    removeBal(bal);
    saveBal(bal + count);
}

void CubicProbing::removeBal(int bal){
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

int CubicProbing::hashFunction(std::string id , int prime){
    int hashValue = 0;

    for(int i = 0 ; i < id.length() ; i++){
        hashValue = (hashValue * prime + id.at(i)) % capacity;
    }

    return hashValue;
}