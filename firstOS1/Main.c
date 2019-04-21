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

	for (int j = 0; j < numberOflib; j++) printf("%s", libs[i]);
	while (1);

	//loop until leave {
		
		//get and cut command

		//call child to execute

	//}

}