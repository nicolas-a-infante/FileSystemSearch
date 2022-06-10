#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Functions based on the code provided in the project description with some modifications since that code did not work as intended

// Print path names of every file and directory within 'testdir'
void read_sub1 (char *sub_dir) {
	DIR *sub_dp = opendir(sub_dir);
	struct dirent *sub_dirp;
	struct stat buf;
	char temp1[] = ".";
	char temp2[] = "..";
	char temp3[] = "/";

	//read the directory contents
	if (sub_dp != NULL) {
		while ((sub_dirp = readdir(sub_dp)) != NULL) {
			
			//ensure the current file or directory being viewed isnt '.' or '..' to prevent infinite recursion
			char *temp = sub_dirp->d_name;
			if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) {
				//write out the full path
				char *temp_sub = malloc(sizeof(char) * 2000);
				temp_sub = strcpy(temp_sub, temp3);
				temp_sub = strcat(temp_sub, temp);

				char *temp_full_path = malloc(sizeof(char) * 2000);
				temp_full_path = strcpy(temp_full_path, sub_dir);
				temp_full_path = strcat(temp_full_path, temp_sub);

				printf ("%s\n", temp_full_path);

				//search using recursion
				DIR *subsubdp = opendir(temp_full_path);
				if (subsubdp != NULL) {
					closedir(subsubdp);
					read_sub1(temp_full_path);
				}
			}
		}
		
		closedir(sub_dp);
	}
	else {
		printf ("Cannot open directory\n");
		exit (2);
	}
}














//given command line argument -name and <file-name>, find a file's path based on its file-name
void read_sub2_1 (char *sub_dir, char *file_name, int _del) {
	DIR *sub_dp = opendir(sub_dir);
	struct dirent *sub_dirp;
	struct stat buf;
	char temp1[] = ".";
	char temp2[] = "..";
	char temp3[] = "/";

	//read contents of a directory
	if (sub_dp != NULL) {
		while ((sub_dirp = readdir(sub_dp)) != NULL) {
			char *temp = sub_dirp->d_name;
			//ensure the file or directory is not '.' or '..' to prevent infinite recursion
			if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) {
				//create the file path name
				char *temp_sub = malloc(sizeof(char) * 2000);
				temp_sub = strcpy(temp_sub, temp3);
				temp_sub = strcat(temp_sub, temp);

				char *temp_full_path = malloc(sizeof(char) * 2000);
				temp_full_path = strcpy(temp_full_path, sub_dir);
				temp_full_path = strcat(temp_full_path, temp_sub);

				//logic to check condition whether the name matches the CLA
				if (strcmp(sub_dirp->d_name, file_name) == 0) {
					printf ("%s\n", temp_full_path);
					if (_del) remove(temp_full_path); //delete the file if the _del flag is set to true
				}

				//search using recursion
				DIR *subsubdp = opendir(temp_full_path);
				if (subsubdp != NULL) {
					closedir(subsubdp);
					read_sub2_1(temp_full_path, file_name, _del);
				}
			}
		}
		
		closedir(sub_dp);
	}
	else {
		printf ("Cannot open directory\n");
		exit (2);
	}
}












