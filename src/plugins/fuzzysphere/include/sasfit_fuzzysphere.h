/*
 * Author(s) of this file:
 *   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
 */

#ifndef SASFIT_PLUGIN_FUZZYSPHERE_H
#define SASFIT_PLUGIN_FUZZYSPHERE_H

#include <sasfit_common_shared_exports.h>

/**
 * \file sasfit_fuzzysphere.h
 * Public available functions and descriptions of the fuzzysphere plugin.
 */

/**
 * \def sasfit_fuzzysphere_DLLEXP
 * \copydoc sasfit_common_DLLEXP
 */

// adjust the project name below
// *_EXPORTS is set by cmake if build as shared library
#if defined(sasfit_fuzzysphere_EXPORTS)
	#ifdef sasfit_fuzzysphere_DLLEXP
	#undef sasfit_fuzzysphere_DLLEXP
	#endif
	#define sasfit_fuzzysphere_DLLEXP SASFIT_LIB_EXPORT
#elif !defined(sasfit_fuzzysphere_DLLEXP)
	// is set somewhere else for export as non-plugin
	#define sasfit_fuzzysphere_DLLEXP SASFIT_LIB_IMPORT
#endif

// general information about the form factor here
// & info used in the GUI:
// - group definition & uplevel group this one is in
// - brief description
// - description of parameters in HTML table-style

/* ################ start ff_fuzzysphere ################ */
/** 
 * \defgroup ff_fuzzysphere FuzzySphere
 * \ingroup ff_plugins_spheres_shells
 *
 * \brief \<some scattering from spherical particles with a "fuzzy" interface function\>
 *
 * <more detailed documentation, see 'doxygen' docs>
 *
 * \note Default (Size) Distribution: \ref delta
 *
 * \par Required parameters:
 *      <table border="0"><tr>
 *       <td>\b R</td>
 *       <td>radius of the fuzzy sphere</td>
 *      </tr><tr>
 *       <td>\b sigma</td>
 *       <td>thickness of the fuzzy shell</td>
 *      </tr><tr>
 *       <td>\b eta_sph</td>
 *       <td>scattering length density of sphere</td>
 *      </tr><tr>
 *       <td>\b eta_sol</td>
 *       <td>scattering length density of the solvent</td>
 *      </tr></table>
 */

/**
 * \ingroup ff_fuzzysphere
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_fuzzysphere(scalar q, sasfit_param * p);

/**
 * \ingroup ff_fuzzysphere
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_fuzzysphere_f(scalar q, sasfit_param * p);

/**
 * \ingroup ff_fuzzysphere
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_fuzzysphere_v(scalar q, sasfit_param * p, int dist);
/* ################ stop ff_fuzzysphere ################ */

/* ################ start ff_radial_profile_of_fuzzysphere ################ */
/** 
 * \defgroup ff_radial_profile_of_fuzzysphere Radial Profile of FuzzySphere
 * \ingroup ff_plugins_spheres_shells
 *
 * \brief \<some brief description of Radial Profile from a spherical particles with a "fuzzy" interface\>
 *
 * <more detailed documentation, see 'doxygen' docs>
 *
 * \note Default (Size) Distribution: \ref delta
 *
 * \par Required parameters:
 *      <table border="0"><tr>
 *       <td>\b R</td>
 *       <td>radius of the fuzzy sphere</td>
 *      </tr><tr>
 *       <td>\b sigma</td>
 *       <td>thickness of the fuzzy shell</td>
 *      </tr><tr>
 *       <td>\b eta_sph</td>
 *       <td>scattering length density of sphere</td>
 *      </tr><tr>
 *       <td>\b eta_sol</td>
 *       <td>scattering length density of solvent</td>
 *      </tr></table>
 */

/**
 * \ingroup ff_radial_profile_of_fuzzysphere
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_radial_profile_of_fuzzysphere(scalar q, sasfit_param * p);

/**
 * \ingroup ff_radial_profile_of_fuzzysphere
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_radial_profile_of_fuzzysphere_f(scalar q, sasfit_param * p);

/**
 * \ingroup ff_radial_profile_of_fuzzysphere
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_radial_profile_of_fuzzysphere_v(scalar q, sasfit_param * p, int dist);
/* ################ stop ff_radial_profile_of_fuzzysphere ################ */
















