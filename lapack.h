#ifndef LAPACK_H
#define LAPACK_H

#ifdef ATLAS
#include <cblas.h>
#elif defined OPENBLAS
#include <cblas-openblas.h>
#elif defined VECLIB
#include <vecLib/cblas.h>
#else
#error 0
#endif

#include "elem.h"


int eposv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	  const int N, const int NRHS,
	  elem *A, const int lda,
	  elem *B, const int ldb);

int epotrf(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, elem *A, const int lda);

int epotrs(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, const int NRHS,
	   const elem *A, const int lda, elem *B, const int ldb);


int eppsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	  const int N, const int NRHS,
	  elem *A, elem *B, const int ldb);

int epptrf(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, elem *A);

int epptrs(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, const int NRHS,
	   const elem *A, elem *B, const int ldb);



#ifdef OSX

extern void dpotrf_(char *uplo, int *n, double *A, int *lda, int *info);
extern void spotrf_(char *uplo, int *n, float *A, int *lda, int *info);

extern void dpotrs_(char *uplo, int *n, int *nrhs, double *A, int *lda,
		    double *B, int *ldb, int *info);
extern void spotrs_(char *uplo, int *n, int *nrhs, float *A, int *lda,
		    float *B, int *ldb, int *info);

#endif

extern void dpptrf_(char *uplo, int *n, double *A, int *info);
extern void spptrf_(char *uplo, int *n, float *A, int *into);

extern void dpptrs_(char *uplo, int *n, int *nrhs, double *A,
		    double *B, int *ldb, int *info);
extern void spptrs_(char *uplo, int *n, int *nrhs, float *A,
		    float *B, int *ldb, int *info);

#endif
