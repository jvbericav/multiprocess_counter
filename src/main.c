#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
	pid_t pid;
	int numero, div;
	char espaco;
	int p = PROT_READ | PROT_WRITE; //protection
	int v = MAP_SHARED | MAP_ANON;  //visibility
	int *para;
	int *b; //número de primos
	int *n_p; //número de processos
	b = (int*) mmap(NULL, sizeof(int), p, v, 0, 0);
	n_p = (int*) mmap(NULL, sizeof(int), p, v, 0, 0);
	para = (int*) mmap(NULL, sizeof(int), p, v, 0, 0);
	*para = 0;
	while(*para==0){
		scanf("%d%c", &numero, &espaco);
		if(espaco == '\n'){
			*para=1;
			div = 0;
			for(int i=1; i<=numero;i++){
				if(numero % i ==0)
					div ++;
			}
			if(div == 2)
				(*b)++; //é primo
		}
		else{
			pid = fork();
			(*n_p) ++;
			//filho
			if(pid == 0){
				div = 0;	
				for(int i=1; i<=numero;i++){
					if(numero % i ==0)
						div ++;
				}
				if(div == 2)
					(*b)++; //é primo
				(*n_p) --;
				exit(0);
			}
			//pai
			else{
				if(*n_p == 4)
					sleep(1);
			}
		}
	}
	sleep(4);
	printf("%d\n", *b);
	return 0;
}


