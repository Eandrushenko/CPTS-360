#include "Node.h"

int main(void)
{
	NODE *root = NULL, *cwd = NULL;
	root = initialize();
	cwd = root;

	char cmd[32], pathname[64], line[64];
	int ID = 0;
	while (ID != 10)
	{
		strcpy(pathname, "\0");
		strcpy(line, "\0");
		strcpy(cmd, "\0");
		printf("input a command: ");
		fgets(line, 64, stdin);
		sscanf(line, "%s %s", cmd, pathname);
		ID = findCommand(cmd);
		switch (ID) {
		case 0:
			menu();
			break;
		case 1:
			mkdir2(cwd, pathname);
			break;
		case 2:
			rmdir2(cwd, pathname);
			break;
		case 3:
			ls(cwd, pathname);
			break;
		case 4:
			cwd = cd(cwd, pathname);
			break;
		case 5:
			pwd(cwd);
			break;
		case 6:
			creat2(cwd, pathname);
			break;
		case 7:
			rm2(cwd, pathname);
			break;
		case 8:
			cwd = clear(root);
			reload(cwd, pathname);
		case 9:
			save(cwd, pathname);
			break;
		case 10:
			quit(cwd);
			break;
		case -1:
			badCommand(cmd);
			break;
		}
	}
	return 0;
}


int dupCheck(NODE* head, char* pathname)
{
	NODE* Cur = head->child;
	int flag = 0;
	if (Cur == NULL)
	{
		flag = 0;
	}
	else
	{
		while (Cur)
		{
			if (!strcmp(Cur->name, pathname))
			{
				printf("%s already exists in this directory\n", pathname);
				flag = 1;
			}
			Cur = Cur->sibling;
		}
	}
	return flag;
}

