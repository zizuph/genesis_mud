/*
 * /d/Gondor/lebennin/sirith/farms/defs.h
 * local defs for the farms
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar).
 *
 */
 
#ifndef SIRITH_FARMS_DEFS
#define SIRITH_FARMS_DEFS

#include "/d/Gondor/lebennin/sirith/defs.h"


/* rooms where livestock may wander */
#define	LIVESTOCK_RESTRAIN	(SIRITH_FARMS_DIR + "fields/")

/* various searches succeed if
 *	SS_AWARENESS >= (MIN_AWARE + random(RANDOM_AWARE))
 */
#define	MIN_AWARE	10
#define	RANDOM_AWARE	 5

#define	SIRITH_FARMER		"_sirith_farmer"
#define	SIRITH_LIVESTOCK	"_sirith_livestock"
#define	SIRITH_MUD		"_sirith_mud"
#define	SIRITH_SCRAPS		"_sirith_scraps"

/* pig stuff ... */

#define	PIGNAME		"_sirith_farm_pig"
#define	PIGCORPSE	(PIGNAME+"_corpse")
#define	PIGWOODS (SIRITH_FARMS_DIR+"fields/pigwoods")	/* hiding place    */
#define	PIGSTY	 (SIRITH_FARMS_DIR+"farm1/pigsty")	/* home           */

#define	PIG_OK		0
#define	PIG_DRUNK	1
#define	PIG_HURT	2

/* min strength & damage in order for poisons to affect pig */
#define	MIN_POIS_STR	30
#define	MIN_POIS_DAM	50

#define	SIRITH_I_LED_PIG		"_sirith_i_led_pig"
#define	SIRITH_I_POIS_PIG		"_sirith_i_pois_pig"
#define	SIRITH_S_WAS_LED		"_sirith_s_was_led"
#define	SIRITH_S_WAS_POIS		"_sirith_s_was_pois"


#define	SIRITH_PIG_GOLD			 1
#define	SIRITH_PIG_ALIGN		50

#endif /* SIRITH_FARMS_DEFS */
