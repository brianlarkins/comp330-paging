/*
 * @file lab5.h - Lab 5 Virtual Memory Replacement Simulator
 * @author D. Brian Larkins (c) 2019
 */

#define MAXPAGES 1024

typedef enum { AllocEq, AllocProp } alloc_t;
typedef enum { EvictFIFO, EvictSecond, EvictLRU, EvictLFU } evict_t;
typedef enum { ReplacementGlobal, ReplacementLocal } local_t;

struct access_s {
  int pid;
  int addr;
};
typedef struct access_s access_t;

struct ptable_s {
  int inframe; // in memory or not?
  int ts;      // timestamp when frame was added to memory (FIFO)
  int refbit;  // reference for second chance
  int refts;   // timestamp when frame was last referenced (LRU)
  int rcount;  // timestamp when frame was last referenced (LFU)
};
typedef struct ptable_s ptable_t;

struct proc_s {
  int       faults;    // # page faults
  int       accesses;  // # total mem accesses
  int       memsize;   // size of virtual memory
  int       nframes;   // # frames allocated
  int       nfree;     // # frames available
  int       npages;    // # pages (memsize / gbl.pagesize)
  int       cursor;    // saved index for second-chance
  ptable_t  pt[MAXPAGES];
};
typedef struct proc_s proc_t;

struct global_s {
  int        memsize;         // size of main memory
  int        pagesize;        // page size
  alloc_t    alloc;           // allocate proportionally/equally?
  evict_t    evict;           // eviction strategy
  local_t    replacement;     // local or global eviction?
  int        period;          // display quantum
  int        gscpid;          // saved pid for global replacement second-chance
  int        nproc;           // # processes
  proc_t     procs[10];       // process information
  int        naccess;         // # accesses in trace
  int        debug;           // debug level
  access_t  *trace;           // process trace
  FILE      *outfp;           // output file pointer (ptable.txt)
};
typedef struct global_s global_t;
