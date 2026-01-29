/*
 * /d/Gondor/lebennin/sirith/defs.h
 * 
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#ifndef	SIRITH_DEFS
#define	SIRITH_DEFS

#include	"/d/Gondor/defs.h"

/* for rooms that need sunrise/sunset effects */
#define	SIRITH_MASTER		(SIRITH_DIR + "master")

/* farms subdir */
#define SIRITH_FARMS_DIR	(SIRITH_DIR + "farms/")

/* default name for our doors */
#define	SIRITH_DOOR	"_sirith_door_"

/* logging macros. comment out the first DEBUG_LOG (or TMP_LOG)
 * and uncomment the second to turn off debugging (or tmp logging)
 */
#define	ERR_LOG(x)	log_file("sirith", \
	"ERR "+ctime(time())+" "+file_name(this_object())+"\nERR\t"+x);
#define	DEBUG_LOG(x)	log_file("sirith", \
	"DBG "+ctime(time())+" "+file_name(this_object())+"\nDBG\t"+x);
#define	TMP_LOG(x)			/* tmp logging off */


#endif /* SIRITH_DEFS */
