//Print numbers in one way pipe
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int main(){
    int n;
    int pipefd[2];
    int numbers[BUFFER_SIZE];

    printf("Enter the number of values to send: ");
    scanf("%d",&n);

    if(pipe(pipefd)==-1){
        printf("Pipe creation failed!");
        exit(EXIT_FAILURE);
    }

    pid_t pid=fork();
    if(pid==-1){
        printf("Fork failed!");
        exit(EXIT_FAILURE);
    }

    if(pid==0){
        //child process
        close(pipefd[1]);

        int received_numbers[BUFFER_SIZE];
        int numbers_received=0;

        while(read(pipefd[0],&received_numbers[numbers_received],sizeof(int))>0){
            printf("%d",received_numbers[numbers_received]);
            numbers_received++;
        }

        printf("The child process recieved the numbers %d",numbers_received);
        close(pipefd[0]);

    }else{
        //parent process
        close(pipefd[0]);

        printf("\nEnter the %d numbers", n);
        for(int i=0;i<n;i++){
            scanf("%d",&numbers[i]);
            write(pipefd[1],&numbers[i],sizeof(int));
        }


        close(pipefd[1]);
    }

    return 0;
}
