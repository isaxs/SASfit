/*
 * Author(s) of this file:
 *   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
 *   2th of August 2016
 */

#ifdef MAKE_SASFIT_PLUGIN
#include "include/private.h"

// functions to mark for export
SASFIT_PLUGIN_EXP_BEGIN(14)
SASFIT_PLUGIN_EXP_ADD( peak_beta_amplitude )
SASFIT_PLUGIN_EXP_ADD( peak_beta_area )
SASFIT_PLUGIN_EXP_ADD( peak_chi_squared_amplitude )
SASFIT_PLUGIN_EXP_ADD( peak_chi_squared_area )
SASFIT_PLUGIN_EXP_ADD( peak_erfc_amplitude )
SASFIT_PLUGIN_EXP_ADD( peak_erfc_area )
SASFIT_PLUGIN_EXP_ADD( peak_error_amplitude )
SASFIT_PLUGIN_EXP_ADD( peak_error_area )
SASFIT_PLUGIN_EXP_ADD( peak_exponentially_modified_gaussian_amplitude )
SASFIT_PLUGIN_EXP_ADD( peak_exponentially_modified_gaussian_area )
SASFIT_PLUGIN_EXP_ADD( peak_extreme_value_amplitude )
SASFIT_PLUGIN_EXP_ADD( peak_extreme_value_area )
SASFIT_PLUGIN_EXP_ADD( peak_gex_amplitude )
SASFIT_PLUGIN_EXP_ADD( peak_gex_area )

SASFIT_PLUGIN_EXP_END

// import functions from other plugins
SASFIT_PLUGIN_IMP_NONE

SASFIT_PLUGIN_INTERFACE

void do_at_init(void)
{
	// insert custom init code here (optional)
}

#endif

