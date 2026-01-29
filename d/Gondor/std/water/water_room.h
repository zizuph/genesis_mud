/*
 * /d/Gondor/std/water/water_room.h
 *
 *  Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * defines for /d/Gondor/std/water/water_room.c
 *
 */

#ifndef	_WATER_ROOM_DEFINITIONS_
#define	_WATER_ROOM_DEFINITIONS_

#ifndef NO_GONDOR_DEFS
#include	"/d/Gondor/defs.h"
#endif /* NO_GONDOR_DEFS */

/***** properties *****/
#define	LIVE_I_FLOAT_DIR	"_live_i_float_dir"

#define	OBJ_I_WATER_MOVE	"_obj_i_water_move"
#define	    WATER_MOVE_SWIM	1
#define	    WATER_MOVE_FLOAT	2
#define	    WATER_MOVE_WADE	3
#define	    WATER_MOVE_ROW	4
#define	    WATER_MOVE_ASHORE	5

#define	OBJ_I_FLOAT		"_obj_i_float"
#define	OBJ_I_SINK		"_obj_i_sink"
#define	OBJ_I_BOAT		"_obj_i_boat"
#define	OBJ_I_ELVEN_BOAT	"_obj_i_elven_boat"
#define	OBJ_I_BOAT_SKILL	"_obj_i_boat_skill"
#define OBJ_I_SWAM_HERE         "_obj_i_swam_here"
#define	OBJ_I_NO_WASH		"_obj_i_no_wash"
#define	OBJ_I_WATER_ALARM	"_obj_i_water_alarm"
#define	OBJ_I_NO_CAPSIZE	"_obj_i_no_capsize"
#define	OBJ_I_HIT_ROCK		"_obj_i_hit_rock"

/* SS_BOAT_HANDL is defined in /d/Gondor/defs.h */


/***** magic #'s for currents *****/

/* don't change these lightly -- fatigue numbers "know" this range */
#define MIN_CURRENT	 0	/* still water		*/
#define	MODERATE_CURRENT 3
#define	ROUGH_CURRENT	 7
#define MAX_CURRENT	10	/* torrential currents	*/

/* give main current (Downstreamdir[0]) extra weight when choosing
 * a random direction
 */
#define	MAIN_CURRENT_WEIGHT	2

/***** #'s for rocks *****/
/* range is 0 (none) - 10 (grinders of death) */
#define	SCATTERED_ROCKS	 3	/* past this, mention in default descs */
#define	ROCKY		 7	/* damage starts being a concern */
#define	MAX_ROCKS	10	/* lethal if there's much current */



/***** #'s for depth *****/
#define	DEFAULT_DEPTH	304	/* 10 feet */
#define	MIN_SWIM_DEPTH	91	/*  3 feet */
#define	MAX_WADE_DEPTH	152	/*  5 feet */



/* delay between object entering and sinking.  use dead-simple for now */
#define SINK_ALARM(str)         2.0


/***** stuff for computing swim/float fatigue and damage *****/

#define	LIMIT_SKILL	60	/* past this, it doesn't get easier
				 *	for very strong currents
				 */
#define	START_INDEX	 4	/* index in Fatigue_arr for skill 10
				 * 	currentstr 1
				 */
#define	LIMIT		10	/* LIMIT_SKILL/10 + START_INDEX */
#define	ENCUMBERANCE	70	/* penalized if encumberance is >= this */

#define	DOES_FLOAT(ob) \
    (!(ob)->query_prop(OBJ_I_SINK) && \
     ((ob)->query_prop(OBJ_I_FLOAT) ||  \
      ((ob)->query_prop(OBJ_I_WEIGHT) < (ob)->query_prop(OBJ_I_VOLUME))))

/* # of hp to reduce when too exhausted to swim for current str 's'
 * and max hp 'h'
 */
#define	CURRENT_DAMAGE(s, h)	( ((h) / 10) + ( ((s) / 3) * ((h) / 10) ) )

/* magic number 25 taken from std/combat/cbase.c's cb_may_panic() */
#define	PANIC_AMOUNT	25

/* PANIC_FATIGUE returns the fatigue for a panic'd player, given
 * a un-panic'd fatigue 'f'
 */
#define	PANIC_FATIGUE(f)	((f) * 2)


/***** path/object names *****/

#define	WATER_DIR	"/d/Gondor/std/water/"
#define	ONWATER		(WATER_DIR+"onwater")
#define	POCKET		(WATER_DIR+"pocket")
#define	BREATH_OBJ	(WATER_DIR+"breath_obj")
#define	BREATH_OBJ_NAME	"Breath_Object"


/***** make this a macro so we can change the test if needed *****/
#define	IS_BOAT(ob)	((ob)->query_prop(OBJ_I_BOAT))

/***** placeholder ... someday we'll have elven boats *****/
#define	IS_ELVEN_BOAT(ob)	((ob)->query_prop(OBJ_I_ELVEN_BOAT))

/***** general purpose macros *****/

#ifndef ARRAY
/* return v if v is an array; otherwise return array containing v */
#define	ARRAY(v)	(pointerp(v) ? (v) : ({ (v) }))
#endif /* !ARRAY */


/* logging macros.
 * i anticipate that INFO_LOG (e.g., player drowns) and ERR_LOG
 * (something went wrong) will always be defined.  however, after
 * things settle down, can comment out the first DEBUG_LOG (or TMP_LOG)
 * and uncomment the second to turn off debugging (or tmp logging)
 */
#define	INFO_LOG(x)	log_file("water", \
	"INFO "+ctime(time())+" "+file_name(this_object())+"\nINFO\t"+x);
#define	ERR_LOG(x)	log_file("water", \
	"ERR "+ctime(time())+" "+file_name(this_object())+"\nERR\t"+x);
#define	DEBUG_LOG(x)	log_file("water", \
	"DBG "+ctime(time())+" "+file_name(this_object())+"\nDBG\t"+x);
#define	TMP_LOG(x)	log_file("water", \
	"TMP "+ctime(time())+" "+file_name(this_object())+"\nTMP\t"+x);
/* #define	DEBUG_LOG(x)			/* logging off */
/* #define	TMP_LOG(x)			/* logging off */


/***** debugging macros & props *****/

#define	GNADNAR_DEBUGGING	"_gnadnar_debugging"
#define	GNADNAR_NAZGUL		"_gnadnar_nazgul"


#define	DBG(o, s) \
	if (o->query_prop(GNADNAR_DEBUGGING)) \
	  { tell_object((o), ctime(time())+" "+(s)); }


#define	NAZGUL(p) \
	( (p)->query_nazgul() || (p)->query_prop(GNADNAR_NAZGUL) )


#endif /* !_WATER_ROOM_DEFINITIONS_ */
