#include "test.h" 

int main(int argc, char *argv[]){
    int option = 0;
    int pass_name = 1;  

    while (pass_name < argc) {
        if (argv[pass_name][0] == '-') {
            for (int j = 1; argv[pass_name][j]; j++) {
                switch (argv[pass_name][j]) {
                    case 'a':
                        a = 1;
                        break;
                    case 'l':
                        l = 1;
                        break;
                    case 'R':
                        R = 1;
                        break;
                    case 't':
                        t = 1;
                        break;
                    case 'r':
                        r = 1;
                        break;
                    case 'i':
                        i = 1;
                        break;
                    case 's':
                        s = 1;
                        break;
                    default:
                        break;
                }
            }
        }
        else{
            printf("%s:\n", argv[pass_name]);
            major(argv[pass_name]);
            option = 1;
        }

        pass_name++; 
    }

    if (!option) {
        major((char *)"."); 
        option = 1; 
    }

    return 0;
}
