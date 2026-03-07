#include <stdio.h>
#include <string.h>

typedef struct {
    char choreName[64];
    } ChoreName;

ChoreName *choreArr = NULL;

int createNew(char *command, int choreCount) {
    if (strcmp(command, "new") == 0) {
	printf("Creating new.... \n");
	}
    else return 0;
	
    return 1;
    }

int main(int argc, char **argv) {
    if (argc < 2) {
	printf("Program usage: %s <command> <arguments> \n", argv[0]);
	return 1;
	}    
    
    int success;
    if (strcmp(argv[1], "new") == 0) {
	success = createNew(argv[1], argc - 2);
	if (!success) {
	    printf("Invalid command \n");
	    }
	else {
	    printf("%d tasks added successfully. \n", argc - 2);
	    }
	}
    else printf("Unknown command. \n");
    return 0;
    }
