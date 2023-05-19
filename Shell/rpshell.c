#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h> 
#include <stdlib.h> 
#include <signal.h>

#define MAXLEN 200000
#define MAXARGS 1000
#define COLOR_BOLD  "\e[1m"
#define COLOR_OFF   "\e[m"

int concurrency=0, change_dir[2];// change_dir is a pipe for sending new_dir

char cmd[MAXLEN],*args[MAXARGS],*wel[] = {"cat","rpshlogo.txt",NULL};

void welcome()
{
    pid_t run = fork();
    if (!run)
    {
        signal(SIGINT,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
        execvp("cat",wel);
        return ;
    }
    wait(NULL);
    sleep(1);
}

void add_to_history()
{
    int count=0;
    FILE *history = fopen("history.txt","a+");
    fprintf(history,"%s",cmd);
    fclose(history);
}

void print_prompt()
{
    char* username = getenv("USER"),cwd[1024]; 
    getcwd(cwd, sizeof(cwd));
    printf(COLOR_BOLD"%s@%s#rpsh> "COLOR_OFF,username,cwd);
}

void print_history()
{
    int count=0;
    FILE *history = fopen("history.txt","r");
    char command[MAXLEN]="";
    while(fgets(command,MAXLEN,history)) printf("%d %s",++count,command);
    fclose(history);
}

void execute_cmd()
{
    concurrency=0;
    if (strlen(cmd)<=1) return;
    if (cmd[0]=='!')
    {
        if (strlen(cmd)<2)
        {
            printf("Invalid Command! Try again.\n");
            return;
        }
        int count=0,check=0,req=-1;
        if (cmd[1]=='!')
            check=1;
        if (!check) sscanf(cmd+1,"%d",&req);
        FILE *history = fopen("history.txt","r");
        char command[MAXLEN]="";
        while(fgets(command,MAXLEN,history)&&++count!=req);
        if (command) printf("command to execute: %s\n",command);
        if (command==NULL||strlen(command)<=1)
        {
            printf("No such command in history!\n");
            return;
        }
        else if (check||count==req)
            strcpy(cmd,command);
        else
        {
            printf("No such command in history!\n");
            return;
        }
        fclose(history);
    }
    if (strlen(cmd)<=1) return;
    add_to_history();
    int *status=calloc(sizeof(int),1);
    int num_of_args=1,in=0,old=0;
    for (int i=0;i<MAXARGS;i++)
    {
        old = in;
        for (;cmd[in]&&cmd[in]!=EOF;in++)
            if (!cmd[in]||cmd[in]=='\n'||cmd[in]==' ')
            {
                break;
                cmd[in]='\0';
            }
            else if (cmd[in]=='&')
            {
                concurrency=1;
                break;
            }
        if (in==old)
            break;
        args[i] = (char*)malloc((in-old+7)*sizeof(char));
        memcpy(args[i],cmd+old,in-old);
        args[i][in-old]='\0';
        in++;
        num_of_args++;
    }
    num_of_args--;
    args[num_of_args]=NULL;
    pid_t executing_child = fork();
    if (executing_child<0)
    {
        printf("Couldn't create a fork!\n");
        return;
    }
    else if (executing_child)
    { 
        if (concurrency) return;
        wait(status);
        if (*status/255==1)
            exit(0);
        else if (*status==2);
        else if (*status!=0)
            printf("Invalid Command! Try again.\n");
        char new_dir[1024];
        if (read(change_dir[0],new_dir,1024)>0)
        {
            printf("new dir : %s\n",new_dir);
            if (chdir(new_dir)<0)
                printf("No such directory: %s\n",new_dir);
        }
        return;
    }
    signal(SIGINT,SIG_DFL);
    signal(SIGTSTP,SIG_DFL);
    char *other_commands[]={"help","history","cd","exit","clear"};
    for (int i=0;i<5;i++)
    {
        if (!strcmp(args[0],other_commands[i]))
        {
            if (!i)
            {
                printf("This is a terminal created by Rohith Peddi.\
                \nAll Rights Reserved (c).\
                \nEnter commands that you wish to do.\
                \nSome commands are:\
                \nhelp: \t\tDisplay help menu.\
                \nexit: \t\tFor exiting rpshell.\
                \nhistory: \tShows you the history.\
                \n!!: \t\tExecutes the most recent command.\
                \n!x: \t\tExecutes xth command in the history.\
                \nThis shell also supports interrupts.\n");
            }
            else if (i==1)
                print_history();
            else if (i==2)
            {
                int y = write(change_dir[1],args[1],strlen(args[1])+1);
                if (y<0) printf("Change directory failed due to OS error!\n");
            }
            else if (i==3)
            {
                printf("\nThanks for using Rohith Peddi Shell (RPSH)\nGood Bye\n");
                exit(1);
            }
            else if (i==4)
                printf("\e[1;1H\e[2J");
            close(change_dir[0]);
            close(change_dir[1]);
            exit(0);
        }
    }
    close(change_dir[0]);
    close(change_dir[1]);
    if (execvp(args[0],args)<0)
        exit(-1);
    exit(0);
}

void signal_handler(int signo)
{
    printf("\n");
    concurrency=0;
    print_prompt();
    fflush(stdout);
}

int main()
{
    signal(SIGINT,signal_handler);
    signal(SIGTSTP,signal_handler);
    int y =pipe(change_dir);
    welcome();
    if (y<0) printf("The pipe communication has failed! cd command will not work!");
    while(7)
    {
        print_prompt();
        fgets(cmd,MAXLEN,stdin);
        concurrency=0;
        execute_cmd();
    }
    return 0;
}

