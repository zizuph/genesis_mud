/*
 * /d/Gondor/pelargir/pelargir_room.h
 *
 * Copyright (C) 1999 by Cooper Sherry (Gorboth) and
 *	Nancy L. Mintz (Gnadnar)
 *
 * base defs for pelargir
 *
 * TBD:
 *	what sections of town do we define?
 *	start with docks and streets, add others as we go ...
 */

#ifndef	_PELARGIR_DEFS
#define	_PELARGIR_DEFS

/* room types */
#define	TYPE_STREET	1
#define	TYPE_DOCKS	2
#define	TYPE_POOR	3
#define	TYPE_SQUARE	4


/* street names
 * using #define's removes the little inconsistencies:
 * "was it admiral street or admiral way"?  "shipwright street"
 * or "shipwright's street"? etc etc. of course, you can
 * still wonder about STREET_SHIPWRIGHT vs STREET_SHIPWRIGHTS,
 * but the driver will let you know if you get it wrong :-)
 */
#define	STREET_BEACON		"Beacon Street"
#define	STREET_BELFALAS		"Belfalas Way"
#define	STREET_MARKET		"Market Street"
#define	STREET_ADMIRAL		"Admiral Street"
#define	STREET_SHIPWRIGHT	"Shipwright Street"
#define	STREET_EARNIL		"Earnil Street"
#define	STREET_PEDDLERS		"Peddlers Lane"


/* similarly, using defines avoids mixtures of "north" 
 * and "northern", etc
 */
#define	PART_NORTH		"northern"
#define	PART_EAST		"eastern"
#define	PART_WEST		"western"
#define	PART_SOUTH		"southern"

/* various npc files */
#define	CITIZEN_FILE	(PELAR_DIR + "npc/citizen")
#define	THIEF_FILE	(PELAR_DIR + "npc/yngthief")
#define	SAILOR_FILE	(PELAR_DIR + "npc/swashb")
#define	RUFFIAN_FILE	(PELAR_DIR + "npc/ruffian")

#endif /* _PELARGIR_DEFS */
