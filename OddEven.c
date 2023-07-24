//ODD EVEN USING ONE WAY PIPE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    
    int pipefd[2];

    if(pipe(pipefd)==-1){
        printf("Pipe error");
        exit(EXIT_FAILURE);
    }

    pid_t pid=fork();
    if(pid==-1){
        printf("Fork Error");
        exit(EXIT_FAILURE);
    }

    if(pid==0){
        //child
        close(pipefd[1]);
        int num;
        read(pipefd[0],&num,sizeof(int));
        if(num%2==0){
            printf("The number received at chiled is even");
        }else{
            printf("The number received at child is odd");
        }
        close(pipefd[0]);

    }else{
        //parent
        close(pipefd[0]);
        int n;
        printf("Enter the number:");
        scanf("%d",&n);
        write(pipefd[1],&n,sizeof(int));
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}
