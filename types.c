/**
 * quatrits
 * (c) Zauz 2018
 **/

#include <stdio.h>

#include <stdlib.h>
#include <stdint.h>

#include "types.h"

// all of the output arrays should probably be memset with zero before calling
// the functions

Trit
Quatrit_get (struct Quatrit *trits, size_t index)
{
	switch (index & 3) {
	case 0:
		return trits[index >> 2].t1;
	case 1:
		return trits[index >> 2].t2;
	case 2:
		return trits[index >> 2].t3;
	default:
		return trits[index >> 2].t4;
	}
}

void
Quatrit_put (struct Quatrit *trits, Trit trit, size_t index)
{
	switch (index & 3) { // is if else if else if else faster?
	case 0:
		trits[index >> 2].t1 = trit;
		break;
	case 1:
		trits[index >> 2].t2 = trit;
		break;
	case 2:
		trits[index >> 2].t3 = trit;
		break;
	default:
		trits[index >> 2].t4 = trit;
		break;
	}
}

void
trits_to_quatrits (Trit *src, struct Quatrit *dest, size_t numtrits)
{
	size_t i;

	for (i = 0; i < numtrits; i++) {
		Quatrit_put(dest, src[i], i);
	}

	for (i = 0; i < numtrits % 4; i++) {
		Quatrit_put(dest, -2, numtrits + i);
	}
}

void
quatrits_to_trits (struct Quatrit *src, Trit *dest, size_t numtrits)
{
	size_t i;

	for (i = 0; i < numtrits; i++) {
		dest[i] = Quatrit_get(src, i);
	}
}

void
trits_to_cintrits (Trit *src, Cintrit *dest, size_t numtrits)
{
	Trit *last_src = &src[numtrits - 1];
	uint8_t factor = 1;

	while (src <= last_src) {
		*dest += *src * factor;
		src += sizeof(Trit);
		factor *= 3;
		if (factor == 243) {
			factor = 1;
			dest += sizeof(Cintrit);
		}
	}
}

void
cintrits_to_trits (Cintrit *src, Trit *dest, size_t numtrits)
{
	Trit *last_dest = dest + numtrits - 1;
	div_t result;
	Cintrit copy = *src;
	int8_t counter = 5;

	while (dest <= last_dest) {
		result = div(copy, 3);
		*dest = result.rem;
		copy = result.quot;
		if (*dest == -2) {
			*dest = 1;
			copy--;
		} else if (*dest == 2) {
			*dest = -1;
			copy++;
		}
		dest += sizeof(Trit);
		counter--;
		if (counter == 0) {
			counter = 5;
			src += sizeof(Cintrit);
			copy = *src;
		}
	}
}
