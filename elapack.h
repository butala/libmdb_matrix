#ifndef ELAPACK_H
#define ELAPACK_H

#ifdef OSX
//#include <cblas.h>
//#include <gsl/gsl_cblas.h>
//#include <clapack.h>
//#define LAPACK_ROW_MAJOR CblasRowMajor
//#define LAPACK_COL_MAJOR CblasColMajor
//#include <lapack.h>
//#include <lapacke_config.h>
//#include <lapacke.h>
#include <lapacke.h>
#else
#include <lapacke.h>
#endif

#include "elem.h"


int eposv(const int order, const char uplo,
	  const int N, const int NRHS,
	  elem *A, const int lda,
	  elem *B, const int ldb);

int epotrf(const int order, const char uplo,
	   const int N, elem *A, const int lda);

int epotrs(const int order, const char uplo,
	   const int N, const int NRHS,
	   elem *A, const int lda, elem *B, const int ldb);


int eppsv(const int order, const char uplo,
	  const int N, const int NRHS,
	  elem *A, elem *B, const int ldb);

int epptrf(const int order, const char uplo,
	   const int N, elem *A);

int epptrs(const int order, const char uplo,
	   const int N, const int NRHS,
	   elem *A, elem *B, const int ldb);

#endif
