/* melder_atof.cpp
 *
 * Copyright (C) 2003-2008,2011,2015-2017 Paul Boersma
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

#include "melder.h"

template <typename T>
static const T *findEndOfNumericString (const T *string) noexcept {
	const T *p = & string [0];
	/*
	 * Leading white space is OK.
	 */
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		p ++;
	/*
	 * Next we accept an optional leading plus or minus.
	 */
	if (*p == '+' || *p == '-') p ++;
	/*
	 * The next character must be a decimal digit.
	 * So we don't allow things like ".5".
	 */
	if (*p < '0' || *p > '9') return nullptr;   // string is not numeric
	p ++;
	/*
	 * Then we accept any number of decimal digits.
	 */
	while (*p >= '0' && *p <= '9') p ++;
	/*
	 * Next we accept an optional decimal point.
	 */
	if (*p == '.') {
		p ++;
		/*
		 * We accept any number of (even zero) decimal digits after the decimal point.
		 */
		while (*p >= '0' && *p <= '9') p ++;
	}
	/*
	 * Next we accept an optional exponential E or e.
	 */
	if (*p == 'e' || *p == 'E') {
		p ++;
		/*
		 * In the exponent we accept an optional leading plus or minus.
		 */
		if (*p == '+' || *p == '-') p ++;
		/*
		 * The exponent must contain a decimal digit.
		 * So we don't allow things like "+2.1E".
		 */
		if (*p < '0' || *p > '9') return nullptr;   // string is not numeric
		p ++;
		/*
		 * Then we accept any number of decimal digits.
		 */
		while (*p >= '0' && *p <= '9') p ++;
	}
	/*
	 * Next we accept an optional percent sign.
	 */
	if (*p == '%') p ++;
	/*
	 * We have found the end of the numeric string.
	 */
	return p;
}

bool Melder_isStringNumeric (const char32 *string) noexcept {
	if (! string) return false;
	const char32 *p = findEndOfNumericString (string);
	if (! p) return false;
	/*
	 * We accept only white space after the numeric string.
	 */
	while (*p == U' ' || *p == U'\t' || *p == U'\n' || *p == U'\r')
		p ++;
	return *p == U'\0';
}

double Melder_a8tof (const char *string) noexcept {
	if (! string) return undefined;
	const char *p = findEndOfNumericString (string);
	if (! p) return undefined;
	Melder_assert (p - string > 0);
	return p [-1] == '%' ? 0.01 * strtod (string, nullptr) : strtod (string, nullptr);
}

double Melder_atof (const char32 *string) noexcept {
	return Melder_a8tof (Melder_peek32to8 (string));
}

int64 Melder_atoi (const char32 *string) noexcept {
	return strtoll (Melder_peek32to8 (string), nullptr, 10);
}

/* End of file melder_atof.cpp */
