#include <unistd.h>
#include <stdio.h>
#include "MyMalloc.h"
__thread struct tcache_t m_tcache;
__thread int tcache_is_initialized=0;


static void init_tcache(){
    tcache_is_initialized=1;
    pthread_t id=pthread_self()%NARENAS;
    pthread_mutex_lock(&g_lock);
    if(!arena_is_initialized[id]){
        init_arena(id);
    }
    pthread_mutex_unlock(&g_lock);
    pthread_mutex_lock(&g_arena[id]->mutex);
    int n2=g_arena[id]->t_thread;
    if(n2<=3) {

    }else if(arena_is_initialized[(id+NARENAS-1)%NARENAS]){
        int ret=pthread_mutex_trylock(&g_arena[(id+NARENAS-1)%NARENAS]->mutex);
        if(ret==0){
            int n1=g_arena[(id+NARENAS-1)%NARENAS]->t_thread;
            if(n1<=n2-3){
                m_tcache.n_arena=(id+NARENAS-1)%NARENAS;
                g_arena[(id+NARENAS-1)%NARENAS]->t_thread++;
                pthread_mutex_unlock(&g_arena[(id+NARENAS-1)%NARENAS]->mutex);
            }else{
                m_tcache.n_arena=(id+NARENAS)%NARENAS;
                g_arena[(id+NARENAS)%NARENAS]->t_thread++;
            }
   
        }else if(arena_is_initialized[(id+NARENAS+1)%NARENAS]){ // 左边被锁了
            int ret2=pthread_mutex_trylock(&g_arena[(id+NARENAS+1)%NARENAS]->mutex);
                if(ret2==0){
                    int n3=g_arena[(id+NARENAS+1)%NARENAS]->t_thread;
                    if(n3<=n2-3){
                        m_tcache.n_arena=(id+NARENAS+1)%NARENAS;
                        g_arena[(id+NARENAS+1)%NARENAS]->t_thread++;
                        pthread_mutex_unlock(&g_arena[(id+NARENAS+1)%NARENAS]->mutex);
                    }
                    else{
                        m_tcache.n_arena=(id+NARENAS)%NARENAS;
                        g_arena[(id+NARENAS)%NARENAS]->t_thread++;
                    }
                }else{ // 右边也被锁了
                    m_tcache.n_arena=(id+NARENAS)%NARENAS;
                    g_arena[(id+NARENAS)%NARENAS]->t_thread++;
                }
        }else{
            m_tcache.n_arena=(id+NARENAS)%NARENAS;
            g_arena[(id+NARENAS)%NARENAS]->t_thread++;
        }
    }
    pthread_mutex_unlock(&g_arena[id]->mutex);
    void* addr=(void*)mmap(NULL,1024,PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(addr==(void*)-1){
        fprintf(stderr,"init tcache fail\n");
        exit(-1);
    }
    size_t1 tcache_addr=init_bin(1,NTBINS,m_tcache.bins,(size_t1)addr,3);
    m_tcache.bitmap=(size_t1)0;
}

static void init_arena(pthread_t id){
    arena_is_initialized[id]=1;
    void* addr=(void*)mmap(NULL,MAX_ARENA_SIZE,PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if(addr==(void*)-1){
        fprintf(stderr,"init_arena fail\n");
        exit(-1);
    }
    g_arena[id]=(struct arena*)addr;
    g_arena[id]->t_thread=1;
    g_arena[id]->unsorted_bin=NULL;
    size_t1 small_bin_end_addr=init_bin(9,NBINS,g_arena[id]->small_bins,
                                        ALIGN_UP_8_BYTES((size_t1)((char*)addr+sizeof(struct arena))),1);
    small_bin_end_addr=ALIGN_UP_N_BYTES(small_bin_end_addr,1024);
    g_arena[id]->large_bin=(struct Chunk*)small_bin_end_addr;
    g_arena[id]->large_bin->prev=NULL;
    g_arena[id]->large_bin->next=NULL;
    //g_arena[id]->large_bin->prev_size=0;
    g_arena[id]->large_bin->size=MAX_LARGE_BIN;
    g_arena[id]->top_chunk=(struct Chunk*)(small_bin_end_addr+MAX_LARGE_BIN);
    g_arena[id]->top_chunk->next=NULL;
    g_arena[id]->top_chunk->prev=NULL;
    //g_arena[id]->top_chunk->prev_size=0;
    g_arena[id]->top_chunk->size=(size_t1)(addr+MAX_ARENA_SIZE-small_bin_end_addr-MAX_LARGE_BIN);
}

/*
addr arena
end of arena
space
begin at small bin
end at small bin
space 
begin at large bin
end at large bin
begin at top bin
topchunk
*/
static size_t1 init_bin(int a,int size,struct Chunk** chunk,size_t1 addr,int num){
    if(num==1){
        for(int i=0;i<size;i++){
        //
            int m_size=a+i*8;
            struct Chunk* m_chunk=(struct Chunk*)addr;
            //m_chunk->prev_size=0;
            m_chunk->size=Chunk_metasize+m_size;
            m_chunk->next=NULL;
            m_chunk->prev=NULL;
            addr=addr+m_chunk->size;
            chunk[i]=m_chunk;
        }   
    }else{
        for(int i=0;i<size;i++){
            int m_size=a+i*8;
            struct Chunk* m_chunk_head=(struct Chunk*)addr;
            m_chunk_head->size=Chunk_metasize+m_size;
            m_chunk_head->next=NULL;
            m_chunk_head->prev=NULL;
            addr=addr+m_chunk_head->size;
            chunk[i]=m_chunk_head;


            for(int j=1;j<num;j++){
                struct Chunk* m_chunk=(struct Chunk*)addr;
                m_chunk->size=NULL;
                m_chunk->next=NULL;
                m_chunk->prev=m_chunk_head;
                m_chunk_head=m_chunk;
                addr=addr+m_chunk->size;
            }


        }
    }
    
    return addr;
}

void* my_malloc(size_t size){
    if(!tcache_is_initialized){
        init_tcache();
    }
}
void my_free(void* ptr){

}
int main(){
    int a[2];
    a[0]=1;
    a[1]=2;
    return 0;
}