#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MYCOMMAND_LEN   1000
#define MYNUM_OF_PARAMS 500

int main()
{
	int i = 0, pid, stat, amountOfLib;
	char command[MYCOMMAND_LEN];
	char *params[MYNUM_OF_PARAMS];
	char *path, *lastStr;
	char *libs[100];
	int numberOflib = 0;
	char *commandPath;

	//cut path
	path = getenv("PATH");
	lastStr = strtok(path, ":");
	libs[0] = (char*)malloc(sizeof(char)*strlen(lastStr) + 1);
	strcpy(libs[0], lastStr);
	i = 1;
	while (lastStr = strtok(NULL, ":")) {
		libs[i] = (char*)malloc(sizeof(char)*strlen(lastStr) + 1);
		strcpy(libs[i], lastStr);
		i++;
		numberOflib = i;
	}
	numberOflib = i;

	puts("Please Enter Command: ");
	gets(commandPath);

	//loop until leave {
	while (strcmp(command, "leave") != 0) {

		//cut command
		lastStr = strtok(command, " ");
		params[0] = (char*)malloc(sizeof(char)*(strlen(lastStr) + 1));
		strcpy(params[0], lastStr);
		i = 1;
		while ((lastStr = strtok(NULL, " ")) != NULL)
		{
			params[i] = (char*)malloc(sizeof(char)*(strlen(lastStr) + 1));
			strcpy(params[i], lastStr);
			i++;
		}
		params[i] = NULL;

		//check if first is relative
		if ((pid = fork()) == 0) {
			if (params[0][0] == '/' ||
				(strlen(params[0]) >= 2 &&
					params[0][0] == '.' &&
					params[0][1] == '/'
					) ||
					(strlen(params[0]) >= 3 &&
						params[0][0] == '.' &&
						params[0][1] == '.' &&
						params[0][2] == '/'
						)
				) execv(params[0], params);
			else {
				for (i = 0; i < amountOfLib; i++) {
					commandPath = libs[i];
					strcat(commandPath, "/");
					strcat(commandPath, params[0]);
					execv(commandPath, params);
				}
				puts("command not found in PATH");
				exit(1);
			}
		} else {
			wait(&stat);
			if (stat != 0)
			{
				puts("Command Doesn't exist.\n");
			}
		}
		puts("Please Enter Command: ");
		gets(commandPath);
	}
	//}

}