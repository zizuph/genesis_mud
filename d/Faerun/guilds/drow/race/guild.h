/*
 * drow/race/guild.h
 *
 * This is the master defines file for the drow racial guild.
 */
#ifndef __DROW_RACIAL_GUILD__
#define __DROW_RACIAL_GUILD__

#include "../drow.h"

/* General guild defines. */
#define GUILD_TAX       5
#define GUILD_TYPE      "race"
#define GUILD_STYLE     "race"
#define GUILD_NAME      DROW_R_GUILD
#define GUILD_SOUL      (P_DROW_RACIAL + "soul")
#define GUILD_SHADOW    (P_DROW_RACIAL + "shadow")
#define GUILD_OBJECT    (P_DROW_RACIAL + "object")
#define GUILD_LOGS      (P_DROW_RACIAL + "logs/")
#define GUILD_HELP      (P_DROW_RACIAL + "help/")
#define GSERVER         DROW_R_SERVER
#define GOBJECT_NAME    DROW_R_OBJECT
#define MESS_DIR        (DROW_DIR + "messengers/")

/* Our default logfile settings. */
#define BANLOG          (GUILD_LOGS + "general")
#define JOINLOG         (GUILD_LOGS + "general")
#define LEFTLOG         (GUILD_LOGS + "general")
#define HOUSELOG        (GUILD_LOGS + "houses")

/* This uses Faerun custom time2format function. */
#define GLOG(log, msg)  write_log((log), \
    time2format(time(), "mm-dd-yyyy tt: ") + (msg) +"\n", 250000, 10)

/* Indexes into the members guild data array,
 * as used in server.c and shadow.c */
#define M_TYPE     0
#define M_OPTIONS  1
#define M_HOUSE    2
#define M_CITY     3
#define M_DEITY    4
#define M_ACTIVE   5

/* These are the various 'type' values a member may have. */
#define GUILD_MEMBER        1
#define HOUSE_MEMBER        2
#define HOUSE_NOBLE         4
#define HOUSE_MATRON        8
#define HOUSE_PATRON       16
#define HOUSE_DAUGHTER     32
#define HOUSE_WMASTER      64
#define HOUSE_WIZARD      128  

/* How long a Matron may be idle before
 * the leadership may be forcibly changed. */
#define MAX_IDLE      7776000  /* 90 days */

/* Indices into the 'houses' mapping. */
#define H_CITY     0
#define H_MEMBERS  1
#define H_APPLY    2
#define H_RANKS    3
/* House ranks indices for the mapping */
#define HR_MATRON    "matron"
#define HR_DAUGHTER  "daughter"
#define HR_PATRON    "patron"
#define HR_WMASTER   "wmaster"
#define HR_FNOBLES   "fnobles"
#define HR_MNOBLES   "mnobles"
#define HR_WIZARD    "wizard"

/* These are appointable ranks within the drow Houses.
 * mapping ([ (string)rank: (mixed *)({
 *   (string)Title, (int)Appointable,
 *   (int)Type, (int *)({ male limits, female limits, neuter }),
 *      }), ])
 */
#define DROW_RANKS  ([ \
   HR_MATRON:   ({ "Matron Mother",  0, HOUSE_MATRON,   ({ 0, 1, 0 }) }),  \
   HR_DAUGHTER: ({ "First Daughter", 1, HOUSE_DAUGHTER, ({ 0, 1, 0 }) }),  \
   HR_PATRON:   ({ "Patron"       ,  1, HOUSE_PATRON,   ({ 1, 0, 0 }) }),  \
   HR_WMASTER:  ({ "Weapons Master", 1, HOUSE_WMASTER,  ({ 1, 0, 0 }) }),  \
   HR_FNOBLES:  ({ "Noble Daughter", 1, HOUSE_NOBLE,    ({ 0, 3, 0 }) }),  \
   HR_MNOBLES:  ({ "Noble Son",      1, HOUSE_NOBLE,    ({ 3, 0, 0 }) }),  \
   HR_WIZARD:   ({ "House Wizard",   1, HOUSE_WIZARD,   ({ 1, 0, 0 }) }),  \
])
/* Indices into the mapping arrays */
#define DR_TITLE   0
#define DR_APPNT   1
#define DR_TYPE    2
#define DR_LIMIT   3

/* This is the Master list of joinable Drow cities
 * and the joinable Houses within those cities. */
/* mapping ([ (string)City: ({ (string *)Houses, (string)helpfile, }), ]) */
#define DROW_CITIES ([            \
	"Ched Nasad": ({ ({       \
		"Arkhenneld",     \
		"Zauvirr",        \
	}), "ched_nasad", }),     \
	"Menzoberranzan": ({ ({   \
		"Fey-Branche",    \
		"Mizzrym",        \
		"Xorlarrin",      \
	}), "menzo", }),          \
	"Sshamath": ({ ({         \
		"Khalazza",       \
		"T'orgh",         \
		"Vyllshan",       \
	}), "sshamath", }),       \
	"Thal'katkhact": ({ ({    \
		"Eveningsky",     \
		"Sweetkiller",    \
	}), "thal_k", }),         \
])

#endif  __DROW_RACIAL_GUILD__
