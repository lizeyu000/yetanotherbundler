# Library dependency #

  * cv.lib highgui.lib cxcore.lib
  * levmar.lib sba.lib blas.lib clapack.lib libF77.lib libI77.lib
  * sba-1.4, levmar-2.2, opencv 1.1

```
#ifndef _MISC_H_
#define _MISC_H_

/* common prefix for BLAS subroutines. Leave undefined in case of no prefix. You might also need to modify LM_BLAS_PREFIX below */
/* f2c'd BLAS */
#define LM_BLAS_PREFIX f2c_
/* C BLAS */
//#define LM_BLAS_PREFIX cblas_

/* common suffix for BLAS subroutines */
#define LM_BLAS_SUFFIX  // define empty if a f2c_ or cblas_ prefix was defined for LM_BLAS_PREFIX above
//#define LM_BLAS_SUFFIX _ // use this in case of no BLAS prefix

```