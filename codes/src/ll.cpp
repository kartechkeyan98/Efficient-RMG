#include<iostream>
#include<linked_list.h>
using namespace std;

int main(void){
    list<int>ls;
    bool leave=false;
    while(!leave){
        cout<<"Linked List Main Menu:\n";
        cout<<"- Insert element ['i']\n";
        cout<<"- Delete element ['r']\n";
        cout<<"- Access element ['a']\n";
        cout<<"- Print List ['p']\n";
        cout<<"- Print Number of elements ['s']\n";
        cout<<"- Exit ['x']\n";

        char c;
        cin>>c;

        if(c=='i'){
            cout<<"\nenter location to insert[0-idx]: ";
            int k;
            cin>>k;

            int dat;
            cout<<"enter value to insert: ";
            cin>>dat;

            ls.insert(dat,k);
        }
        else if(c == 'r'){
            cout<<"\nenter location to delete[0-idx]: ";
            int k;
            cin>>k;

            ls.remove(k);
        }
        else if(c=='a'){
            cout<<"\nenter location to access[0-idx]: ";
            int k;
            cin>>k;

            cout<<ls[k]<<endl;
        }
        else if(c=='p'){
            cout<<ls<<endl;
        }
        else if(c=='s'){
            cout<<ls.size()<<endl;
        }
        else if(c=='x')break;
        
        cout<<endl;

    }
}