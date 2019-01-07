#ifndef CTR_H
#define CTR_H

#include <stdio.h>
#include <dirent.h>

#define MB     1024*1024
#define BYTE   unsigned char
#define BOOL   char
#define TRUE   1
#define FALSE -1

#define CONFIG_FILEPATH "ctr.xlsx"

long int fsize(FILE* f);
long int fsizes(const char* filename);
BOOL fexists(const char* filename);
BOOL is_filepath_target(const char* filepath, const char* prefix_pattern);
long int calc_start(long int size);
void corrupt(const char* filepath);

#endif