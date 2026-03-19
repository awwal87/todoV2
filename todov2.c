#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

const char* filename = "data.bin";

typedef struct {
    char choreName[64];
    } ChoreName;

ChoreName *choreArr = NULL;

int createNew(char *command, int choreCount) {
    FILE *f;
    if (strcmp(command, "new") == 0) {
	printf("Creating new.... \n");
	f = fopen(filename, "wb");
	if (!f) {
	    perror("Error creating file");
	    return 0;
	    }
	}
    else return 0;
    
    int i = 0;
    uint32_t len;
    while ((len = strlen(choreArr[i].choreName))) {
	fwrite(&len, sizeof(uint32_t), 1, f);
	fwrite(choreArr[i].choreName, sizeof(char), len, f);
	i++;
	}
    
    fclose(f);
    return 1;
    }

int viewList(void) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
	perror("Error opening file");
	return 0;
	}
    uint32_t len;
    int i = 1;
    
    while (fread(&len, sizeof(uint32_t), 1, f)) {
	fread(choreArr->choreName, sizeof(char), len, f);
	if (len < 64) choreArr->choreName[len] = '\0';
	else choreArr->choreName[len - 1] = '\0';
	printf("%d:\t%s \n", i, choreArr->choreName);
	i++;
	}
    
    fclose(f);
    return 1;
    }

int main(int argc, char **argv) {
    if (argc < 2) {
	printf("Program usage: %s <command> <arguments> \n", argv[0]);
	return 1;
	}
    
    choreArr = malloc(sizeof(ChoreName) * (argc - 2));
    if (!choreArr) {
	perror("Memory allocation failed");
	return 1;
	}
    
    for (int i = 0; i < argc - 2; i++) {
	strcpy(choreArr[i].choreName, argv[i + 2]);
	}
    
    int success;
    if (strcmp(argv[1], "new") == 0) {
	success = createNew(argv[1], argc - 2);
	if (!success) {
	    printf("Invalid command \n");
	    }
	else {
	    printf("%d tasks added successfully. \n", argc - 2);
	    for (int i = 0; i < argc - 2; i++) {
		printf("%s \n", choreArr[i].choreName);
		}
	    }
	}
    else if (strcmp(argv[1], "view") == 0) {
	viewList();
	}
    else printf("Unknown command. \n");
    return 0;
    }
/*
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * */
