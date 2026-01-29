/*                                                                        *
 *  file name:   ~ziggurat.h                                              *
 *  creator:     Zielia                                                   *
 *  last update:                                                          *
 *  purpose:   File to hold defines for Ziggurat files                    *
 *  note:                                                                 *
 *  bug(s):                                                               *
 *  to-do:                                                                *
 */
#ifndef __AVENIR_ZIGGURAT
#define __AVENIR_ZIGGURAT

#include "../city.h"
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"

/* Our rotating log inherit. */
#define RLOG	"/d/Avenir/inherit/logrotate"

/* All Ziggurat files: now defined in "../city.h"
#define ZIG		(CITY + "zigg/")
 */

/* Where to put Ziggurat specific log files. */
#define ZIG_LOGS	"/d/Avenir/log/zigg/"

/* Where to find inheritables */
#define ZIG_LIB		(ZIG + "lib/")

/* Where to find objects */
#define ZIG_OBJ		(ZIG + "obj/")

/* Where to find food and drinks */
#define ZIG_FOOD	(ZIG + "food/")

/* Where to find rooms */
#define ZIG_RL1		(ZIG + "level1/")
#define ZIG_RL2		(ZIG + "level2/")
#define ZIG_RL3		(ZIG + "level3/")
#define ZIG_RL4		(ZIG + "level4/")
#define ZIG_RLG		(ZIG + "garden/")

/* Where to find monsters */
#define ZIG_MON		(ZIG + "mon/")

/* Standard inherits / base files */
#define ZIG_NPC		(ZIG_LIB + "npc")
#define ZIG_ROOM	(ZIG_LIB + "room")

/* The Ziggurat clock */
#define AVTIME		(ZIG_LIB + "avtime")

/* Clothmaker */
#define CM		(ZIG_LIB + "clothmaker")

/* Master eye subloc object */
#define EYES_OBJ	(ZIG_OBJ + "eyes_obj")
#define EYES_NAME	 "zigg::eyes::object"

/* General Zigg props */
#define PROP_I_CLEANSED  "_cleansed_for_ziggurat"
#define PROP_I_SEE_TRUE  "_live_i_see_through_illusion"
#define CAN_SEE_TRUE(x)  (x)->query_prop(PROP_I_SEE_TRUE)

/* Default Recovery lost % */
#define RECOVERY_LOST  25

/* If defined, unknown "asks" to NPC's will be logged here. */
#define LOG_QUESTIONS	(ZIG_LOGS + "asks")


/*  Q U E S T S  */

/* Inherit file for quests, has reward_quest() function. */
#define QUEST	"/d/Avenir/inherit/quest"

/* Ziggurat quests are in group 1. */
/* Ziggurat has bits 10-19 reserved. */
#define ZQ_GROUP	1
/*
 * LEGEND:
 *
 *   ZQB_*  ==  Ziggurat Quest Bit
 *   ZQE_*  ==  Ziggurat Quest Experience
 *   ZQN_*  ==  Ziggurat Quest Name
 */
/* Ry'nal's Gift */
#define ZQB_RYNAL	10
#define ZQE_RYNAL	3000
#define ZQN_RYNAL	"Ry'nal's Gift"
#define RYNAL_I_QUEST	"__rynal_i_questing"
/* Custom Perfumes */
#define ZQB_PERFUME	11
#define ZQE_PERFUME	5000
#define ZQN_PERFUME	"Cheynal Perfumes"
/* Gemdust Delivery */
#define ZQB_GEMDUST	12
#define ZQE_GEMDUST	1000
#define ZQN_GEMDUST	"Gemdust Delivery"
#define IMLIS_I_QUEST   "__imlis_i_questing"

#endif  __AVENIR_ZIGGURAT
