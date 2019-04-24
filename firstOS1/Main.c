#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MYCOMMAND_LEN   100
#define MYNUM_OF_PARAMS 50

extern char **environ;

int main()
{
	int i = 0, j, pid, stat, amountOfLib = 0 ,numofparams;
	char *command;
	char *params[MYNUM_OF_PARAMS];
	char *path, *lastStr;
	char *libs[100];
	int numberOflib = 0;
	char commandPath[20], *envp[1];


	//cut path
	path = (char*)malloc(sizeof(char)*strlen(getenv("PATH"))+1);
	strcpy(path,getenv("PATH"));


	puts("Please Enter Command: ");
	command = (char*)malloc(sizeof(char)*MYCOMMAND_LEN);
	rewind(stdin);
	gets(command);

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
		numofparams = i;

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
				) { execv(params[0], params);}
			else {

				for (lastStr = strtok(path, ":"); lastStr != NULL ; lastStr = strtok(NULL, ":")) {
                    strcpy(commandPath, lastStr);
					strcat(commandPath, "/");
					strcat(commandPath, params[0]);

                    setenv("PATH", lastStr,1);

					execv(commandPath, params);
				}
				puts("command not found in PATH");
				exit(1);
			}
		} else {
            wait(0);
		}
		puts("Please Enter Command: ");
		rewind(stdin);
        gets(command);
	}
	//}
exit(0);
}
