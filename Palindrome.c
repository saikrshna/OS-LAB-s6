//PALINDROME USING TWO WAY PIPE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

#define BUFFER_SIZE 50

int is_palindrome(char *arr){
    int len=strlen(arr)-1;
    int i,j;
    for(i=0,j=len-1;i<j;i++,j--){
        if(arr[i] != arr[j]){
            return 0;
        }
    }
    return 1;
}

int main(){
    int pipefd1[2];
    int pipefd2[2];
    char str[BUFFER_SIZE];

    if(pipe(pipefd1)==-1 || pipe(pipefd2)==-1){
        perror("Pipe failure");
        exit(EXIT_FAILURE);
    }

    pid_t pid=fork();
    if(pid==-1){
        perror("Fork failure");
        exit(EXIT_FAILURE);
    }

    if(pid==0){
        //child
        close(pipefd1[1]);
        char arr[BUFFER_SIZE];
        int palindrome;
        sleep(3);
        read(pipefd1[0],&arr,sizeof(arr));
        if(is_palindrome(arr)==0){
            palindrome=0;
        }else{
            palindrome=1;
        }
        close(pipefd1[0]);
        close(pipefd2[0]);
        write(pipefd2[1],&palindrome,sizeof(palindrome));
        close(pipefd2[1]);
        
    }else{
        //parent
        close(pipefd1[0]);
        printf("Enter the string:");
        fgets(str, sizeof(str),stdin);
        write(pipefd1[1],&str,sizeof(str));
        close(pipefd1[1]);
        wait(NULL);
        
        close(pipefd2[1]);
        int pal;
        read(pipefd2[0],&pal,sizeof(pal));
        if(pal==1){
            printf("Palindrome");
        }else{
            printf("Not palindrome");
        }
        close(pipefd2[0]);
    }
}
