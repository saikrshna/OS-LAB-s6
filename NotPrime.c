#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define BUFFERSIZE 50;

int is_prime(int num){
    if(num==0 || num==1){
        return 0;
    }
    for(int i=2;i<=num/2;i++){
        if(num%i==0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int n;
    int pipefd1[2];
    int pipefd2[2];
    
    if(pipe(pipefd1)==-1 || pipe(pipefd2)==-1){
        printf("Pipe creation failed");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid=fork();
    if(pid==-1){
        printf("Fork failed");
        exit(EXIT_FAILURE);
    }
    
    if(pid==0){
        //child
        close(pipefd1[1]);
        int prime[n];
        int count;
        read(pipefd1[0],&count,sizeof(int));
        read(pipefd1[0],prime,count*sizeof(int));
        close(pipefd1[0]);
        
        close(pipefd2[0]);
        int notprime[n];
        int limit=prime[count-1];
        int counter=0;
        
        for(int i=0;i<limit;i++){
            if(!is_prime(i)){
                notprime[counter]=i;
                counter++;
            }
        }
       
        write(pipefd2[1],&counter,sizeof(int));
        write(pipefd2[1],notprime,counter*sizeof(int));
        close(pipefd2[1]);
        
    }else{
        //parent
        close(pipefd1[0]);
        printf("Enter the limit: ");
        scanf("%d",&n);
        int prime[n];
        int count=0;
        printf("\nThe prime numbers are: ");
        for(int j=2;j<n;j++){
            if(is_prime(j)==1){
                printf("%d,", j);
                prime[count]=j;
                count++;
            }
        }
        
        write(pipefd1[1],&count,sizeof(int));
        write(pipefd1[1],prime,count*sizeof(int));
        close(pipefd1[1]);
        
        close(pipefd2[1]);
        int counter;
        read(pipefd2[0],&counter,sizeof(int));
        int notprime[counter];
        read(pipefd2[0],notprime,counter*sizeof(int));
        
        printf("\nThe non prime numbers are: ");
        for(int i=0;i<counter;i++){
            printf("%d,", notprime[i]);
        }
        wait(NULL);
    }
    return 0;
    
}
