/*
 * Author(s) of this file:
 *   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
 */

#ifdef MAKE_SASFIT_PLUGIN
#include "include/private.h"

// functions to mark for export
SASFIT_PLUGIN_EXP_BEGIN(4)
SASFIT_PLUGIN_EXP_ADD( ff_triax_ellip_shell )
SASFIT_PLUGIN_EXP_ADD( ff_triax_ellip_shell_syl )
SASFIT_PLUGIN_EXP_ADD( ff_triax_ellip_shell_sq_baba_ahmed_1 )
SASFIT_PLUGIN_EXP_ADD( ff_triax_ellip_shell_sq_baba_ahmed_2 )
SASFIT_PLUGIN_EXP_END

// import functions from other plugins
SASFIT_PLUGIN_IMP_BEGIN(1)
SASFIT_PLUGIN_IMP_ADD( sq_baba_ahmed_syl )
SASFIT_PLUGIN_IMP_END

SASFIT_PLUGIN_INTERFACE

void do_at_init(void)
{
	// insert custom init code here (optional)
}

#endif

