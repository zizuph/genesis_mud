/*
 * /d/Gondor/river/anduin/anduin.h
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 */


#ifndef	_ANDUIN_DEFS
#define	_ANDUIN_DEFS

#define	RIVER_ANDUIN_DIR	"/d/Gondor/river/anduin/"
#define	CARROCK_TO_LORIEN_DIR	(RIVER_ANDUIN_DIR+"carrock2lorien/")
#define	LORIEN_TO_RAUROS_DIR	(RIVER_ANDUIN_DIR+"lorien2rauros/")

/* XXX first cut. may need to be tweaked */

/* using '3', someone with con 170, completely unencumbered, can
 * float for 15 rooms before starting to take damage from exhaustion.
 * swimming, they last for only 3 rooms.
 */
#define	SWIM_FATIGUE_FOR_DISTANCE(f, d) \
	((d) > 3 ? (f * d / 3) : f)

#define	ROW_FATIGUE_FOR_DISTANCE(f, d) \
	((d) > 6 ? (f * d / 6) : f)

#endif /* _ANDUIN_DEFS */
