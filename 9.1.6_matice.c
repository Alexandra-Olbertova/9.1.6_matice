#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define ELEM(mat,i,j) (mat->elem[(mat->cols)*i+j])

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;

MAT *mat_create_with_type(unsigned int rows, unsigned int cols){
	
	MAT *mat;
	mat = (MAT*)malloc(sizeof(float)*rows*cols);
	
	mat->cols = cols;
	mat->rows = rows;
	mat->elem = (float*)malloc(sizeof(float)*rows*cols);
	
	if (mat->elem == NULL){
		free(mat);
		return NULL;
	}
	return mat;	
}

void mat_destroy(MAT *mat){
	free(mat->elem);
	free(mat);
}

void mat_unit(MAT *mat){
	unsigned int i,j;
	
	for(i = 0; i < mat->rows; i++){
		for(j = 0; j < mat->cols; j++){
			if(i == j)
				ELEM(mat,i,j) = 1;
			else
				ELEM(mat,i,j) = 0;
		}
	}
}

void mat_random(MAT *mat){
	unsigned int i,j;
	
	srand(time(0));
	for(i = 0; i < mat->rows; i++){
		for(j = 0; j < mat->cols; j++){
			ELEM(mat,i,j) = -1+(float)rand()/(float)(RAND_MAX)*2;
		}
	}
}

void mat_print(MAT *mat){
	int i,j;
	
	for(i = 0; i < mat->rows; i++){
		for(j = 0; j < mat->cols; j++){
			printf("%02.2f ", ELEM(mat,i,j));
		}
		printf("\n");
	}
}
	
void mat_create_random_increasing(MAT *mat){
	
	int i,j;
	int x;
	
	srand(time(0));
	
	x = (rand()%200)-100;
	
	for(i = 0; i < mat->rows; i++){
		for(j = 0; j < mat->cols; j++){
		
			ELEM(mat,i,j) = x;
			x += (rand()%200);
		}
	}
}

main(){
	MAT *mat;
	
	mat = mat_create_with_type(3,3);

	mat_unit(mat);
	mat_print(mat);
	printf("\n");
	
	mat_random(mat);
	mat_print(mat);
	printf("\n");
	
	mat_create_random_increasing(mat);
	mat_print(mat);
	printf("\n");
}


