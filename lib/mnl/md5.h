/* MD5.H - header file for MD5C.C
 */

/* Copyright (C) 1991-2, RSA Data Security, Inc. Created 1991. All
rights reserved.

License to copy and use this software is granted provided that it
is identified as the "RSA Data Security, Inc. MD5 Message-Digest
Algorithm" in all material mentioning or referencing this software
or this function.

License is also granted to make and use derivative works provided
that such works are identified as "derived from the RSA Data
Security, Inc. MD5 Message-Digest Algorithm" in all material
mentioning or referencing the derived work.

RSA Data Security, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

These notices must be retained in any copies of any part of this
documentation and/or software.
 */

/*
 * This is slightly modified for tpop3d; since OpenSSL defines its own
 * structure called MD5_CTX, we rename this one for compatibility. We also
 * remove global.h which needn't be in a separate file, and get rid of the
 * K&Risms.
 */

#include <limits.h>


/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;

/* XXX should replace these with C99 types or whatever. */

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
#if INT_MAX>32767L
typedef unsigned int UINT4;
#else
typedef unsigned long int UINT4;
#endif

/* MD5 context. */
typedef struct {
  UINT4 state[4];                    /* state (ABCD) */
  UINT4 count[2];     /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                /* input buffer */
} md5_ctx;

void MD5Init(md5_ctx *);
void MD5Update(md5_ctx *, unsigned char *, unsigned int);
void MD5Final(unsigned char [16], md5_ctx *);
void md5_signature(const unsigned char *, unsigned int, unsigned char [16]);
