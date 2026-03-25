#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

const char *filename = "data.bin";

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
    ChoreName chore;
    FILE *f = fopen(filename, "rb");
    if (!f) {
	perror("Error opening file");
	return 0;
	}
    uint32_t len;
    int i = 1;
    
    while (fread(&len, sizeof(uint32_t), 1, f)) {
	fread(chore.choreName, sizeof(char), len, f);
	chore.choreName[len] = '\0';
	printf("%d:\t%s \n", i, chore.choreName);
	i++;
	}
    
    fclose(f);
    return 1;
    }

char *delete(char *taskNo) {
    ChoreName chore;    
    char *endptr, *deletedItem;
    const char *tempFile = "temp.bin";
    errno = 0;
    
    int itemNo = (int)strtol(taskNo, &endptr, 10);
    
    if (errno != 0) {
	perror("Conversion failed");
	return NULL;
	}    
    if (endptr == taskNo) {
	printf("Invalid item no. \n");
	return NULL;
	}
    
    FILE *f1, *f2; 
    f1 = fopen(filename, "rb");
    f2 = fopen(tempFile, "wb");
    deletedItem = malloc(sizeof(ChoreName));
        
    if (!f1 || !f2 || !deletedItem) {
	if (!f1 || !f2) perror("Failed to open file");
	if (!deletedItem) perror("Memory allocation failed");
	if (f1) fclose(f1);
	if (f2) fclose(f2);
	if (deletedItem) free(deletedItem);
	return NULL;
	}
    
    int i = 1;
    uint32_t len;
    while (fread(&len, sizeof(uint32_t), 1, f1)) {
	if (itemNo == i) {
	    i++;
	    fread(chore.choreName, sizeof(char), len, f1);
	    strcpy(deletedItem, chore.choreName);
	    continue;
	    }
	else {
	    fread(chore.choreName, sizeof(char), len, f1);
	    fwrite(&len, sizeof(uint32_t), 1, f2);
	    fwrite(chore.choreName, sizeof(char), len, f2);
	    i++;
	    }
	}
    
    fclose(f1);
    fclose(f2);
    remove(filename);
    rename(tempFile, filename);
    
    return deletedItem;
    }

int main(int argc, char **argv) {
    if (argc < 2) {
	printf("Program usage: %s <command> <arguments> \n", argv[0]);
	return 1;
	}
    
    uint32_t allocdMem = sizeof(ChoreName) * (argc - 2);
    choreArr = malloc(allocdMem);
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

    else if (strcmp(argv[1], "delete") == 0) {
	char *deletedItem = delete(argv[2]);
	char *itemNo = argv[2];
	if (itemNo != NULL) {
	    printf("Deleted item no. %s: %s \n", itemNo, deletedItem);
	    free(deletedItem);
	    }
	}
    
    else printf("Unknown command. \n");
    free(choreArr);
    return 0;
    }
