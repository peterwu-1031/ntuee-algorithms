//
//  main.cpp
//  Algorithms
//
//  Created by 吳育丞 on 2021/9/22.
//
#include <fstream>
#include <iostream>
using namespace std;

void help_message() {
    cout << "usage: ./mps <input file name> <output file name>" << endl;
}

void find_chords(int i, int j, int** M, int* chords, fstream &fout) {
    if(i<j) {
        if(i>chords[j] || chords[j]>j) {
            find_chords(i, j-1, M, chords, fout);
        }
        else if(chords[j] == i) {
            fout << i << " " << j << endl;
            find_chords(i+1, j-1, M, chords, fout);
        }
        else {
            int k = chords[j];
            if(M[i][j] == (M[i][k-1]+M[k+1][j]+1)) {
                find_chords(i, k-1, M, chords, fout);
                fout << k << " " << j << endl;
                find_chords(k+1, j-1, M, chords, fout);
            }
            else {
                find_chords(i, j-1, M, chords, fout);
            }
        }
    }
}

int maxPlanarSubset(int i, int j, int** M, int* chords) {
    if(M[i][j]<0) {
        if(i>=j) {
            M[i][j] = 0;
        }
        else if(i>chords[j] || chords[j]>j) {
            M[i][j] = maxPlanarSubset(i, j-1, M, chords);
        }
        else if(chords[j] == i) {
            M[i][j] = maxPlanarSubset(i+1, j-1, M, chords)+1;
        }
        else {
            int k = chords[j];
            M[i][j] = maxPlanarSubset(i, k-1, M, chords)+maxPlanarSubset(k+1, j, M, chords)+1;
            if(M[i][j]<maxPlanarSubset(i, j-1, M, chords)) {
                M[i][j] = M[i][j-1];
            }
        }
    }
    return M[i][j];
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
       help_message();
       return 0;
    }
    
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int num, point1, point2;
    fin >> num;
    int* chords = new int[num];
    while (fin >> point1 >> point2) {
        chords[point1] = point2;
        chords[point2] = point1;
    }
    
    int** M = new int*[num];
    for(int i=0; i<num; i++) {
        M[i] = new int[num];
        for(int j=0; j<num; j++){
            M[i][j] = -1;
        }
    }
    
    //max_num of chords
    fout << maxPlanarSubset(0, num-1, M, chords) << endl;
    //find chords
    find_chords(0, num-1, M, chords, fout);
    
    delete[] chords;
    for(int i=0; i<num; i++) {
        delete[] M[i];
    }
    delete[] M;
    
    fin.close();
    fout.close();
    
    return 0;
}
