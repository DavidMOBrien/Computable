/* enorm.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

doublereal enorm_(integer *n, doublereal *x)
{
    /* Initialized data */

    static doublereal one = 1.;
    static doublereal zero = 0.;
    static doublereal rdwarf = 3.834e-20;
    static doublereal rgiant = 1.304e19;

    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal s1, s2, s3, xabs, x1max, x3max, agiant, floatn;

/*     ********** */

/*     function enorm */

/*     given an n-vector x, this function calculates the */
/*     euclidean norm of x. */

/*     the euclidean norm is computed by accumulating the sum of */
/*     squares in three different sums. the sums of squares for the */
/*     small and large components are scaled so that no overflows */
/*     occur. non-destructive underflows are permitted. underflows */
/*     and overflows do not occur in the computation of the unscaled */
/*     sum of squares for the intermediate components. */
/*     the definitions of small, intermediate and large components */
/*     depend on two constants, rdwarf and rgiant. the main */
/*     restrictions on these constants are that rdwarf**2 not */
/*     underflow and rgiant**2 not overflow. the constants */
/*     given here are suitable for every known computer. */

/*     the function statement is */

/*       double precision function enorm(n,x) */

/*     where */

/*       n is a positive integer input variable. */

/*       x is an input array of length n. */

/*     subprograms called */

/*       fortran-supplied ... dabs,dsqrt */

/*     argonne national laboratory. minpack project. march 1980. */
/*     burton s. garbow, kenneth e. hillstrom, jorge j. more */

/*     ********** */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    s1 = zero;
    s2 = zero;
    s3 = zero;
    x1max = zero;
    x3max = zero;
    floatn = (doublereal) (*n);
    agiant = rgiant / floatn;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xabs = (d__1 = x[i__], abs(d__1));
	if (xabs > rdwarf && xabs < agiant) {
	    goto L70;
	}
	if (xabs <= rdwarf) {
	    goto L30;
	}

/*              sum for large components. */

	if (xabs <= x1max) {
	    goto L10;
	}
/* Computing 2nd power */
	d__1 = x1max / xabs;
	s1 = one + s1 * (d__1 * d__1);
	x1max = xabs;
	goto L20;
L10:
/* Computing 2nd power */
	d__1 = xabs / x1max;
	s1 += d__1 * d__1;
L20:
	goto L60;
L30:

/*              sum for small components. */

	if (xabs <= x3max) {
	    goto L40;
	}
/* Computing 2nd power */
	d__1 = x3max / xabs;
	s3 = one + s3 * (d__1 * d__1);
	x3max = xabs;
	goto L50;
L40:
	if (xabs != zero) {
/* Computing 2nd power */
	    d__1 = xabs / x3max;
	    s3 += d__1 * d__1;
	}
L50:
L60:
	goto L80;
L70:

/*           sum for intermediate components. */

/* Computing 2nd power */
	d__1 = xabs;
	s2 += d__1 * d__1;
L80:
/* L90: */
	;
    }

/*     calculation of norm. */

    if (s1 == zero) {
	goto L100;
    }
    ret_val = x1max * sqrt(s1 + s2 / x1max / x1max);
    goto L130;
L100:
    if (s2 == zero) {
	goto L110;
    }
    if (s2 >= x3max) {
	ret_val = sqrt(s2 * (one + x3max / s2 * (x3max * s3)));
    }
    if (s2 < x3max) {
	ret_val = sqrt(x3max * (s2 / x3max + x3max * s3));
    }
    goto L120;
L110:
    ret_val = x3max * sqrt(s3);
L120:
L130:
    return ret_val;

/*     last card of function enorm. */

} /* enorm_ */