//given command line arguments -mmin and <mod-time>, print the path for a file or directory with <mod-time> condition
void read_sub2_2 (char *sub_dir, char *mod_time, int _del) {
	DIR *sub_dp = opendir(sub_dir);
	struct dirent *sub_dirp;
	struct stat buf;
	char temp1[] = ".";
	char temp2[] = "..";
	char temp3[] = "/";

	//read directory contents
	if (sub_dp != NULL) {
		while ((sub_dirp = readdir(sub_dp)) != NULL) {
			char *temp = sub_dirp->d_name;
			//ensure the directory is not '.' or '..' to prevent infinite recursion
			if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) {
				//create path name
				char *temp_sub = malloc(sizeof(char) * 2000);
				temp_sub = strcpy(temp_sub, temp3);
				temp_sub = strcat(temp_sub, temp);

				char *temp_full_path = malloc(sizeof(char) * 2000);
				temp_full_path = strcpy(temp_full_path, sub_dir);
				temp_full_path = strcat(temp_full_path, temp_sub);

				//logic checking whether the file matches the correct mod-time
				if (stat(temp_full_path, &buf) == 0) {
					if (*mod_time == '-') {
						if ((time(NULL) - buf.st_mtime)/60 < atoi(mod_time+1)) {
							printf ("%s\n", temp_full_path);
							if (_del) remove(temp_full_path); //delete the file if the _del flag is set to true
						}
					}
					else if (*mod_time == '+') {
						if ((time(NULL) - buf.st_mtime)/60 > atoi(mod_time+1)) {
							printf ("%s\n", temp_full_path);
							if (_del) remove(temp_full_path); //delete the file if the _del flag is set to true
						}
					}
					else {
						if ((time(NULL) - buf.st_mtime)/60 == atoi(mod_time)) {
							printf ("%s\n", temp_full_path);
							if (_del) remove(temp_full_path); //delete the file if the _del flag is set to true
						}
					}
				}

				//search using recursion
				DIR *subsubdp = opendir(temp_full_path);
				if (subsubdp != NULL) {
					closedir(subsubdp);
					read_sub2_2(temp_full_path, mod_time, _del);
				}
			}
		}
		
		closedir(sub_dp);
	}
	else {
		printf ("Cannot open directory\n");
		exit (2);
	}
}



















//given the command line arguments -inum and <i-node> search for a file with that i-node
void read_sub2_3 (char *sub_dir, int i_node, int _del) {
	DIR *sub_dp = opendir(sub_dir);
	struct dirent *sub_dirp;
	struct stat buf;
	char temp1[] = ".";
	char temp2[] = "..";
	char temp3[] = "/";

	//read directory contents
	if (sub_dp != NULL) {
		while ((sub_dirp = readdir(sub_dp)) != NULL) {
			char *temp = sub_dirp->d_name;
			//ensure the directory is not '.' or '..' to prevent infinite recursion
			if (strcmp(temp, temp1) != 0 && strcmp(temp, temp2) != 0) {
				//create path name
				char *temp_sub = malloc(sizeof(char) * 2000);
				temp_sub = strcpy(temp_sub, temp3);
				temp_sub = strcat(temp_sub, temp);

				char *temp_full_path = malloc(sizeof(char) * 2000);
				temp_full_path = strcpy(temp_full_path, sub_dir);
				temp_full_path = strcat(temp_full_path, temp_sub);

				//logic checking whether the i-node matches the CLA
				if (stat(temp_full_path, &buf) == 0) {
					if ((int)buf.st_ino == i_node) {
						printf ("%s\n", temp_full_path);
						if (_del) remove(temp_full_path); //delete the file if the _del flag is set to true
					}
				}

				//search using recursion
				DIR *subsubdp = opendir(temp_full_path);
				if (subsubdp != NULL) {
					closedir(subsubdp);
					read_sub2_3(temp_full_path, i_node, _del);
				}
			}
		}
		
		closedir(sub_dp);
	}
	else {
		printf ("Cannot open directory\n");
		exit (2);
	}
}
















//main function parses CLAs and calls the correct function accordingly

int main(int argc, char *argv[]) {
	if (argc == 2) {
		read_sub1(argv[1]);
	}
	else if (argc == 4) {
		if (strcmp(argv[2], "-name") == 0) {
			read_sub2_1(argv[1], argv[3], 0);
		}
		else if (strcmp(argv[2], "-mmin") == 0) {
			read_sub2_2(argv[1], argv[3], 0);
		}
		else if (strcmp(argv[2], "-inum") == 0) {
			read_sub2_3(argv[1], atoi(argv[3]), 0);
		}
	}
	else if (argc == 5 && strcmp(argv[4], "-delete") == 0) { //call functions with the _del flag set to true
		if (strcmp(argv[2], "-name") == 0) {
			read_sub2_1(argv[1], argv[3], 1);
		}
		else if (strcmp(argv[2], "-mmin") == 0) {
			read_sub2_2(argv[1], argv[3], 1);
		}
		else if (strcmp(argv[2], "-inum") == 0) {
			read_sub2_3(argv[1], atoi(argv[3]), 1);
		}
	}
}




