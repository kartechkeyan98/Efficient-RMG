#pragma once
#include<iostream>
#include<vector>
#include<random> 

// my own
#include<linked_list.h>


void generate(
    std::vector<std::vector<int> > &A, std::vector<std::vector<int> > &T,           // matrices A and T
    int n, int i,                                                                   // n: size of A and T, i: stage of recursion[0-idx]
    list<int> &ls,                                                                  // which columns are available to use
    std::mt19937 &rng,                                                              // this is the random number generator, already seeded
    std::uniform_int_distribution<int> &distro                                      // distribution we will be using to generate prn s                                             
){
    if(i==n-1){
        // only one element left now

        // 1. obtain which column is available in last row. 
        int c = ls.head()->data;   // access the available column
        A[i][c] = 1;               // assign 1 to it
        
        // 2. assign random value to T[c,c]
        int rdm= distro(rng);       // variable to store random number
        while(rdm == 0){
            rdm = distro(rng);
        }
        T[c][c] = rdm;              // assign non-0 value to T[c,c]

        ls.remove(0);               // remove the last element
        return;
    }

    std::vector<int> v(n-i);        // in i-th stage we want random assignment of size n-i

    // 1. generating random non-zero vector
    bool flag=false;        
    int r=-1;
    int r_abs=-1;
    while(!flag){
        node<int>* t=ls.head();
        for(int j=0;j<ls.size();++j){
            v[j] = distro(rng);             // random number
            if(!flag&&v[j]!=0){                    
                flag=true;
                r=j;                        // first non-zero column, relative
                r_abs=t->data;              // first non-zero column, absolute
            }
            t=t->next;
        }
    }

    // 2. assign A[i,:] = e_r
    node<int>* t=ls.head();
    for(int j=0;j<ls.size();j++){
        // t->data contains the index[0-idx] of the j-th available column
        if(j==r)A[i][t->data] = 1;
        else A[i][t->data] = 0;
        t=t->next;
    }
    // for column elements below first non-0 element, assign random values
    for(int j=i+1;j<n;j++)A[j][r_abs]=distro(rng);

    // 3. assign values to T
    /**
     * 3a. T[r_abs,:] = v
     */
    t=ls.head();
    for(int j=0;j<ls.size();++j){
        T[r_abs][t->data] = v[j];
        t=t->next;
    }
    
    /**
     * 3b. Modify the r_abs-th column of T by setting 0 above and below
     */
    t = ls.head();
    for(int j=0;j<ls.size();j++){
        if(t->data!=r_abs)T[t->data][r_abs]=0;
        t=t->next;
    }

    // 4. remove r-th element from list of available columns
    ls.remove(r);

    // go for this
    generate(
        A,T,
        n,i+1,
        ls,
        rng, distro
    );
    return;
}



template<typename T>
std::ostream& operator<<(std::ostream& out,std::vector<std::vector<T> >& V){
    int m=V.size(), n=V[0].size();
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)out<<V[i][j]<<" ";
        out<<std::endl;
    }
    return out;
}