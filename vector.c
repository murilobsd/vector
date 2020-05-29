/*
 * Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <err.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

#define SELF ((struct vector *)v)

/* vector */
struct vector {
	uint32_t	 capacity;
	uint32_t	 length; 	/* number of elements */
	uint32_t 	 size;		/* size of each element */
	void		*data;
};

void
vector_free(vector_t *v)
{
	if (v == NULL) return;

	if (SELF->data != NULL)
		free(SELF->data);

	SELF->capacity = 0;
	SELF->length = 0;
	SELF->size = 0;

	free(v);
}


vector_t *
vector_new(uint32_t cap, uint32_t el_size)
{
	vector_t 	*v = NULL;

	if (cap == 0)
		cap = 1;

	if (el_size == 0 || cap >= ((size_t) - 1) / el_size)
		return NULL;

	v = malloc(sizeof(vector_t));

	if (v == NULL)
		return NULL;

	SELF->capacity = cap;
	SELF->length = 0;
	SELF->size = el_size;

	if (cap * el_size < VECTOR_MIN_ALLOC)
		cap = (VECTOR_MIN_ALLOC + (el_size - 1)) / el_size;

	/* TODO: check if os openbsd use reallocarray */
	SELF->data = malloc(cap * el_size);

	if (SELF->data == NULL) {
		free(v);
		return NULL;
	}

	return v;
}
