#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <fcntl.h>
#include <errno.h>

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
	
	if (mat == NULL || mat->elem == NULL){
		free(mat);
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
		printf("%s", strerror(errno));
		return NULL;
	}
	
	read(f, type, 2);
	
	if(type[0] != 'M' && type[1] != '1'){
		printf("%s", strerror(errno));
		return NULL;
	}
	
	read(f, rowcol, 2);
	
	matNew = mat_create_with_type(rowcol[0],rowcol[1]);
	matNew->elem = (float*)malloc(sizeof(float)*rowcol[0]*rowcol[1]);
	
	read(f, matNew->elem, rowcol[0]*rowcol[1]);
	
	return matNew;
}

char mat_save(MAT *mat,char *filename){
	
	char type[2];
	unsigned int rowcol[2];
	
	int f = open(filename, O_RDWR);
	
	if(f < 0){
		printf("%s", strerror(errno));
		return;
	}
	
	rowcol[0] = mat->rows;
	rowcol[1] = mat->cols;
	
	write(f, "M1", 2);
	write(f, rowcol, 2);
	write(f, mat->elem, rowcol[0]*rowcol[1]);
	
	if(close(f) == EOF){
		printf("Unable to close file\n");
		return;
	}
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

	for(j = 0; j < mat->cols; j++){
		
		ELEM(mat,0,j) = x;
		x += (rand()%200);
	}

	for(i = 1; i < mat->rows; i++){
		
		xx += (rand()%200);
		ELEM(mat,i,0) = xx;
		
		for(j = 1; j < mat->cols; j++){

			if(ELEM(mat,i-1,j) < ELEM(mat,i,j-1))
				ELEM(mat,i,j) = ELEM(mat,i,j-1)+ (rand()%200);
			else 
				ELEM(mat,i,j) = ELEM(mat,i-1,j) + (rand()%200);
	
		}		
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
	
//	mat_destroy(mat);
	
//	MAT *mat2;
//	char filename[50] = {"filename.bin"};

//	mat_save(mat, filename);
   	
//	mat2 = mat_create_by_file(filename);
//	mat_print(mat2);

//	mat_destroy(mat2);	
}


