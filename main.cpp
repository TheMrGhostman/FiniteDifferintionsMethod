//
//  main.cpp
//  FiniteDifferintionsMethod
//
//  Created by Matej Zorek on 04.04.18.
//  Copyright © 2018 Matej Zorek. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

void vypis(double *pole, int delka){
    cout <<endl;
    for(int i = 0; i < delka; i++){
        cout << pole[i] << " ";
    }
    cout <<endl;
}

int main() {
    int m;
    double h;
    double a = 0.2;
    double b = 0.8;
    double *u;
    double *p;
    double *q;
    double f = 0;
    
    
    cout <<"Zadejte počet kroků metody (m)." <<endl << "m: ";
    cin >>m;
    m=m+1;
    u = new double[m];
    cout <<"Zadejte počáteční a koncovou podmínku." <<endl <<"y(0.2) = " ;
    cin >> u[0];
    cout <<"y(0.8) = " ;
    cin >>u[m-1];
    
    h = (b-a)/(m-1);

    p = new double[m];
    q = new double[m];
    
    // p = -(exp(-x)/x)
    // q = +(exp(-x)/x * (2/x -2))
    // x = a+jh
    

    for(int i = 0; i < m; i++){
        if(i == 0){
            p[i] = 0;
            continue;
        }
        p[i] = -exp(-(a+i*h))/(a+i*h);
    }
    //cout <<"p = ";
    //vypis(p, m);
    
    for(int i = 0; i < m; i++){
        if(i == 0 || i == m-1){
            q[i] = 0;
            continue;
        }
        q[i] = (exp(-(a+i*h))/(a+i*h))*(2/(a+i*h) - 2);
    }
    //cout <<"q = ";
    //vypis(q, m);
    
    double *A,*B,*C;
    A = new double[m-1];
    B = new double[m-1];
    C = new double[m-1];
    for(int i = 0; i < m-1 ; i++){
        A[i] = -p[i]/(h*h);
        B[i] = -p[i+1]/(h*h);
        C[i] = -(p[i]+p[i+1])/(h*h) -q[i];
    }
    //vypis(A,m-1);
    //vypis(B,m-1);
    //vypis(C,m-1);
    
    double *alpha,*beta;
    alpha = new double[m];
    beta = new double[m];
    
    alpha[0] = 0;
    alpha[1] = 0;
    beta[0] = 0;
    beta[1] = -u[0];
    
    for(int i = 1; i < m-1; i++){
        alpha[i+1] = B[i]/(C[i]-alpha[i]*A[i]);
        beta[i+1] = (beta[i]*A[i]-f)/(C[i] - alpha[i]*A[i]);
    }
    //vypis(alpha,m);
    //vypis(beta, m);
    
    for(int i = m-2; i >= 0; i--){
        u[i] = alpha[i+1]*u[i+1] - beta[i+1];
    }
    vypis(u, m);
    

    ofstream myfile;
    myfile.open ("/Users/Ghosty/Documents/XCode - programy/FiniteDifferintionsMethod/FiniteDifferintionsMethod/output.txt");
    for(int i= 0 ;i < m ;i++){
        myfile << a+i*h <<"\t" << u[i]<< endl;
    }
    myfile.close();
    
    delete [] p;
    delete [] q;
    delete [] A;
    delete [] B;
    delete [] C;
    delete [] alpha;
    delete [] beta;
    delete [] u;

    return 0;
}
