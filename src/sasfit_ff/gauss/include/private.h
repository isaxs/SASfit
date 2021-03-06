/*
 * src/sasfit_ff/gauss/include/private.h
 *
 * Copyright (c) 2008-2009, Paul Scherrer Institute (PSI)
 *
 * This file is part of SASfit.
 *
 * SASfit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SASfit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SASfit.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Author(s) of this file:
 *   Joachim Kohlbrecher (joachim.kohlbrecher@psi.ch)
 *   Ingo Bressler (ingo@cs.tu-berlin.de)
 */

#ifndef GAUSS_PRIVATE_H
#define GAUSS_PRIVATE_H

#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_gamma.h>
#include "../../include/sasfit_ff_utils.h"


/**
 * form factor of a gauss coil with radius of gravity Rg  and scattering
 * length density eta
 */

typedef enum
{
	RG,
	PARAM1,
	PARAM2,
	PARAM3,
	PARAM4,
	B_P,
	MW,
	RHO_P,
	ETA_S,
	VOL,
	MN,
	I0,
	Q
} variable_names;

#define V       param->p

#define GAUSS_HEADER \
\
	scalar u; \
\
	SASFIT_ASSERT_PTR(param); \
\
	V[Q] = q; \
\
	SASFIT_CHECK_COND1((V[Q] < 0.0), param, "q(%lg) < 0",V[Q]); \
	SASFIT_CHECK_COND1((V[RG] < 0.0), param, "Rg(%lg) < 0",V[RG]); \
\
	u = V[Q]*V[Q] * V[RG]*V[RG]

#endif

