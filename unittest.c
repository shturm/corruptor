#include "ctr.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <dirent.h>

unsigned int testcase_count = 0;

// testcase
void test(const char* testName, void (*f)())
{
	testcase_count++;
	printf("===   TEST: %s ===\n", testName);
	f();
	printf("=== //TEST: %s ===\n\n", testName);
}

void test_is_filepath_target()
{
	assert(FALSE == is_filepath_target("", ""));
	assert(FALSE == is_filepath_target("somedir", ""));
	assert(FALSE == is_filepath_target("somedir/", ""));
	assert(FALSE == is_filepath_target("somedir/somefile", ""));
	assert(FALSE == is_filepath_target("somedir/somefile.txt", ""));
	assert(FALSE == is_filepath_target("somedir/somefile.xlsx", ""));
	assert(FALSE == is_filepath_target("somedir/somefile.mp3.xlsx", ""));
	assert(TRUE  == is_filepath_target("somedir/somefile.mp3.xlsx.mp3", ""));
	assert(TRUE  == is_filepath_target("somedir/somefile.mp3", ""));

	assert(FALSE == is_filepath_target("I:\\", ""));
	assert(FALSE == is_filepath_target("I:\\somedir", ""));
	assert(FALSE == is_filepath_target("I:\\somedir\\otherdir", ""));
	assert(FALSE == is_filepath_target("I:\\somedir\\otherdir\\somefile", ""));
	assert(FALSE == is_filepath_target("I:\\somedir\\otherdir\\somefile.xlsx", ""));
	assert(FALSE == is_filepath_target("I:\\somedir\\otherdir\\somefile.xlsx.mp3.txt", ""));
	assert(FALSE == is_filepath_target("I:\\somedir\\otherdir\\somefile.xlsx.mp", ""));
	assert(TRUE  == is_filepath_target("I:\\somedir\\otherdir\\somefile.mp3", ""));
	assert(TRUE  == is_filepath_target("somefile.mp3", ""));
	assert(TRUE  == is_filepath_target("somedir\\somefile.mp3", ""));
	assert(TRUE  == is_filepath_target("somedir\\OTHER\\somefile.mp3", ""));

	//////////////////////////

	assert(TRUE  == is_filepath_target("somedir/20190101.mp3", "20190101"));
	assert(TRUE  == is_filepath_target("somedir/2019010199999999.mp3", "20190101"));
	assert(FALSE  == is_filepath_target("somedir/20200101.mp3", "20190101"));
}

void test_demo_strstr()
{
	printf("strstr('abcd','c'): %s\n", strstr("abcd", "c")); // "cd"
	printf("strstr('abcd','z'): %s\n", strstr("abcd", "z")); // null
}

int filter(const struct dirent *d)
{ 
	if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) return 0;

	return 1;
}

void test_dirent()
{
	struct dirent **eps;
	int n = scandir ("./", &eps, filter, alphasort); // dirent: alphasort
	if (n >= 0)
	{
		int cnt;
		for (cnt = 0; cnt < n; ++cnt)
			printf("%s\n", eps[cnt]->d_name); 
	}
	else
	perror ("Couldn't open the directory");
}

void test_calc_start()
{	
	assert(-1 == calc_start(0));
	assert(-1 == calc_start(1));
	assert(-1 == calc_start(720));

	assert(1*MB > calc_start(721));	
	assert(1*MB > calc_start(1*MB));
	assert(1*MB+1 > calc_start(2*MB));
	assert(1*MB > calc_start(3*MB));
	assert(1*MB > calc_start(4*MB));
	
	assert(2*MB == calc_start(5*MB));
	assert(2*MB == calc_start(6*MB));
	assert(2*MB == calc_start(7*MB));
	assert(2*MB == calc_start(8*MB));
	assert(2*MB == calc_start(9*MB));
	assert(2*MB == calc_start(10*MB));
	
	assert(2*MB == calc_start(11*MB));
	assert(2*MB == calc_start(12*MB));
	assert(2*MB == calc_start(13*MB));
	assert(2*MB == calc_start(14*MB));
	assert(2*MB == calc_start(15*MB));
	assert(2*MB == calc_start(16*MB));
	assert(2*MB == calc_start(17*MB));
	assert(2*MB == calc_start(18*MB));
	assert(2*MB == calc_start(19*MB));
	
	assert(4*MB == calc_start(20*MB));
	assert(4*MB == calc_start(25*MB));
	assert(4*MB == calc_start(30*MB));
	assert(4*MB == calc_start(40*MB));
	assert(4*MB == calc_start(49*MB));
	
	assert(8*MB == calc_start(50*MB));
	assert(8*MB == calc_start(100*MB));
}

int main(int argc, char const *argv[])
{
	test("strstr(...)", test_demo_strstr);
	test("test_is_filepath_target()", test_is_filepath_target);
	test("test_dirent()", test_dirent);
	test("test_calc_start()", test_calc_start);

	printf("TESTCASES: %d\n", testcase_count);
	return 0;
}