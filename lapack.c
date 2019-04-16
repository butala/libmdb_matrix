#include <assert.h>
#include <stdio.h>

#ifdef LINUX
#ifdef ATLAS
#include <clapack.h>
#else
//#error LAPACK routines are (so far) assume that atlas is installed
#endif
#endif


#include "lapack.h"


int eposv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, const int NRHS,
	   elem *A, const int lda,
	   elem *B, const int ldb) {
#ifdef OSX
  int ierr = 0;

  assert(order == CblasColMajor);

  if (!ierr) ierr = epotrf(order, uplo, N, A, lda);
  if (!ierr) epotrs(order, uplo, N, NRHS, A, lda, B, ldb);
  return(ierr);

#else
#ifdef DOUBLE_ELEM
  //return clapack_dposv(order, uplo, N, NRHS, A, lda, B, ldb);
  return dposv_(order, uplo, N, NRHS, A, lda, B, ldb);
#elif defined FLOAT_ELEM
  //return clapack_sposv(order, uplo, N, NRHS, A, lda, B, ldb);
  return sposv_(order, uplo, N, NRHS, A, lda, B, ldb);
#else
#error ?
#endif
#endif
}


int epotrf(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, elem *A, const int lda) {
#ifdef OSX
  char uplo_local;
  int N_local;
  int lda_local;
  int info;

  assert(order == CblasColMajor);

  if (uplo == CblasUpper) {
    uplo_local = 'U';
  }
  else if (uplo == CblasLower) {
    uplo_local = 'L';
  }
  else {
    assert(0);
  }

  N_local = N;
  lda_local = lda;

#ifdef DOUBLE_ELEM
  dpotrf_(&uplo_local, &N_local, A, &lda_local, &info);
  return info;
#elif defined FLOAT_ELEM
  spotrf_(&uplo_local, &N_local, A, &lda_local, &info);
  return info;
#else
#error ??
#endif

#else
#ifdef DOUBLE_ELEM
  //return clapack_dpotrf(order, uplo, N, A, lda);
  return dpotrf_(order, uplo, N, A, lda);
#elif defined FLOAT_ELEM
  //return clapack_spotrf(order, uplo, N, A, lda);
  return spotrf_(order, uplo, N, A, lda);
#else
#error ?
#endif
#endif
}


int epotrs(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, const int NRHS,
	   const elem *A, const int lda, elem *B, const int ldb) {
#ifdef OSX
  char uplo_local;
  int N_local, NRHS_local;
  int lda_local, ldb_local;
  int info;

  assert(order == CblasColMajor);

  if (uplo == CblasUpper) {
    uplo_local = 'U';
  }
  else if (uplo == CblasLower) {
    uplo_local = 'L';
  }
  else {
    assert(0);
  }

  N_local = N;
  NRHS_local = NRHS;
  lda_local = lda;
  ldb_local = ldb;

#ifdef DOUBLE_ELEM
  dpotrs_(&uplo_local, &N_local, (int *) &NRHS, (double *) A, &lda_local,
	  B, &ldb_local, &info);
  return info;
#elif defined FLOAT_ELEM
  spotrs_(&uplo_local, &N_local, (int *) &NRHS, (float *) A, &lda_local,
	  B, &ldb_local, &info);
  return info;
#else
#error ??
#endif

#else
#ifdef DOUBLE_ELEM
  //return clapack_dpotrs(order, uplo, N, NRHS, A, lda, B, ldb;)
  return dpotrs_(order, uplo, N, NRHS, A, lda, B, ldb);
#elif defined FLOAT_ELEM
  //return clapack_spotrs(order, uplo, N, NRHS, A, lda, B, ldb);
  return spotrs_(order, uplo, N, NRHS, A, lda, B, ldb);
#else
#error ?
#endif
#endif
}



int eppsv(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	  const int N, const int NRHS,
	  elem *A, elem *B, const int ldb) {
  int ierr = 0;

  assert(order == CblasColMajor);

  if (!ierr) ierr = epptrf(order, uplo, N, A);
  if (!ierr) epptrs(order, uplo, N, NRHS, A, B, ldb);
  return(ierr);
}


int epptrf(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, elem *A) {
  char uplo_local;
  int N_local;
  int info;

  assert(order == CblasColMajor);

  if (uplo == CblasUpper) {
    uplo_local = 'U';
  }
  else if (uplo == CblasLower) {
    uplo_local = 'L';
  }
  else {
    assert(0);
  }

  N_local = N;

#ifdef DOUBLE_ELEM
  dpptrf_(&uplo_local, &N_local, A, &info);
  return info;
#elif defined FLOAT_ELEM
  spptrf_(&uplo_local, &N_local, A, &info);
  return info;
#else
#error ?
#endif
}


int epptrs(const enum CBLAS_ORDER order, const enum CBLAS_UPLO uplo,
	   const int N, const int NRHS,
	   const elem *A, elem *B, const int ldb) {
  char uplo_local;
  int N_local, NRHS_local;
  int ldb_local;
  int info;

  assert(order == CblasColMajor);

  if (uplo == CblasUpper) {
    uplo_local = 'U';
  }
  else if (uplo == CblasLower) {
    uplo_local = 'L';
  }
  else {
    assert(0);
  }

  N_local = N;
  NRHS_local = NRHS;
  ldb_local = ldb;

#ifdef DOUBLE_ELEM
  dpptrs_(&uplo_local, &N_local, (int *) &NRHS, (double *) A,
	  B, &ldb_local, &info);
  return info;
#elif defined FLOAT_ELEM
  spptrs_(&uplo_local, &N_local, (int *) &NRHS, (float *) A,
	  B, &ldb_local, &info);
  return info;
#else
#error ?
#endif
}
