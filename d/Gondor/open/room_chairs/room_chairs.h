/*
 * /d/Gondor/open/room_chairs/room_chairs.h
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * #defines for room_chairs
 */

#ifndef ROOM_CHAIRS_DEFINITIONS
#define ROOM_CHAIRS_DEFINITIONS

#define	LIVE_S_SITTING		"_live_s_sitting"
#define	SITTING_S_SUBLOC	"_sitting_s_subloc"

#ifndef CHAIRS_LOG_ERR
#define	CHAIRS_LOG_ERR(s) \
	log_file("room_chairs", ctime(time()) + " " + \
	    file_name(this_object()) + " " + (s));
#endif

#endif /* ROOM_CHAIRS_DEFINITIONS */
