#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    
    int pipefd1[2];
    int pipefd2[2];
    
    int n;
    printf("Enter the limit of fibonacci: ");
    scanf("%d",&n);
    
    if(pipe(pipefd1)==-1 || pipe(pipefd2)==-1){
        printf("Pipe creation failed!");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid=fork();
    if(pid==-1){
        printf("Fork failed");
        exit(EXIT_FAILURE);
    }
    
    if(pid==0){
        //child
        int fib[n+1];
        close(pipefd1[1]);
        read(pipefd1[0],fib,(1+n)*sizeof(int));
        close(pipefd1[0]);
        
        close(pipefd2[0]);
        int limit=fib[n];
        int isFibonacci;
        int notfib[limit];
        int k=0;
        
        if(n<=4){
        printf("\nNo non-fibonacci Whole numbers exist in range..\n");
        }else{
        
            for(int i=4;i<limit;i++){
                isFibonacci=0;
                for(int j=2;j<=n;j++){
                    if(fib[j]==i){
                        isFibonacci=1;
                        break;
                    }
                }
            
                if(!isFibonacci){
                    notfib[k]=i;
                    k++;
                }
            }
        }
        write(pipefd2[1],&k,sizeof(int));
        write(pipefd2[1],notfib,k*sizeof(int));
        close(pipefd2[1]);
        
    }else{
        //parent
        close(pipefd1[0]);
        int fib[n+1];
        if(n==0){
            fib[0];
        }else if(n==1){
            fib[0]=0;
            fib[1]=1;
        }else if(n>=2){
            fib[0]=0;
            fib[1]=1;
            for(int i=2;i<=n;i++){
                fib[i]=fib[i-2]+fib[i-1];
            }
        }
    
        printf("\nThe fibonacci series is: ");
        for(int i=0;i<=n;i++){
            printf("%d\t",fib[i]);
        }
        
        write(pipefd1[1],fib,(1+n)*sizeof(int));
        close(pipefd1[1]);
        
        close(pipefd2[1]);
        int k;
        read(pipefd2[0],&k,sizeof(int));
        int notfib[k];
        read(pipefd2[0],notfib,k*sizeof(int));
        
        if(k!=0){
            printf("\nThe non fibonacci numbers are: ");
            for(int i=0;i<k;i++){
                printf("%d,",notfib[i]);
            }
        }
        close(pipefd2[0]);
        wait(NULL);
    }
    
    return 0;
}
