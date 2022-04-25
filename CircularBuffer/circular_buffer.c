#include "circular_buffer.h"
#include <stdio.h>
#include <stdlib.h>



int circular_buffer_create(struct circular_buffer_t *a, int N){
    if(a==NULL || N<=0) return 1;
    
    a->ptr=(int*)malloc(N*sizeof(int));
    
    if(a->ptr==NULL) return 2;
    
    a->begin=0;
    a->end=0;
    a->capacity=N;
    a->full=0;
    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N){

    if(cb==NULL || N<=0) return 1;
    
    *cb=malloc(sizeof(struct circular_buffer_t));
    
    if(*cb==NULL) return 2;
    
    if(circular_buffer_create(*cb,N)!=0){
        free(*cb);
        return 2;
    }

    return 0;

}

void circular_buffer_destroy(struct circular_buffer_t *a){
    if(a==NULL||a->ptr==NULL) return;
    
    free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a){
    if(a==NULL) return;
    
    circular_buffer_destroy(*a);
    free(*a);
}


int circular_buffer_push_back(struct circular_buffer_t *cb, int value){
    if(cb==NULL || cb->ptr==NULL || cb->capacity<=0||cb->end<0 || cb->begin<0 || cb->begin>=cb->capacity || cb->end>=cb->capacity){
        return 1;
    }
    *(cb->ptr+cb->end)=value;
    cb->end++;
    if(cb->full==1) cb->begin+=1;
    
    if(cb->end>=cb->capacity) cb->end=0;
    
    if(cb->begin==cb->capacity) cb->begin=0;
    
    if(cb->end==cb->begin) cb->full=1;
    
    return 0;
}
int circular_buffer_empty(const struct circular_buffer_t *a) {
    if (a==NULL||a->ptr==NULL|| a->end < 0 || a->begin < 0 || a->capacity <= 0 || a->end >= a->capacity || a->begin >= a->capacity) return -1;

    if ( a->end==a->begin&& a->full==0) return 1;

    else return 0;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code){
    if(a==NULL||a->ptr==NULL||a->begin<0||a->end<0||a->capacity<1||a->end>=a->capacity|| a->begin>=a->capacity){
        
        if(err_code!=NULL) *err_code=1;
        return 1;
    }
    if(err_code!=NULL){
        if(circular_buffer_empty(a)==1) *err_code=2;
        else *err_code=0;
    }
    a->full=0;
    int Toreturn = *(a->ptr+a->begin);
    a->begin++;
    
    if(a->capacity==a->begin) a->begin=0;
    
    return Toreturn;
}
int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code){
    if(a==NULL||a->ptr==NULL||a->begin<0||a->end<0||a->capacity<1||a->end>=a->capacity|| a->begin>=a->capacity){
        if(err_code!=NULL) *err_code=1;
        
        return 1;
    }
    int flag=0;
    int Toreturn;
    if(err_code!=NULL){
        if(circular_buffer_empty(a)==1) *err_code=2;
        
        else *err_code=0;
        
    }

    if(a->end){
        Toreturn = *(a->ptr+a->end-1);
        flag=1;
    }
    else Toreturn = *(a->ptr+a->capacity-1);
    
    a->full=0;
    if(flag==1) a->end-=1;
    
    else a->end=a->capacity-1;
    
    return Toreturn;
}


int circular_buffer_full(const struct circular_buffer_t *a){
    if(a==NULL||a->ptr==NULL||a->begin<0||a->end<0||a->capacity<1||a->end>=a->capacity|| a->begin>=a->capacity){
        return -1;
    }
    return a->full;
}

void circular_buffer_display(const struct circular_buffer_t *a){
    if(a==NULL||a->ptr==NULL||a->begin<0||a->end<0||a->capacity<=0||a->end>=a->capacity|| a->begin>=a->capacity){
        return ;
    }
    else{
        if(circular_buffer_full(a)==1){
            for(int i=a->begin;i<a->capacity;i++){
                printf("%d ",*(a->ptr+i));
            }
            for(int k=0;k<a->end;k++){
                printf("%d ",*(a->ptr+k));
            }
        }
        else{
            for(int i=a->begin;i<a->end;i++){
                printf("%d ",*(a->ptr+i));
            }
        }
    }
}