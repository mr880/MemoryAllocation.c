#include "mymalloc.h"
char  memspace[5000] ={[0] = (short)4996, [4998]= (short)-4996};

void* mymalloc(size_t size, char* file, int line){
	short* tmp = (short*)&memspace[0];

	while(tmp < (short*)&memspace[4998]){
		if(debug){
			printf("checking %ld\n",&memspace[4998]-tmp);
		}
		short i = (short)*tmp;
		i = (short)abs((int)i);
		if(*tmp > size+4){
			if(i-size-4 > 0){
				if(debug)
					printf("%d\n",-(short)size);
				*tmp = -(short)size;
				*(tmp+size+2) = (short)size;
				*(tmp+size+4) = (short)(i-size-4);
				*(tmp+i+2) = -(short)(i-size-4);
			}
			else{
				*tmp = -i;
				*(tmp+i+2) = i;
			}
			if(debug){
				printf("found space\n");
				printf("value of bot is %d at %p\n",*tmp,tmp);
			}
			return (void*)(tmp+2);
		}
		tmp = tmp + i+2;
	}
	printf("no space was available for %s on line %d",file,line);
}

void myfree(void* ptr,  char* file, int line){
	if(ptr == NULL){
		printf("Error on line %d in file %s: null pointer\n",line,file);
		return;	
	}
	short* bot = (short*)(ptr - 2);
	short size = abs((short)*bot);
	short* top = (short*)(ptr + size);
	short* tmp;
	if(*(bot) > 0){
		printf("Error on line %d in file %s: memory already free\n",line,file);
		if(debug)
			printf("%d\n",*bot);
		return;
	}
	if(*(bot-2) < 0 && (char*)bot != &memspace[0]){
		tmp = bot - 4 - abs(*(bot - 2));
		size = *tmp + abs(*(bot)); 
		*((short*)ptr-4) = (short)0;
		*bot = (short)0;
		*(bot-2) = (short)0;
		bot = tmp;
	}

	tmp = (short*)(ptr + size);
	if(*(top+2) > 0 && (char*)top != &memspace[4998]){
		size = size + abs(*(top+2));
		*top = (short)0;
		top = top + *(top+2) + 4
;
	}

	*bot = size;
	*top = -size;

	return;
}

 
