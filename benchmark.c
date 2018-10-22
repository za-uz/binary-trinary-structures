/**
 * quatrits
 * (c) Zauz 2018
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"

#define TX_NUM 1000
#define TX_SIZE 8019
#define QTX_SIZE 2005
#define CTX_SIZE 1604

void random_trits(Trit *dest, size_t num);

int main() {
	Trit *txs[TX_NUM];
	Trit *from_q_txs[TX_NUM];
	Trit *from_c_txs[TX_NUM];
	struct Quatrit *qtxs[TX_NUM];
	Cintrit *ctxs[TX_NUM];
	size_t i;
	struct timespec before, after;

	srand(142);
	
	printf("Allocating memory...\n");
	clock_gettime(CLOCK_REALTIME, &before);
	for (i = 0; i < TX_NUM; i++) {
		txs[i] = malloc(TX_SIZE);
		from_q_txs[i] = malloc(TX_SIZE);
		from_c_txs[i] = malloc(TX_SIZE);
		qtxs[i] = malloc(QTX_SIZE);
		ctxs[i] = malloc(CTX_SIZE);

		memset(txs[i], 0, TX_SIZE);
		memset(qtxs[i], 0, QTX_SIZE);
		memset(ctxs[i], 0, CTX_SIZE);
	}
	clock_gettime(CLOCK_REALTIME, &after);
	printf("Finished %lld.%.9ld\n", (long long) after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);
	
	printf("Generating random trits...\n");
	clock_gettime(CLOCK_REALTIME, &before);
	for (i = 0; i < TX_NUM; i++) {
		random_trits(txs[i], TX_SIZE);
	}
	clock_gettime(CLOCK_REALTIME, &after);
	printf("Finished %lld.%.9ld\n", (long long) after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);

	printf("Converting to Quatrits...\n");
	clock_gettime(CLOCK_REALTIME, &before);
	for (i = 0; i < TX_NUM; i++) {
		trits_to_quatrits(txs[i], qtxs[i], TX_SIZE);
	}
	clock_gettime(CLOCK_REALTIME, &after);
	printf("Finished %lld.%.9ld\n", (long long) after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);

	printf("Converting to Cintrits...\n");
	clock_gettime(CLOCK_REALTIME, &before);
	for (i = 0; i < TX_NUM; i++) {
		trits_to_cintrits(txs[i], ctxs[i], TX_SIZE);
	}
	clock_gettime(CLOCK_REALTIME, &after);
	printf("Finished %lld.%.9ld\n", (long long) after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);


	printf("Converting from Quatrits...\n");
	clock_gettime(CLOCK_REALTIME, &before);
	for (i = 0; i < TX_NUM; i++) {
		quatrits_to_trits(qtxs[i], from_q_txs[i], TX_SIZE);
	}
	clock_gettime(CLOCK_REALTIME, &after);
	printf("Finished %lld.%.9ld\n", (long long) after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);

	printf("Converting from Cintrits...\n");
	clock_gettime(CLOCK_REALTIME, &before);
	for (i = 0; i < TX_NUM; i++) {
		cintrits_to_trits(ctxs[i], from_c_txs[i], TX_SIZE);
	}
	clock_gettime(CLOCK_REALTIME, &after);
	printf("Finished %lld.%.9ld\n", (long long) after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);

	printf("Comparing...\n");
	clock_gettime(CLOCK_REALTIME, &before);
	for (i = 0; i < TX_NUM; i++) {
		if (memcmp(txs[i], from_q_txs[i], TX_SIZE) != 0) {
			fprintf(stderr, "ERROR: Converting didn't work!");
		}
		if (memcmp(txs[i], from_c_txs[i], TX_SIZE) != 0) {
			fprintf(stderr, "ERROR: Converting didn't work!");
		}
	}
	clock_gettime(CLOCK_REALTIME, &after);
	printf("Finished %lld.%.9ld\n", (long long) after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);
	printf("Freeing...\n");
	clock_gettime(CLOCK_REALTIME, &before);
	for (i = 0; i < TX_NUM; i++) {
		free(txs[i]);
		free(qtxs[i]);
		free(ctxs[i]);
	}
	clock_gettime(CLOCK_REALTIME, &after);
	printf("Finished %lld.%.9ld\n", (long long) after.tv_sec-before.tv_sec, after.tv_nsec-before.tv_nsec);

	return EXIT_SUCCESS;
}

void random_trits(Trit *dest, size_t num)
{
	Trit *final = dest + num;
	for (final = dest + num; dest < final; dest += sizeof(Trit)) {
		*dest = (Trit) (rand() % 3 - 1);
	}
}
