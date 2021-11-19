
/*
 * @file lab5.c - Lab 5 Virtual Memory Replacement Simulator
 * @author your name (c) 2021
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lab5.h"

// global state
global_t gbl;

void process_params(int argc, char **argv);
int  evict(int pid);
int  evict_min(int pid);
int  evict_fifo(int pid);
int  evict_second(int pid);
int  evict_lru(int pid);
int  evict_lfu(int pid);
void reset_refbits();
void dump_ptable(int timestep);



/*
 * process_args - process command-line arguments and process files
 * @param argc - argument count
 * @param argv - array of argumenet strings
 */
void process_params(int argc, char **argv) {
  FILE *plist, *ptrace, *outfp;
  int pid, msize, count = 0;
  char ch;

  if (argc != 7) {
    fprintf(stderr, "usage: %s [memsize] [pagesize] [alloc] [eviction] [replacement] [period]\n", argv[0]);
    fprintf(stderr, "      memsize  - size of physical memory in bytes\n");
    fprintf(stderr, "      pagesize - size of pages/frames in bytes \n");
    fprintf(stderr, "      alloc:\n");
    fprintf(stderr, "          0 - equal allocation\n");
    fprintf(stderr, "          1 - proportional allocation\n");
    fprintf(stderr, "      eviction:\n");
    fprintf(stderr, "          0 - FIFO page replacement:\n");
    fprintf(stderr, "          1 - second chance replacement:\n");
    fprintf(stderr, "          2 - LRU replacement\n");
    fprintf(stderr, "          3 - LFU replacement\n");
    fprintf(stderr, "      replacement:\n");
    fprintf(stderr, "          0 - global replacement\n");
    fprintf(stderr, "          1 - local replacement\n");
    exit(1);
  }

  // process command-line args
  gbl.memsize  = atoi(argv[1]);
  gbl.pagesize = atoi(argv[2]);
  gbl.period   = atoi(argv[6]);

  // allocation algorithm
  switch(atoi(argv[3])) {
    case 0:
      gbl.alloc = AllocEq;
      break;
    case 1:
      gbl.alloc = AllocProp;
      break;
    default:
      fprintf(stderr, "allocation algorithm must be 0 (equal) or 1 (proportional)\n");
      exit(1);
      break;
  }

  // eviction algorithm
  switch(atoi(argv[4])) {
    case 0:
      gbl.evict = EvictFIFO;
      break;
    case 1:
      gbl.evict = EvictSecond;
      break;
    case 2:
      gbl.evict = EvictLRU;
      break;
    case 3:
      gbl.evict = EvictLFU;
      break;
    default:
      fprintf(stderr, "allocation algorithm must be 0 (equal) or 1 (proportional)\n");
      exit(1);
      break;
  }

  // global vs. local replacement
  switch(atoi(argv[5])) {
    case 0:
      gbl.replacement = ReplacementGlobal;
      break;
    case 1:
      gbl.replacement = ReplacementLocal;
      break;
    default:
      fprintf(stderr, "allocation algorithm must be 0 (equal) or 1 (proportional)\n");
      exit(1);
      break;
  }

  // read process information
  plist = fopen("plist.txt", "r");
  if (!plist) {
    perror("plist fopen");
    exit(1);
  }

  fscanf(plist, "%d", &gbl.nproc);

  for (int i=0; i < gbl.nproc; i++) {
    fscanf(plist, "%d %d", &pid, &msize);
    // now have process i's memory size in msize
    // ADD CODE TO SAVE PROCESS MEMORY SIZE
  }

  fclose(plist);

  ptrace = fopen("ptrace.txt", "r");
  if (!ptrace) {
    perror("ptrace fopen");
    exit(1);
  }


  // count total # of accesses
  while ((ch = fgetc(ptrace)) != EOF) {
    if (ch == '\n') count++;
  }
  gbl.naccess = count;

  // now read them into an array
  rewind(ptrace);

  gbl.trace = calloc(count, sizeof(access_t));
  if (!gbl.trace) {
    perror("trace alloc");
    exit(1);
  }

  for (int cur = 0; cur < count; cur++) {
    fscanf(ptrace, "%d %d", &gbl.trace[cur].pid, &gbl.trace[cur].addr);
  }

  fclose(ptrace);

  printf("*****************************************************\n");
  printf("memsize   : %13d   pagesize: %12d   period     : %8d  nframes: %d\n",
      gbl.memsize, gbl.pagesize, gbl.period, gbl.memsize/gbl.pagesize);
  printf("allocation: %13s   eviction: %12s   replacement: %8s\n",
      gbl.alloc == AllocEq ? "equal" : "proportional",
      gbl.evict == EvictFIFO ? "FIFO"  :
                               (gbl.evict == EvictSecond ? "SecondChance" :
                                                           (gbl.evict == EvictLRU ? "LRU" : "LFU")),
      gbl.replacement == ReplacementGlobal ? "global" : "local");

  printf("trace contains %d memory accesses\n", count);

  if (gbl.period == 0) {
    outfp = NULL;
  } else {
    outfp = fopen("ptable.txt", "w");
    if (!outfp) {
      perror("output file");
      exit(1);
    }
  }
}



/*
 * evict - evict the best candidate page from those resident in memory
 * @param pid the process requesting eviction
 * @returns 1 if frame stolen from another process, 0 otherwise
 */
int  evict(int pid) {
  evict_t evict = EvictFIFO; // you need to fix this with your own way to trace eviction scheme

  switch (evict) {
    case EvictFIFO:
      // call FIFO eviction function here
      return 0;
      break;
    case EvictSecond:
      // call 2nd chance eviction function here
      return 0;
      break;
    case EvictLRU:
      // call LRU eviction function here
      return 0;
      break;
    case EvictLFU:
      // call LFU eviction function here
      return 0;
      break;
  }
  return -1;
}



/**
 * main
 */
int main(int argc, char **argv) {

  process_params(argc, argv);

  // calculate #pages per process

  // allocate frames to each process

  // process memory trace using replacement strategy
  //for (int ts=0; ts < naccess; ts++) {
  //
  //}
}
