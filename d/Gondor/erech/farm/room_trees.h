/*
 * /d/Gondor/open/room_chairs/room_chairs.h
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * #defines for room_chairs
 */

#ifndef ROOM_TREE_DEFINITIONS
#define ROOM_TREE_DEFINITIONS

#define	LIVE_S_SITTING		"_live_s_sitting"
#define	TREE_S_SUBLOC	        "_tree_s_subloc"

#ifndef TREE_LOG_ERR
#define	TREE_LOG_ERR(s) \
	log_file("room_trees", ctime(time()) + " " + \
	    file_name(this_object()) + " " + (s));
#endif

#endif /* ROOM_TREE_DEFINITIONS */