int findCommand(char *command)
{
	char *cmd[] = { "menu", "mkdir", "rmdir", "ls", "cd",
		"pwd", "creat", "rm","reload", "save", "quit", 0 };
	int i = 0;
	while (cmd[i])
	{
		if (strcmp(command, cmd[i]) == 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}

void badCommand(char *command)
{
	printf("========== ERROR =============\n");
	printf("The command \'%s\' was not found\n", command);
	printf("==============================\n");
}

NODE* makeNode(char newType, char newName[64])
{
	NODE* Mem = NULL;
	Mem = (NODE*)malloc(sizeof(NODE));
	if (Mem != NULL)
	{
		Mem->sibling = NULL;
		Mem->type = newType;
		Mem->child = NULL;
		Mem->parent = NULL;
		strcpy(Mem->name, newName);
	}
	return Mem;
}

NODE* initialize()
{
	NODE *root = makeNode('D', "/");
	root->sibling = root;
	root->parent = root;
	root->child = NULL;
	return root;
}


void mkdir(NODE* head, char* dirName)
{
	NODE* Mem = makeNode('D', dirName);
	NODE* Cur = head->child;
	int check = 0;
	check = dupCheck(head, dirName);
	if (check == 1)
	{
		return;
	}
	if (Mem != NULL)
	{
		if (head->child == NULL)
		{
			head->child = Mem;
			Mem->parent = head;
		}
		else
		{
			while (Cur->sibling != NULL)
			{
				Cur = Cur->sibling;
			}
			Cur->sibling = Mem;
			Mem->parent = head;
		}
	}
}

void ls(NODE* head, char* pathname)
{
	NODE* Cur = head->child;
	if (!strcmp(pathname, "\0"))
	{
		while (Cur)
		{
			printf("%c : %s   ", Cur->type, Cur->name);
			Cur = Cur->sibling;
		}
		printf("\n");
	}
}

void pwd(NODE* head)
{
	NODE* Cur = head;
	printf("Current Directory: %s\n", Cur->name);
	char string1[128] = "";
	char string2[128] = "";
	char slash[128] = "/";
	while (Cur->parent != Cur->sibling)
	{
		strcpy(slash, "/");
		strcpy(string2, Cur->name);
		strcat(slash, string2);
		strcat(slash, string1);
		strcpy(string1, slash);
		Cur = Cur->parent;
	}
	if (!strcmp(string1, ""))
	{
		strcpy(string1, slash);
	}
	printf("Directory Path: %s\n", string1);

}

NODE* cd(NODE* head, char* pathname)
{
	NODE* Cur = head;
	int flag = 0;
	if (!strcmp(pathname, "\0"))
	{
		while (Cur->parent != Cur)
		{
			Cur = Cur->parent;
		}
		return Cur->parent;
	}
	else
	{
		Cur = Cur->child;
		while (Cur)
		{
			if (!strcmp(Cur->name, pathname))
			{
				if (Cur->type == 'D')
				{
					return Cur;
				}
				else
				{
					printf("%s is not a directory\n", pathname);
					return head;
				}
				flag = 1;
			}
			Cur = Cur->sibling;
		}
		if (flag == 0)
		{
			printf("%s does not exist\n", pathname);
			return head;
		}
	}
}

void creat(NODE* head, char* fileName)
{
	NODE* Mem = makeNode('F', fileName);
	NODE* Cur = head->child;
	int check = 0;
	check = dupCheck(head, fileName);
	if (check == 1)
	{
		return;
	}

	if (Mem != NULL)
	{
		if (head->child == NULL)
		{
			head->child = Mem;
			Mem->parent = head;
		}
		else
		{
			while (Cur->sibling != NULL)
			{
				Cur = Cur->sibling;
			}
			Cur->sibling = Mem;
			Mem->parent = head;
		}
	}
}

void menu()
{
	//char *cmd[] = { "menu", "mkdir", "rmdir", "ls", "cd",
	//	"pwd", "creat", "rm","reload", "save", "quit", 0 };
	printf("========== MENU ==============\n");
	printf("menu, mkdir, rmdir, ls, cd,\npwd, creat, rm, reload, save, quit\n");
	printf("==============================\n");

}

void rmDir(NODE* head, char* dirName)
{
	NODE* Cur = head->child;
	NODE* Prev = Cur;
	NODE* remove;
	int flag = 0;

	if (Cur == NULL)
	{
		flag = 0;
	}
	else if (!strcmp(Cur->name, dirName))
	{
		if (Cur->type == 'D')
		{
			if (Cur->child == NULL)
			{
				head->child = Cur->sibling;
				remove = Cur;
				flag = 1;
			}
			else
			{
				printf("%s must be empty before it can be removed\n", dirName);
				flag = 2;
			}
		}
		else
		{
			printf("%s is not a directory\n", dirName);
			flag = 2;
		}
	}
	else
	{
		Prev = head->child;
		Cur = Prev->sibling;
		while (Cur)
		{
			if (!strcmp(Cur->name, dirName))
			{
				if (Cur->type == 'D')
				{
					if (Cur->child == NULL)
					{
						Prev->sibling = Cur->sibling;
						remove = Cur;
						flag = 1;
					}
					else
					{
						printf("%s must be empty before it can be removed\n", dirName);
						flag = 2;
					}
				}
				else
				{
					printf("%s is not a directory\n", dirName);
					flag = 2;
				}
			}
			Prev = Cur;
			Cur = Cur->sibling;
		}
	}
	if (flag == 0)
	{
		printf("%s was not found\n", dirName);
	}
	else if (flag == 1)
	{
		free(remove);
	}
}


void rm(NODE* head, char* fileName)
{
	NODE* Cur = head->child;
	NODE* Prev = Cur;
	NODE* remove;
	int flag = 0;

	if (Cur == NULL)
	{
		flag = 0;
	}
	else if (!strcmp(Cur->name, fileName))
	{
		if (Cur->type == 'F')
		{
			if (Cur->child == NULL)
			{
				head->child = Cur->sibling;
				remove = Cur;
				flag = 1;
			}
			else
			{
				printf("%s Somehow has Child Nodes! BIG ERROR!\n", fileName);
				flag = 2;
			}
		}
		else
		{
			printf("%s is not a file\n", fileName);
			flag = 2;
		}
	}
	else
	{
		Prev = head->child;
		Cur = Prev->sibling;
		while (Cur)
		{
			if (!strcmp(Cur->name, fileName))
			{
				if (Cur->type == 'F')
				{
					if (Cur->child == NULL)
					{
						Prev->sibling = Cur->sibling;
						remove = Cur;
						flag = 1;
					}
					else
					{
						printf("%s Somehow has Child Nodes! BIG ERROR!\n", fileName);
						flag = 2;
					}
				}
				else
				{
					printf("%s is not a file\n", fileName);
					flag = 2;
				}
			}
			Prev = Cur;
			Cur = Cur->sibling;
		}
	}
	if (flag == 0)
	{
		printf("%s was not found\n", fileName);
	}
	else if (flag == 1)
	{
		free(remove);
	}
}

void savepwd(NODE* head, FILE* filename)
{
	NODE* Cur = head;
	fprintf(filename, "%c   ", Cur->type);
	char string1[128] = "";
	char string2[128] = "";
	char slash[128] = "/";
	while (Cur->parent != Cur->sibling)
	{
		strcpy(slash, "/");
		strcpy(string2, Cur->name);
		strcat(slash, string2);
		strcat(slash, string1);
		strcpy(string1, slash);
		Cur = Cur->parent;
	}
	if (!strcmp(string1, ""))
	{
		strcpy(string1, slash);
	}
	fprintf(filename, "%s\n", string1);

}

void preorder(NODE* head, FILE* filename)
{
	if (head)
	{
		savepwd(head, filename);
		preorder(head->child, filename);
		preorder(head->sibling, filename);
	}
}

void save(NODE* head, char* pathname)
{
	NODE* Cur = head;
	while (Cur->parent != Cur->sibling)
	{
		Cur = Cur->parent;
	}
	Cur = Cur->child;
	if (!strcmp(pathname, ""))
	{
		strcpy(pathname, "file.txt");
	}
	FILE *fp = fopen(pathname, "w+");
	fprintf(fp, "D   /\n");
	preorder(Cur, fp);
	fclose(fp);
}

void quit(NODE* head)
{
	save(head, "file.txt");
}

int dirExists(NODE* head, char* dirName)
{
	NODE* Cur = head->child;
	int flag = 0;

	while (Cur)
	{
		if (!strcmp(dirName, Cur->name))
		{
			if (Cur->type == 'D')
			{
				flag = 1;
				return flag;
			}
			else
			{
				printf("%s is not a directory\n", dirName);
				return flag;
			}
		}
		Cur = Cur->sibling;
	}
	if (flag == 0)
	{
		printf("path does not exist: stopped at [%s]\n", dirName);
		return flag;
	}
}

NODE* pathfinder(NODE* head, char* path)
{
	NODE* Cur = head;
	int flag = 1;
	if (path[0] == '/')
	{
		while (Cur->parent != Cur->sibling)
		{
			Cur = Cur->parent;
		}
	}
	char *token;
	token = strtok(path, "/");
	while (token != NULL)
	{
		flag = dirExists(Cur, token);
		if (flag == 1)
		{
			Cur = cd(Cur, token);
		}
		else
		{
			flag = 0;
			return head;
		}
		token = strtok(NULL, "/");
	}
	return Cur;
}

void mkdirpath(NODE* head, char* path, char* base)
{
	NODE* Cur = head;
	int flag = 1;
	if (path[0] == '/')
	{
		while (Cur->parent != Cur->sibling)
		{
			Cur = Cur->parent;
		}
	}
	char *token;
	token = strtok(path, "/");
	while (token != NULL)
	{
		flag = dirExists(Cur, token);
		if (flag == 1)
		{
			Cur = cd(Cur, token);
		}
		else
		{
			flag = 0;
			return;
		}
		token = strtok(NULL, "/");
	}
	mkdir(Cur, base);
}

void mkdir2(NODE* head, char* pathname)
{
	NODE* Cur = head;
	char temp[128] = "", path[128] = "", base[64] = "";

	strcpy(temp, pathname);
	strcpy(path, dirname(temp));

	strcpy(temp, pathname);
	strcpy(base, basename(temp));

	if (!strcmp(path, "."))
	{
		mkdir(Cur, base);
	}
	else
	{
		mkdirpath(Cur, path, base);
	}
}

void creatpath(NODE* head, char* path, char* base)
{
        NODE* Cur = head;
        int flag = 1;
        if (path[0] == '/')
        {
                while (Cur->parent != Cur->sibling)
                {
                        Cur = Cur->parent;
                }
        }
        char *token;
        token = strtok(path, "/");
        while (token != NULL)
        {
                flag = dirExists(Cur, token);
                if (flag == 1)
                {
                        Cur = cd(Cur, token);
                }
                else
                {
                        flag = 0;
                        return;
                }
                token = strtok(NULL, "/");
        }
        creat(Cur, base);
}

void creat2(NODE* head, char* pathname)
{
        NODE* Cur = head;
        char temp[128] = "", path[128] = "", base[64] = "";

        strcpy(temp, pathname);
        strcpy(path, dirname(temp));

        strcpy(temp, pathname);
        strcpy(base, basename(temp));

        if (!strcmp(path, "."))
        {
                creat(Cur, base);
        }
        else
        {
                creatpath(Cur, path, base);
        }
}

void rmdirpath(NODE* head, char* path, char* base)
{
        NODE* Cur = head;
        int flag = 1;
        if (path[0] == '/')
        {
                while (Cur->parent != Cur->sibling)
                {
                        Cur = Cur->parent;
                }
        }
        char *token;
        token = strtok(path, "/");
        while (token != NULL)
        {
                flag = dirExists(Cur, token);
                if (flag == 1)
                {
                        Cur = cd(Cur, token);
                }
                else
                {
                        flag = 0;
                        return;
                }
                token = strtok(NULL, "/");
        }
	if (Cur == head)
	{
		printf("You can not delete current working directory\n");
		return;
	}
        rmDir(Cur, base);
}

void rmdir2(NODE* head, char* pathname)
{
        NODE* Cur = head;
        char temp[128] = "", path[128] = "", base[64] = "";

        strcpy(temp, pathname);
        strcpy(path, dirname(temp));

        strcpy(temp, pathname);
        strcpy(base, basename(temp));

        if (!strcmp(path, "."))
        {
                rmDir(Cur, base);
        }
        else
        {
                rmdirpath(Cur, path, base);
        }
}

void rmpath(NODE* head, char* path, char* base)
{
        NODE* Cur = head;
        int flag = 1;
        if (path[0] == '/')
        {
                while (Cur->parent != Cur->sibling)
                {
                        Cur = Cur->parent;
                }
        }
        char *token;
        token = strtok(path, "/");
        while (token != NULL)
        {
                flag = dirExists(Cur, token);
                if (flag == 1)
                {
                        Cur = cd(Cur, token);
                }
                else
                {
                        flag = 0;
                        return;
                }
                token = strtok(NULL, "/");
        }
        rm(Cur, base);
}

void rm2(NODE* head, char* pathname)
{
        NODE* Cur = head;
        char temp[128] = "", path[128] = "", base[64] = "";

        strcpy(temp, pathname);
        strcpy(path, dirname(temp));

        strcpy(temp, pathname);
        strcpy(base, basename(temp));

        if (!strcmp(path, "."))
        {
                rm(Cur, base);
        }
        else
        {
                rmpath(Cur, path, base);
        }
}

void clearAll(NODE* head)
{
	if (head)
	{
		clearAll(head->child);
		clearAll(head->sibling);
		free(head);
	}
}

NODE* clear(NODE* root)
{
	clearAll(root->child);
	root->sibling = root;
	root->parent = root;
	root->child = NULL;
	return root;
}

void removeSpaces(char *str)
{
	int i,j=0;
    	for(i=0;str[i]!='\0';++i)
    	{
        	if(str[i]!=' ')
            	str[j++]=str[i];
    	}
    
    	str[j]='\0';
}

void reload(NODE* head, char* pathname)
{
	NODE* Cur = head;
	if (!strcmp(pathname, ""))
	{
		strcpy(pathname, "file.txt");
	}
	FILE *fp = fopen(pathname, "r");
	if (fp != NULL)
	{
		char line[128];
		fgets(line, sizeof line, fp);
		while (fgets(line, sizeof line, fp) != NULL)
		{
			removeSpaces(line);
			char* token;
			token = strtok(line, "\n");
			if (line[0] == 'D')
			{
				mkdir2(Cur, memmove(token, token + 2, strlen(token)));
			}
			else
			{
				creat2(Cur, memmove(token, token + 2, strlen(token)));
			}
		}
	}
	else
	{
		printf("%s does not exist", pathname);
		return;
	}
	fclose(fp);
}


