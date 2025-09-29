#include "Functions.h"

int main(int argc, char* argv[]){

    for(int i = 0; i < argc; i++){
        Print(argv[i]);
    }

    system("pause");

    return 0;
};