#pragma once
#define NTBINS 10
#define NBINS  56
#define NARENAS 5
#define MAX_FAST 64
#define MAX_SMALL_BIN 512
#define MAX_LARGE_BIN 4096
#define MAX_ARENA_SIZE 24*1024
#define Chunk_metasize sizeof(struct Chunk)
#define PAGE 4*1024
#include<pthread.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

#define ALIGN_UP_N_BYTES(size,n)  ((((size)+(n)-1)/(n))*(n))
#define ALIGN_UP_8_BYTES(size) ALIGN_UP_N_BYTES(size, 8)
#define ALIGN_UP_1KB(size) ALIGN_UP_N_BYTES(size, 1024)

typedef unsigned long size_t1;
static int arena_is_initialized[NARENAS];
//pthread_mutex_t arena_lock[NARENAS];
static pthread_mutex_t g_lock;
struct Chunk{       
    //size_t1 prev_size;
    size_t1 size; // 最后一位是否使用，倒数第二位mmap分配，倒数第三个是否主分区,这个是加上meta数据的总大小
    struct Chunk* prev;
    struct Chunk* next;
    
};
// 空闲的Chunk 8+8+8=24B

struct arena{
    size_t1 t_thread; // 记录多少个线程指向现在的线程 
    pthread_mutex_t mutex;
    struct Chunk* small_bins[NBINS]; // 每个是一个
    //[8*9,8*10.....8*64]
    struct Chunk* large_bin;// 先分配1K
    struct Chunk* unsorted_bin;// 初始化为0
    struct Chunk* top_chunk;
}; // 一共是 8+sizeof(lock)+(8*56) +(8*73*28)+1024  
    // 分配24k


struct tcache_t{
    //struct arena* arena_ptr; // 指向一个arena
    int n_arena;// 指向全局变量g_arena
    struct Chunk*  bins[NTBINS];
    //[8*1....8*10]
    // 每个bin有3个缓存，一共三十个
    size_t1 bitmap;
    // 32位用来标志bin是否使用了
};  // 一共是8+30*16+(8*55)+8=8+480+440+8=928+8=936B

struct arena* g_arena[NARENAS];
void* my_malloc(size_t);
void  my_free(void*);
void  realloc(void*);
static void init_malloc();
static void init_arena(pthread_t i);
static void init_tcache();
//inline static size_t1 Align(size_t1);
static size_t1 init_bin(int a,int size,struct Chunk** chunk,size_t1 addr,int num); // a代表第一个的大小,num是每一个分配几个chunk 