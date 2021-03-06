#include "f2c.h"
#include "blaswrap.h"

/* Table of constant values */

static integer c__7 = 7;
static real c_b5 = 0.f;
static real c_b6 = 1.f;

doublereal stzt02_(integer *m, integer *n, real *af, integer *lda, real *tau, 
	real *work, integer *lwork)
{
    /* System generated locals */
    integer af_dim1, af_offset, i__1, i__2;
    real ret_val;

    /* Local variables */
    integer i__;
    real rwork[1];
    extern doublereal slamch_(char *), slange_(char *, integer *, 
	    integer *, real *, integer *, real *);
    extern /* Subroutine */ int xerbla_(char *, integer *), slaset_(
	    char *, integer *, integer *, real *, real *, real *, integer *), slatzm_(char *, integer *, integer *, real *, integer *, 
	    real *, real *, real *, integer *, real *);


/*  -- LAPACK test routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  STZT02 returns */
/*       || I - Q'*Q || / ( M * eps) */
/*  where the matrix Q is defined by the Householder transformations */
/*  generated by STZRQF. */

/*  Arguments */
/*  ========= */

/*  M       (input) INTEGER */
/*          The number of rows of the matrix AF. */

/*  N       (input) INTEGER */
/*          The number of columns of the matrix AF. */

/*  AF      (input) REAL array, dimension (LDA,N) */
/*          The output of STZRQF. */

/*  LDA     (input) INTEGER */
/*          The leading dimension of the array AF. */

/*  TAU     (input) REAL array, dimension (M) */
/*          Details of the Householder transformations as returned by */
/*          STZRQF. */

/*  WORK    (workspace) REAL array, dimension (LWORK) */

/*  LWORK   (input) INTEGER */
/*          length of WORK array. Must be >= N*N+N */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    /* Parameter adjustments */
    af_dim1 = *lda;
    af_offset = 1 + af_dim1;
    af -= af_offset;
    --tau;
    --work;

    /* Function Body */
    ret_val = 0.f;

    if (*lwork < *n * *n + *n) {
	xerbla_("STZT02", &c__7);
	return ret_val;
    }

/*     Quick return if possible */

    if (*m <= 0 || *n <= 0) {
	return ret_val;
    }

/*     Q := I */

    slaset_("Full", n, n, &c_b5, &c_b6, &work[1], n);

/*     Q := P(1) * ... * P(m) * Q */

    for (i__ = *m; i__ >= 1; --i__) {
	i__1 = *n - *m + 1;
	slatzm_("Left", &i__1, n, &af[i__ + (*m + 1) * af_dim1], lda, &tau[
		i__], &work[i__], &work[*m + 1], n, &work[*n * *n + 1]);
/* L10: */
    }

/*     Q := P(m) * ... * P(1) * Q */

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = *n - *m + 1;
	slatzm_("Left", &i__2, n, &af[i__ + (*m + 1) * af_dim1], lda, &tau[
		i__], &work[i__], &work[*m + 1], n, &work[*n * *n + 1]);
/* L20: */
    }

/*     Q := Q - I */

    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	work[(i__ - 1) * *n + i__] += -1.f;
/* L30: */
    }

    ret_val = slange_("One-norm", n, n, &work[1], n, rwork) / (
	    slamch_("Epsilon") * (real) max(*m,*n));
    return ret_val;

/*     End of STZT02 */

} /* stzt02_ */