/* ################ start ff_coreshellmicrogel ################ */
/** 
 * \defgroup ff_coreshellmicrogel CoreShellMicrogel
 * \ingroup ff_plugins_spheres_shells
 *
 * \brief \<some scattering from spherical particles with a "fuzzy" interface function\>
 *
 * <more detailed documentation, see 'doxygen' docs>
 *
 * \note Default (Size) Distribution: \ref delta
 *
 * \par Required parameters:
 *      <table border="0"><tr>
 *       <td>\b W_core</td>
 *       <td>radius of center parts of core  with homogeneous scattering length density</td>
 *      </tr><tr>
 *       <td>\b sigma_core</td>
 *       <td>interface half width of the core</td>
 *      </tr><tr>
 *       <td>\b W_shell</td>
 *       <td>width of center parts of shell  with homogeneous scattering length density</td>
 *      </tr><tr>
 *       <td>\b sigma_sh,in</td>
 *       <td>half width of the inner interface of shell</td>
 *      </tr><tr>
 *       <td>\b D</td>
 *       <td>scattering length density of sphere</td>
 *      </tr><tr>
 *       <td>\b sigma_out</td>
 *       <td>half width of the outer surface profile</td>
 *      </tr><tr>
 *       <td>\b eta_core</td>
 *       <td>scattering length density of homogeneous core part</td>
 *      </tr><tr>
 *       <td>\b eta_shell</td>
 *       <td>scattering length density of homogeneous shell part</td>
 *      </tr><tr>
 *       <td>\b eta_sol</td>
 *       <td>scattering length density of solvent</td>
 *      </tr></table>
 */

/**
 * \ingroup ff_coreshellmicrogel
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_coreshellmicrogel(scalar q, sasfit_param * p);

/**
 * \ingroup ff_coreshellmicrogel
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_coreshellmicrogel_f(scalar q, sasfit_param * p);

/**
 * \ingroup ff_coreshellmicrogel
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_coreshellmicrogel_v(scalar q, sasfit_param * p, int dist);
/* ################ stop ff_coreshellmicrogel ################ */

/* ################ start ff_radial_profile_of_coreshellmicrogel ################ */
/** 
 * \defgroup ff_radial_profile_of_coreshellmicrogel Radial Profile of CoreShellMicrogel
 * \ingroup ff_plugins_spheres_shells
 *
 * \brief \<some brief description of Radial Profile from a spherical particles with a "fuzzy" interface\>
 *
 * <more detailed documentation, see 'doxygen' docs>
 *
 * \note Default (Size) Distribution: \ref delta
 *
 * \par Required parameters:
 *      <table border="0"><tr>
 *       <td>\b W_core</td>
 *       <td>radius of center parts of core  with homogeneous scattering length density</td>
 *      </tr><tr>
 *       <td>\b sigma_core</td>
 *       <td>interface half width of the core</td>
 *      </tr><tr>
 *       <td>\b W_shell</td>
 *       <td>width of center parts of shell  with homogeneous scattering length density</td>
 *      </tr><tr>
 *       <td>\b sigma_sh,in</td>
 *       <td>half width of the inner interface of shell</td>
 *      </tr><tr>
 *       <td>\b D</td>
 *       <td>scattering length density of sphere</td>
 *      </tr><tr>
 *       <td>\b sigma_out</td>
 *       <td>half width of the outer surface profile</td>
 *      </tr><tr>
 *       <td>\b eta_core</td>
 *       <td>scattering length density of homogeneous core part</td>
 *      </tr><tr>
 *       <td>\b eta_shell</td>
 *       <td>scattering length density of homogeneous shell part</td>
 *      </tr><tr>
 *       <td>\b eta_sol</td>
 *       <td>scattering length density of solvent</td>
 *      </tr></table>
 */

/**
 * \ingroup ff_radial_profile_of_coreshellmicrogel
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_radial_profile_of_coreshellmicrogel(scalar q, sasfit_param * p);

/**
 * \ingroup ff_radial_profile_of_coreshellmicrogel
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_radial_profile_of_coreshellmicrogel_f(scalar q, sasfit_param * p);

/**
 * \ingroup ff_radial_profile_of_coreshellmicrogel
 *
 * \sa sasfit_fuzzysphere.h, ff_plugins_spheres_shells
 */
sasfit_fuzzysphere_DLLEXP scalar sasfit_ff_radial_profile_of_coreshellmicrogel_v(scalar q, sasfit_param * p, int dist);
/* ################ stop ff_radial_profile_of_coreshellmicrogel ################ */


#endif // this file

