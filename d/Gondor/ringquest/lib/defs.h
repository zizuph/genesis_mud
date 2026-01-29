/*
 *	/d/Mordor/ringquest/lib/defs.h
 *
 *	Copyright (C) 1995 by Christian Markus
 *
 *	Definition for the Ring Quest.
 *
 *	Olorin, December 1995
 *
 *	Modification log:
 */
#include "/d/Gondor/defs.h"

#ifndef RINGQUEST_DEFINTIONS
#define RINGQUEST_DEFINTIONS
/*
 *	No definitions above this line.
 */
#define RQ_ERROR_LOG		"rq_errors"

#define ONE_RING_MASTER		(RQ_DIR + "obj/one_ring")

/*
 *      Useful defintions not in /d/Gondor/defs.h:
 */
#define HE(x)            ((x)->query_pronoun())
#define HIS(x)           ((x)->query_possessive())
#define HIM(x)           ((x)->query_objective())
 
/*
 *	No definitions below this line.
 */
#endif RINGQUEST_DEFINTIONS
