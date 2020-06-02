#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

typedef struct node
{
	struct node *sibling;
	struct node *child;
	struct node *parent;
	char type;
	char name[64];
}NODE;

int findCommand(char *command);
NODE* initialize();
void badCommand(char *command);
NODE* makeNode(char newType, char newName[64]);
void mkdir(NODE* head, char* dirName);
void ls(NODE* head, char* pathname);
NODE* cd(NODE* head, char* pathname);
void pwd(NODE* head);
void creat(NODE* head, char* fileName);
void menu();
void rmDir(NODE* head, char* dirName);
void rm(NODE* head, char* fileName);
int dupCheck(NODE* head, char* pathname);
void savepwd(NODE* head, FILE* filename);
void preorder(NODE* head, FILE* filename);
void save(NODE* head, char* pathname);
void quit(NODE* head);
int dirExists(NODE* head, char* dirName);
NODE* pathfinder(NODE* head, char* path);
void mkdirpath(NODE* head, char* path, char* base);
void mkdir2(NODE* head, char* pathname);
void creatpath(NODE* head, char* path, char* base);
void creat2(NODE* head, char* pathname);
void rmdirpath(NODE* head, char* path, char* base);
void rmdir2(NODE* head, char* pathname);
void rmpath(NODE* head, char* path, char* base);
void rm2(NODE* head, char* pathname);
void clearAll(NODE* head);
NODE* clear(NODE* root);
void removeSpaces(char *str);
void reload(NODE* root, char* pathname);

