/*
 * Author(s) of this file:
 *   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
 */
 
#include <sasfit.h>

#include <sasfit_common.h>
#include "include/private.h"
#include <sasfit_error_ff.h>

// define shortcuts for local parameters/variables

scalar sasfit_ff_parallelepiped_abc2(scalar q, sasfit_param * param)
{
	scalar sum;
    scalar cubxmin[3], cubxmax[3], fval[1], ferr[1];
    int intstrategy;
	
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	SASFIT_CHECK_COND1((q < 0.0), param, "q(%lg) < 0",q);
	SASFIT_CHECK_COND1((A < 0.0), param, "a(%lg) < 0",A); // modify condition to your needs
	SASFIT_CHECK_COND1((B < 0.0), param, "b(%lg) < 0",B); // modify condition to your needs
	SASFIT_CHECK_COND1((C < 0.0), param, "c(%lg) < 0",C); // modify condition to your needs
	SASFIT_CHECK_COND1((ETA < 0.0), param, "eta(%lg) < 0",ETA); // modify condition to your needs

    if (SIGMA==0) return sasfit_ff_parallelepiped_abc(q,param);
	Q=q;
	NUDIM = 2;
	// insert your code here
    intstrategy = sasfit_get_int_strategy();
	intstrategy = P_CUBATURE;

	switch(intstrategy) {
		// ERROR_INDIVIDUAL, ERROR_PAIRED, ERROR_L2
    case H_CUBATURE: {
			cubxmin[0]=0;
			cubxmax[0]=M_PI/2.0;
			cubxmin[1]=0;
			cubxmax[1]=M_PI/2.0;
			find_LogNorm_int_range(4,1,SIGMA,&cubxmin[2], &cubxmax[2], param);
			hcubature(1, &K_cubature,param,3, cubxmin, cubxmax, 
				100000, 0.0, sasfit_eps_get_nriq(), ERROR_L2, 
				fval, ferr);
			sum = fval[0];
            break;
            }
    case P_CUBATURE: {
			cubxmin[0]=0;
			cubxmax[0]=M_PI/2.0;
			cubxmin[1]=0;
			cubxmax[1]=M_PI/2.0;
			find_LogNorm_int_range(4,1,SIGMA,&cubxmin[2], &cubxmax[2], param);
			pcubature(1, &K_cubature,param,3, cubxmin, cubxmax, 
				100000, 0.0, sasfit_eps_get_nriq(), ERROR_L2, 
				fval, ferr);
			sum = fval[0];
            break;
            }
    default: {
		    sasfit_err("no valid sasfit_integrate routine\n");
//            sum=sasfit_integrate(0.0,M_PI/2.0,&Psi_kernel,param);;
            break;
            }
    }
	return gsl_pow_2(ETA)*sum;
}

scalar sasfit_ff_parallelepiped_abc2_f(scalar q, sasfit_param * param)
{
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	// insert your code here
    if (SIGMA==0) return sasfit_ff_parallelepiped_abc_f(q,param);
	return 0.0;
}

scalar sasfit_ff_parallelepiped_abc2_v(scalar q, sasfit_param * param, int dist)
{
	SASFIT_ASSERT_PTR(param); // assert pointer param is valid

	// insert your code here
    if (SIGMA==0) return sasfit_ff_parallelepiped_abc_v(q,param,dist);
	return A*B*C;
}

