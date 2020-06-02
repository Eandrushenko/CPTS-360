#include "type.h"
#include "source.h"

int main(int argc, char *argv[])
{
    int i, cmd; 
    char line[128], cname[64], parameter[64];
    initialize();
    mount_root(argv[1]);
    printf("Dev=%d, inodeBegin=%d, bmap=%d, imap=%d, ninodes=%d\n", dev, inodeBegin, bmap, imap, ninodes);
    while(1)
    {
      	strcpy(pathname, "");
	strcpy(parameter, "");
	strcpy(cname, "");
        printf("P%d running: ", running->pid);
        printf("input command : ");
        fgets(line, 128, stdin);
        //line[strlen(line)-1] = 0;  // kill the \r char at end
        if (line[0]==0) continue;

        sscanf(line, "%s %s %s", cname, pathname, parameter);
        printf("Pathname = %s, parameter = %s\n", pathname, parameter);
        if(parameter[0] != 0)
        {
            strcat(pathname, " ");
            strcat(pathname, parameter);
        }

	if(!strcmp(cname, "ls"))
	{
		ls(pathname);
	}
	else if(!strcmp(cname, "cd"))
        {
                cd(pathname);
        }
        else if(!strcmp(cname, "pwd"))
        {
                do_pwd(pathname);
        }
        else if(!strcmp(cname, "quit"))
        {
                quit(pathname);
        }
        else if(!strcmp(cname, "mkdir"))
        {
                make_dir(pathname);
        }
        else if(!strcmp(cname, "rmdir"))
        {
                my_rmdir(pathname);
        }
        else if(!strcmp(cname, "creat"))
        {
                creat_file(pathname);
        }
        else if(!strcmp(cname, "link"))
        {
                link(pathname);
        }
        else if(!strcmp(cname, "unlink"))
        {
                unlink(pathname);
        }
        else if(!strcmp(cname, "symlink"))
        {
                symlink(pathname);
        }






    }
}

