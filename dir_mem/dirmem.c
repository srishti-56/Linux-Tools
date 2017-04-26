#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int dirStat(char *dirn) {
	DIR *dptr = NULL;
	dptr = opendir(dirn);
	if(dptr == NULL) {
		printf("Could not open directory\n");
		return -1;
	}
	chdir(dirn);
	
	struct dirent *dent;
	int dir_dskusg = 0;

	printf("\n  Name\t\t\t\tSize (b)");
	printf("\n__________________________________________");
	while( (dent = readdir(dptr)) != NULL) {
		if( !strcmp(dent->d_name, ".") || !strcmp(dent->d_name, ".." )) {
			continue;
		}
		struct stat tmp_stat_str;
		stat(dent->d_name, &tmp_stat_str);
		dir_dskusg += tmp_stat_str.st_size;
		if(tmp_stat_str.st_mode & S_IFDIR)
			printf("\n%20.20s/\t|\t%jd", dent->d_name, tmp_stat_str.st_size);
		else 
			printf("\n%20.20s\t|\t%jd", dent->d_name, tmp_stat_str.st_size);
	}
	char cwd[1024] = "";
	getcwd(cwd, 1024);
	printf("\n\nTotal disk usage by %s: %db\n\n\n", cwd, dir_dskusg);

	closedir(dptr);
	
	free(dent);
	dptr = NULL;
	dent = NULL;
	return 0;
}

int main(int argc, char* argv[]) {
	
	if( argc != 2 ) {
		printf("Argument: relative or absolute path to directory\n");
		return -1;
	}

	char *dirname = argv[1];

	if(!strcmp(dirname, ".")) {
		getcwd(dirname, 1024);
	}
	
	struct stat stat_str;
	stat(dirname, &stat_str);
	
	switch( S_IFMT & stat_str.st_mode) {
		case S_IFDIR:
			if( ! dirStat(dirname) ) return -1;
			break;
		default: 
			printf("Argument: relative or absoulte path to directory\n"); return -1;
	}

	dirname = NULL;
	return 0;
}
