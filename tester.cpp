#include <bits/stdc++.h>
#include "BaseClass.h"
#include "Chaining.h"
#include "Chaining.cpp"
#include "LinearProbing.h"
#include "LinearProbing.cpp"
#include "QuadraticProbing.h"
#include "QuadraticProbing.cpp"
#include "CubicProbing.h"
#include "CubicProbing.cpp"
#include "Comp.h"
#include "Comp.cpp"

using namespace std;
BaseClass *Bank;
void test(){
    ifstream fin("test1.txt");
    int command;
    string accName;
    int accBalance,accBalance2,transactionAmount;
    int kValue,rKValue;
    vector<int> TopKBalances;
    string s1,s2;
    int deletionResult1,deletionResult2,accExists;
    
    int casesTested=0;
    while(fin>>command){
        switch(command){
            case 1:
                fin>>accName>>accBalance;
                Bank->createAccount(accName,accBalance);
                fin>>accBalance2;
                if(Bank->getBalance(accName)!=accBalance){
                    cout<<"FAILED on creating account "<<accName<<" with balance "<<accBalance<<endl;
                    cout<<"On retreving balance on "<<accName<<" expected "<<accBalance2<<" but found "<<Bank->getBalance(accName)<<endl;
                }
                casesTested++;
                break;
            case 2:
                fin>>accName>>transactionAmount;
                Bank->addTransaction(accName,transactionAmount);
                fin>>accBalance2;
                if(Bank->getBalance(accName)!=accBalance2){
                    cout<<"FAILED on adding transaction to "<<accName<<" an amount "<<transactionAmount<<endl;
                    cout<<"Final balance on "<<accName<<" expected "<<accBalance2<<" but found "<<Bank->getBalance(accName)<<endl;
                }
                casesTested++;
                break;
            case 4:
                fin>>kValue;
                fin>>rKValue;
                TopKBalances=Bank->getTopK(kValue);
                if(rKValue!=TopKBalances.size()){
                    cout<<"FAILED on geiing top K balances"<<endl;
                    cout<<"Expected length of vector "<<rKValue<<" but found "<<TopKBalances.size()<<endl;
                }
                else{
                    sort(TopKBalances.rbegin(),TopKBalances.rend());
                    s1="";
                    s2="";
                    for(int i=0;i<rKValue;i++){
                        s1+=to_string(TopKBalances[i])+" ";
                        fin>>accBalance;
                        s2+=to_string(accBalance)+" ";
                    }
                    if(s1!=s2){
                        cout<<"FAILED on getting top K balances"<<endl;
                        cout<<"Expected top K balances "<<s2<<endl;
                        cout<<"Found "<<s1<<endl;
                    }
                }
                casesTested++;
                break;
            case 5:
                fin>>accName;
                fin>>accBalance;
                if(accBalance!=Bank->getBalance(accName)){
                    cout<<"FAILED to get acc balance of acc "<<accName<<endl;
                    cout<<"Expected balance "<<accBalance<<" but found "<<Bank->getBalance(accName)<<endl;
                }
                casesTested++;
                break;
            case 6:
                fin>>accName;
                fin>>deletionResult1;
                deletionResult2=Bank->deleteAccount(accName);
                if(deletionResult1&&!deletionResult2 || !deletionResult1&&deletionResult2){
                    cout<<"FAILED in deletion of account "<<accName<<endl;
                    cout<<"Expected "<<deletionResult1<<" but found "<<deletionResult2<<endl;
                    cout<<"1 is true and 0 is false"<<endl;
                }
                casesTested++;
                break;
            case 8:
                fin>>accName;
                fin>>accBalance;
                accExists=Bank->doesExist(accName);
                if(accBalance&&!accExists || !accBalance&&accExists){
                    cout<<"FAILED in doesExist "<<accName<<endl;
                    cout<<"Expected "<<accBalance<<" but found "<<accExists<<endl;
                    cout<<"1 is true and 0 is false"<<endl;
                }
                casesTested++;
                break;
            case 9:
                fin>>accBalance;
                if(Bank->databaseSize()!=accBalance){
                    cout<<"FAILED total database size"<<endl;
                    cout<<"Expected "<<accBalance<<" but found "<<Bank->databaseSize()<<endl;
                }
                casesTested++;
                break;
        }
        if(casesTested%10000==0){
            cout<<casesTested<<" OK"<<endl;
        }
    }
    cout<<"CasesTested "<<casesTested<<endl;
   }


int main() {
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cout<<"How may commands do you want to test with?: ";
    cout.flush();
    int commandCount;
    cin>>commandCount;
    string commandToGeneratedTestCase="py generateTests.py "+to_string(commandCount)+" > test1.txt";
    system(&commandToGeneratedTestCase[0]);
    cout<<"what part of your code do you want to test?\n1->chaining\n2->linearProbin\n4->quadraticProbing\n8->cubicProbing\n16->compPart\n";
    cout<<"Enter the number as sum of parts you want to test (like it would be 31 to test all): ";
    cout.flush();
    int toTest;
    cin>>toTest;
    cout<<endl;
    cout<<"CasesTested may not match with the number of commands asked, its just to know that actually some testing happened, if its very small like 0 then something went wrong"<<endl;
    cout<<endl;
    cout<<"If program is not ending it means your code might be stuck in an infinite Loop"<<endl;
    cout<<endl;
    if(toTest&1){
        cout<<"STARTING WITH CHAINING"<<endl;
        Bank=new Chaining;
        test();
        cout<<"DONE WITH CHAINING"<<endl;
    }
    if(toTest&2){
        cout<<"STARTING WITH LinearProbing"<<endl;
        Bank=new LinearProbing;
        test();
        cout<<"DONE WITH LinearProbing"<<endl;
    }
    if(toTest&4){
        cout<<"STARTING WITH QuadraticProbing"<<endl;
        Bank=new QuadraticProbing;
        test();
        cout<<"DONE WITH QuadraticProbing"<<endl;
    }
    if(toTest&8){
        cout<<"STARTING WITH CubicProbing"<<endl;
        Bank=new CubicProbing;
        test();
        cout<<"DONE WITH CubicProbing"<<endl;
    }
    if(toTest&16){
        cout<<"STARTING WITH Comp"<<endl;
        Bank=new Comp;
        test();
        cout<<"DONE WITH Comp"<<endl;
    }
    cout<<"Do you want to clean up the test cases file generated?(y/n):"<<endl;
    cout.flush();
    string r;
    cin>>r;
    if(r=="Y" || r=="y")
        system("del test1.txt");
    
    cout<<"DONE"<<endl;


    
    return 0;
}