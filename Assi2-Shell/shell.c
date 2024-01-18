#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>


bool flag = false;
char cwd[100];
char prompt[100];


//this function is used to print the prompt
void printDir()
{
       char prompt1[500];
       if (flag == false)
       {
           	if (getcwd(cwd, sizeof(cwd)) != NULL) 
	       {
		      strcpy(prompt1,cwd);
		      strcat(prompt1,"$");
		      printf("%s ", prompt1);
	       }
	       else 
	       {
		      perror("Something is wrong!");
	       }   
      }
      else
      {
           printf("%s ", prompt);
      }
              
}


//this function is used to read the input
int readInput(char *str)
{
	char* buffer;

	buffer = readline("");
	if(strlen(buffer) != 0)
	{
		strcpy(str,buffer);
		return 0;
        }
        else
        {
                return 1;
        }
}


// this function is used to create tokens for executing command like ls -l, mkdir r,etc.
int token(char *str)
{
	int status;
	char *argv[200];
	int count = 0;
	char *final_str;
	char *token = strtok(str, " ");
	char *tokens[200];
	char *final_str1;
	
	while(token != NULL)
	{

		tokens[count] = malloc(sizeof(char) * strlen(token));
		strcpy(tokens[count], token);

		token = strtok(NULL," ");
		count++;

	}
	
	tokens[count] = NULL;
	
	final_str = malloc(sizeof(char) * (strlen(tokens[0]) + strlen("/bin/")));
	strcpy(final_str, "/bin/");
	strcat(final_str, tokens[0]);
	
	
	if(fork() == 0)
	{
		execv(final_str,tokens);
		perror("Command not found.");

	}
	else
	{
		wait(NULL);
	} 	       
}


//this function allows user to change the prompt to a particular string and revert back to CWD prompt PS1="XYZ"
int ps(char *str)
{
      
       char *temp = str;
       char newStr;
       int len=strlen(str);
     
       if(strncmp(temp,"PS1=\"", 5)==0)
        {
        	
                char new_prompt[100];
                for(int i=0;i<len-6;i++)
                {
                     new_prompt[i]=str[5+i];
                }
                   
                   flag = true;
                  //printf("%s ", new_prompt);
                   strcpy(prompt, new_prompt);
                   
                if(strcmp(temp,"PS1=\"\\w$\"")==0)
                {
                      flag = false;
                      return 1;
                } 
                   
        }
                
                
        else
        {
               return 0;
                 
        }
    return 1;
    
}

int main() 
{

        char str[100];
        while(1)
	{
              printDir();
	      if(readInput(str))
		      continue;
	      
	      if(ps(str)==1)
	      {
	        continue;
	      }
	         
	         
	      if(!(strcmp(str,"exit")))
	              exit(0);
	      
	      token(str);
	      
        }
	return 0;
}


