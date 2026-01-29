/*
 * /d/Gondor/std/water/boat.h
 *
 *  Copyright (C) 1998 by Nancy L. Mintz
 *
 * defines for /d/Gondor/std/water/boat.c
 *
 */

#ifndef	_BOAT_DEFINITIONS_
#define	_BOAT_DEFINITIONS_

#include <ss_types.h>
#include "water_room.h"

#define	INSIDE_BOAT_FILE	(WATER_DIR+"inside_boat")
#define	SPLINTERED_WOOD		(WATER_DIR+"splintered_wood")

#define	DEFAULT_CAPACITY	3
#define	MAX_CAPACITY		6

#define	MIN_BOAT_SKILL		5
#define	DEFAULT_WEIGHT		90720	/* 200 lbs */
#define	DEFAULT_VOLUME		1699235 /* 10' long x 3' wide x 2' deep */
#define	DEFAULT_MAX_VOLUME(v)	((80 * (v)) / 100)


/* min # of times boat may hit rock before it breaks up */
#define	MIN_ROCK_HITS	5

/* can player 'pl' flip boat whose max current is 'max' in 
 * current of str 'str' ?
 * if good swim skill && water < boat's max && water < ROUGH,
 * succeed; else 50/50 chance
 */
#define	CAN_FLIP(pl, str, max) \
    (((pl)->query_skill(SS_SWIM) > 25 && \
      str < max && \
      str < ROUGH_CURRENT) || \
     random(2))

#endif /* !_BOAT_DEFINITIONS_ */
