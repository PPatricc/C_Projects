#include <stdio.h>
#include "circular_buffer.h"

int main() {
    printf("Podaj rozmiar bufora: ");
    int Rozm;
    if(scanf("%d",&Rozm)!=1){
        printf("Incorrect input");
        return 1;
    }
    if(Rozm<=0){
        printf("Incorrect input data");
        return 2;
    }
    struct circular_buffer_t *Bufor;
    int x= circular_buffer_create_struct(&Bufor,Rozm);
    if(x==2){
        printf("Failed to allocate memory");
        return 8;
    }
    int errC;
    for(;;){
        printf("Co chcesz zrobic? ");
        int WhatTodo;
        if(scanf("%d",&WhatTodo)!=1){
            printf("Incorrect input");
            circular_buffer_destroy_struct(&Bufor);
            return 1;
        }
        if(WhatTodo==0){
            break;
        }
        else if(WhatTodo!=1 && WhatTodo!=2 && WhatTodo!=3 && WhatTodo!=4 && WhatTodo!=5 && WhatTodo!=6){
            printf("Incorrect input data\n");
        }
        switch (WhatTodo) {
            case 1 :
                printf("Podaj liczbe");
                int Toadd;
                if(scanf("%d",&Toadd)!=1){
                    circular_buffer_destroy_struct(&Bufor);
                    printf("Incorrect input");
                    return 1;
                }
                circular_buffer_push_back(Bufor,Toadd);
                break;

            case 2:
                if(circular_buffer_empty(Bufor)==1){
                    printf("Buffer is empty\n");
                    break;
                }else{
                    printf("%d\n",circular_buffer_pop_back(Bufor,&errC));
                    break;
                }

            case 3:
                if(circular_buffer_empty(Bufor)==1){
                    printf("Buffer is empty\n");
                    break;
                }
                else{
                    printf("%d\n",circular_buffer_pop_front(Bufor,&errC));
                    break;
                }


            case 4:
                if(circular_buffer_empty(Bufor)==1){
                    printf("Buffer is empty");
                    break;
                }
                circular_buffer_display(Bufor);
                printf("\n");
                break;

            case 5:
                printf("%d\n",circular_buffer_empty(Bufor));
                break;

            case 6:
                printf("%d\n",circular_buffer_full(Bufor));
                break;

            default:break;
        }

    }
    circular_buffer_destroy_struct(&Bufor);

    return 0;
}