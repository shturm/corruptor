#include <string.h>
#include "ctr.h"

int filter(const struct dirent *d)
{ 
	if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) return 0;
	
	return 1;
}

int main(int argc, char const *argv[])
{

	// todo while(1)

	FILE* fconf = fopen("ctr.xlsx", "r");

	char* target_dir[512]; // target dir read from ctr.xlsx
	char* pattern_prefix[128]; // 20190101
	fgets(target_dir, 512, fconf);
	fgets(pattern_prefix, 512, fconf);
	// printf("%s\n", target_dir); //
	fclose(fconf);
	if (!fexists(target_dir)) return 0;

	printf("target_dir is %s\n", target_dir);

	struct dirent **eps;
	int n = scandir (target_dir, &eps, filter, alphasort); // dirent: alphasort
	if (n >= 0)
	{
		int cnt;
		char filepath[1024];
		for (cnt = 0; cnt < n; ++cnt)
		{
			// printf("%s\n", eps[cnt]->d_name); 
			strcpy(filepath, target_dir);
			strcat(filepath, eps[cnt]->d_name);
			// corrupt(eps[cnt]->d_name);
			if (FALSE == is_filepath_target(filepath, pattern_prefix)) continue;
			corrupt(filepath);
			// printf("corrupting %s\n", filepath);
		}
	} else {
		perror ("Couldn't open the directory");
		printf("%s\n", target_dir);
	}
	
	return 0;
}