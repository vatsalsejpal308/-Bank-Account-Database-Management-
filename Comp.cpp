#include "Comp.h"

Comp::Comp(){
    size = 0;
    capacity = 100000;

    Account temp;
    temp.id = "";
    temp.balance = -1;

    bankStorage1d = std::vector<Account>(capacity , temp);
    bankStorage1d_1 = std::vector<Account>(capacity , temp);
    bankStorage1d_2 = std::vector<Account>(capacity , temp);
}

void Comp::createAccount(std::string id, int count) {
    Account newAccount;
    newAccount.id = id;
    newAccount.balance = count;

    saveBal(count);

    int key1 = hashFunction(id , primes[0]) , key2 = hashFunction(id , primes[1]) , key3 = hashFunction(id , primes[2]);

    if(bankStorage1d[key1].id == ""){
        bankStorage1d[key1] = newAccount;
    }else{
        if(bankStorage1d_1[key2].id == ""){
            bankStorage1d_1[key2] = newAccount;
        }else{
            int ind = 0;
            while(bankStorage1d_2[(key3 + 19 * ind * ind + 7) % capacity].id != "" && bankStorage1d_2[(key3 + 167 * ind) % capacity].id != ""){
                ind++;
            }
            if(bankStorage1d_2[(key3 + 19 * ind * ind + 7) % capacity].id == ""){
                bankStorage1d_2[(key3 + 19 * ind * ind + 7) % capacity] = newAccount;
            }else{
                bankStorage1d_2[(key3 + 167 * ind) % capacity] = newAccount;
            }
        }
    }

    size++;

}

std::vector<int> Comp::getTopK(int k) {
    std::vector<int> kBalances;
    for(int i = 0 ; i < std::min(k, static_cast<int>(kTop.size())) ; i++){
        kBalances.push_back(kTop[i]);
    }

    return kBalances;
}

int Comp::getBalance(std::string id) {
    if(!doesExist(id)){
        return -1;
    }else{
        int key1 = hashFunction(id , primes[0]) , key2 = hashFunction(id , primes[1]) , key3 = hashFunction(id , primes[2]);
        if(bankStorage1d[key1].id == id){
            return bankStorage1d[key1].balance;
        }else{
            if(bankStorage1d_1[key2].id == id){
                return bankStorage1d_1[key2].balance;
            }else{
                int ind = 0;
                while(bankStorage1d_2[(key3 + ind) % capacity].id != id){
                    ind++;
                }
                key3 = (key3 + ind) % capacity;
                return bankStorage1d_2[key3].balance;
            }
        }
    }
}

void Comp::addTransaction(std::string id, int count) {
    if(!doesExist(id)){
        createAccount(id , count);
    }else{
        int key1 = hashFunction(id , primes[0]) , key2 = hashFunction(id , primes[1]) , key3 = hashFunction(id , primes[2]);
        if(bankStorage1d[key1].id == id){
            saveBal(bankStorage1d[key1].balance , count);
            bankStorage1d[key1].balance += count;
        }else{
            if(bankStorage1d_1[key2].id == id){
                saveBal(bankStorage1d_1[key2].balance , count);
                bankStorage1d_1[key2].balance += count;
            }else{
                int ind = 0;
                while(bankStorage1d_2[(key3 + ind) % capacity].id != id){
                    ind++;
                }
                key3 = (key3 + ind) % capacity;
                saveBal(bankStorage1d_2[key3].balance , count);
                bankStorage1d_2[key3].balance += count;
            }
        }
    }

}

bool Comp::doesExist(std::string id) {
    int key1 = hashFunction(id , primes[0]) , key2 = hashFunction(id , primes[1]) , key3 = hashFunction(id , primes[2]);

    if(bankStorage1d[key1].id == id){
            return true;
        }else{
            if(bankStorage1d_1[key2].id == id){
                return true;
            }else{
                int ind = 0;
                while(bankStorage1d_2[(key3 + ind) % capacity].id != id && ind < capacity){
                    ind++;
                }
                key3 = (key3 + ind) % capacity;
                return (bankStorage1d_2[key3].id == id);
            }
        }

}

bool Comp::deleteAccount(std::string id) {
    if(!doesExist(id)){
        return false;
    }else{
        int key1 = hashFunction(id , primes[0]) , key2 = hashFunction(id , primes[1]) , key3 = hashFunction(id , primes[2]);
        if(bankStorage1d[key1].id == id){
            removeBal(bankStorage1d[key1].balance);
            bankStorage1d[key1].id = "";
            bankStorage1d[key1].balance = -1;

        }else{
            if(bankStorage1d_1[key2].id == id){
                removeBal(bankStorage1d_1[key2].balance);
                bankStorage1d_1[key2].id = "";
                bankStorage1d_1[key2].balance = -1;
            }else{
                int ind = 0;
                while(bankStorage1d_2[(key3 + ind) % capacity].id != id){
                    ind++;
                }
                key3 = (key3 + ind) % capacity;
                removeBal(bankStorage1d_2[key3].balance);
                bankStorage1d_2[key3].id = "";
                bankStorage1d_2[key3].balance = -1;
            }
        }
        size--;
        return true;
    }
    
}
int Comp::databaseSize() {
    return size;
}

int Comp::hash(std::string id) {
    int hashValue = hashFunction(id , primes[0]);
    return hashValue;
}

void Comp::saveBal(int bal){
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


void Comp::saveBal(int bal , int count){
    removeBal(bal);
    saveBal(bal + count);
}

void Comp::removeBal(int bal){
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

int Comp::hashFunction(std::string id , int prime){
    int hashValue = 0;

    for(int i = 0 ; i < id.length() ; i++){
        hashValue = (hashValue * prime + id.at(i)) % capacity;
    }

    return hashValue;
}