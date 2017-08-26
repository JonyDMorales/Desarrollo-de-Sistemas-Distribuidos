#include <stdio.h>
#include <stdlib.h>

int es_primo(unsigned int n){
	for(int i = 2; i < n ; i++)
		if((n % i) == 0)
			return 0;
return 1;
}

int main(){
	int p = es_primo(4294967291);
	//int p = es_primo(2507831371);
	//printf("%d\n",p);
	return 0;
}