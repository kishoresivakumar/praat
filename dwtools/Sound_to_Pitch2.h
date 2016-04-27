#ifndef _Sound_to_Pitch2_h_
#define _Sound_to_Pitch2_h_
/* Sound_to_Pitch2.h
 *
 * Copyright (C) 1993-2011, 2015 David Weenink
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 djmw 19970410
 djmw 20020813 GPL header
 djmw 20110307 Latest modification
*/

#include "Sound_extensions.h"
#include "Pitch.h"

autoPitch Sound_to_Pitch_shs (Sound me, double timeStep, double minimumPitch,
	double maximumFrequency, double ceiling, long maxnSubharmonics, long maxnCandidates,
	double compressionFactor, long nDivisionsPerOctave);

autoPitch Sound_to_Pitch_SPINET (Sound me, double timeStep, double windowDuration,
	double minimumFrequencyHz, double maximumFrequencyHz, long nFilters,
	double ceiling, int maxnCandidates);

#endif /* _Sound_to_Pitch2_h_ */
