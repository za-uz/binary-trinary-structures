/**
 * quatrits
 * (c) Zauz 2018
 **/

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

/**
 * Curl and Kerl needs these for hashing
 * They are values between -1 and 1 representing a single trit
 **/
typedef int8_t Trit;

/**
 * SIN uses these for network communication
 * They are four times two bits representing four times one trit
 **/
struct Quatrit {
	int8_t t1:2;
	int8_t t2:2;
	int8_t t3:2;
	int8_t t4:2;
};

Trit
Quatrit_get (struct Quatrit *trits, size_t index);

void
Quatrit_put (struct Quatrit *trits, Trit trit, size_t index);

/**
 * @param src: pointer to at least numtrits src Trits
 * @param dest: pointer to at least ((numtrits-1) / 4 + 1) Quatrits
 * @param numtrits: How many trits to copy
 **/
void
trits_to_quatrits (Trit *src, struct Quatrit *dest, size_t numtrits);

/**
 * @param src: pointer to at least ((numtrits-1) / 4 + 1) src Quatrits
 * @param dest: pointer to at least numtrits Trits
 * @param numtrits: How many trits to copy
 **/
void
quatrits_to_trits (struct Quatrit *src, Trit *dest, size_t numtrits);


/**
 * IRI uses these for network communication
 * They are a number between -121 and 121 representing 5 trits
 **/
typedef int8_t Cintrit;

/**
 * @param src: pointer to at least numtrits src Trits
 * @param dest: pointer to at least ((numtrits-1) / 5 + 1) Quatrits
 * @param numtrits: How many trits to copy
 **/
void
trits_to_cintrits (Trit *src, Cintrit *dest, size_t numtrits);

/**
 * @param src: pointer to at least ((numtrits-1) / 5 + 1) src Quatrits
 * @param dest: pointer to at least numtrits Trits
 * @param numtrits: How many trits to copy
 **/
void
cintrits_to_trits (Cintrit *src, Trit *dest, size_t numtrits);

#endif

