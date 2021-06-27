#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <unistd.h>
#include <fcntl.h>

#define ELEM(mat,i,j) (mat->elem[(mat->cols)*i+j])
#define FAIL 0

typedef struct{
	unsigned int rows;
	unsigned int cols;
	float *elem;
}MAT;

MAT *mat_create_with_type(unsigned int rows, unsigned int cols){
	
	MAT *mat;
	mat = (MAT*)malloc(sizeof(float)*rows*cols);
	
	if(mat == NULL){
		free(mat);
		return NULL;
	}
	
	mat->cols = cols;
	mat->rows = rows;
	mat->elem = (float*)malloc(sizeof(float)*rows*cols);
	
	if (mat->elem == NULL){	
		free(mat->elem);
		return NULL;
	}
	return mat;	
}

MAT *mat_create_by_file(char *filename){
	
	char type[2];
	unsigned int rowcol[2];
	
	MAT *matNew;
	
	int f = open(filename, O_RDONLY);
	
	if(f < 0){
		return NULL;
	}
	
	read(f, type, 2);
	if(read == NULL)
		return FAIL;
	
	if(type[0] != 'M' && type[1] != '1'){
		return NULL;
	}
	
	read(f, rowcol, 2);
	if(read == NULL)
		return FAIL;
	
	matNew = mat_create_with_type(rowcol[0],rowcol[1]);
	matNew->elem = (float*)malloc(sizeof(float)*rowcol[0]*rowcol[1]);
	
	if(matNew->elem == NULL){
		free(matNew->elem);
		return NULL;
	}
	
	read(f, matNew->elem, rowcol[0]*rowcol[1]);
	
	return matNew;
}

char mat_save(MAT *mat, char *filename){
	
	char type[2];
	unsigned int rowcol[2];
	
	int f = open(filename, O_RDWR);
	
	if(f < 0){
		return;
	}
	
	rowcol[0] = mat->rows;
	rowcol[1] = mat->cols;
	
	write(f, "M1", 2);
	if(write == NULL)
		return FAIL;
		
	write(f, rowcol, 2);
	if(write == NULL)
		return FAIL;
		
	write(f, mat->elem, rowcol[0]*rowcol[1]);
	if(write == NULL)
		return FAIL;
		
	if(close(f) == EOF){
		return FAIL;
	}
	
	return f;	
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
			printf("%02.2f \t", ELEM(mat,i,j));
		}
		printf("\n");
	}
}
	
void mat_create_random_increasing(MAT *mat){
	
	int i,j;
	int x, y, xx;
	
	x = (rand()%200)-100;
	xx = x;

	for(i = 0; i < mat->rows; i++){
				
		ELEM(mat,i,0) = xx;

		for(j = 1; j < mat->cols; j++){

			if(i == 0){
				ELEM(mat,i,j) = x;
				x += (rand()%200);
				}
			
			else{
				if(ELEM(mat,i-1,j) < ELEM(mat,i,j-1))
					y = ELEM(mat,i,j-1);
				else 
					y = ELEM(mat,i-1,j);

				x = y + (rand()%200);
				ELEM(mat,i,j) = x;

			}		
		}
		xx += (rand()%200);
	}
	
	
}

main(){
	srand(time(0));
	
	MAT *mat;
	
	mat = mat_create_with_type(3,4);

	printf("Diagonal\n");
	mat_unit(mat);
	mat_print(mat);
	printf("\n");
	
	printf("Random\n");
	mat_random(mat);
	mat_print(mat);
	printf("\n");
	
	printf("Random increasing\n");
	mat_create_random_increasing(mat);
	mat_print(mat);
	printf("\n");
	
	mat_destroy(mat);
	mat_save(mat,"filename2.bin");
	
//	MAT *mat2;
//	char filename[50] = {"filename.bin"};
   	
//	mat2 = mat_create_by_file(filename);
//	mat_print(mat2);
//	mat_save(mat2, filename);

//	mat_destroy(mat2);	
}

