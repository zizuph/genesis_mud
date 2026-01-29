#ifndef __STEED_DEFINES__
#define __STEED_DEFINES__

/*
 * These are path defines to steed objects and default steed settings.
 */
#define STEED_PATH              "/d/Genesis/steed/new/"
#define STEED_RIDER_SHADOW      (STEED_PATH + "steed_sh")
#define STEED_LEAD_SHADOW       (STEED_PATH + "lead_sh")
#define STEED_PACK_SUBLOC       "_steed_pack_subloc"
#define STEED_MOUNT_SUBLOC      "_steed_mount_subloc"
#define STEED_RIDER_SUBLOC      "_steed_rider_subloc"
#define STEED_MAX_RIDERS        2
#define STEED_FOOD_BASE ({ \
        "apple", "oat", "hay", "oats", "carrot", "celery", "barley", \
        "sugar", "brocolli", \



// Standard rider's shadow for riding around.
// #define STD_RIDER_SHADOW STEED_PATH + "rider_shadow"
#define STD_RIDER_SHADOW    STEED_PATH + "rider_shadow"

// The feeding module.
#define FEEDING             STEED_PATH + "feeding"
// The leading shadow.
#define LEADER_SHADOW       STEED_PATH + "leader_shadow"
//#define LEADER_SHADOW "/d/Shire/bree/rooms/town/stable/obj/leader_shadow"
// Rider object with rider commands.
#define RIDER_OBJECT        STEED_PATH + "rider_object"
// Leader object with leader commands.
#define LEADER_OBJECT       STEED_PATH + "leader_object"                        })

#define STEED_LEAD_MAX(ob) \
                (((ob)->query_skill(SS_ANI_HANDL) / 15) + \
                (((ob)->query_base_stat(SS_STR) + \
                (ob)->query_base_stat(SS_WIS)) / 2) / 120)


/*
 * Use these to set a steeds size and check for their ability
 * to move amongst rooms via the LIVE_*_STEED props.
 */
#define STEED_NONE	0		/* None may pass 		*/
#define STEED_ALL	1		/* All may pass 		*/
#define STEED_MINI	(STEED_ALL + 1)	/* Faerie sized steed? 		*/
#define STEED_SMALL	(STEED_ALL + 2) /* Pygmia horse sized? 		*/
#define STEED_MEDIUM	(STEED_ALL + 3) /* Regular horse sized. 	*/
#define STEED_NORMAL	STEED_MEDIUM	/* See above 			*/
#define STEED_LARGE	(STEED_ALL + 4)	/* Elephant, gryphon sized?	*/
#define STEED_HUGE	(STEED_ALL + 5)	/* Dragon sized?		*/

#define STEED_MIN_SIZE	STEED_MINI
#define STEED_MAX_SIZE	STEED_HUGE

/*
 * Misc steed defines
 */
#define STEED_FATIGUE_XFACTOR	5	/* Additional fatigue for steeds */


#endif  __STEED_DEFINES__

