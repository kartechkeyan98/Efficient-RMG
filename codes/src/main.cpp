#include<iostream>
#include<vector>

// self libraries
#include<rmg.h>

int main(void){
    // size of matrix
    int n;
    std::cin>>n;

    // the two vectors
    std::vector<std::vector<int> >A(n,std::vector<int>(n,-1));
    std::vector<std::vector<int> >T(n,std::vector<int>(n,-1));

    // linked list to store available cols
    list<int>ls;
    for(int i=0;i<n;++i){
        ls.insert(n-i-1,0);
    }
    std::cout<<ls<<std::endl;

    // rng
    std::random_device rd;
    std::mt19937 mt(rd());                                         // seeded rng
    std::uniform_int_distribution<int> distro(0,1);                // distribution

    // step-1: Generate the two matrices L and U
    generate(
        A,T,
        n,0,
        ls,
        mt,distro
    );

    // step-2: Multiply L&U and get your answer, bitch!
    std::vector<std::vector<int> >R(n,std::vector<int>(n,0));     // actual random matrix to be generated
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            for(int k=0;k<n;++k)R[i][j] = (R[i][j]+(A[i][k]*T[k][j]))%2;
        }
    }

    std::cout<<std::endl;

    std::cout<<"A\n";
    std::cout<<A<<std::endl;
    std::cout<<std::endl;

    std::cout<<"T\n";
    std::cout<<T<<std::endl;
    std::cout<<std::endl;

    std::cout<<"R\n";
    std::cout<<R<<std::endl;

    

}