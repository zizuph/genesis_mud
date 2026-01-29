/*
 * /d/Gondor/mordor/ungol/tower_quest.h
 *
 * This file contains the definitions for the quests at Cirith Ungol.
 * Every quest should at least have a (unique) number that can be used
 * to generate random and a list of hints. Those hints can take various
 * forms. They may be strings (words), numbers or filenames.
 *
 * Hint: make the quest number an odd number, which is better for the
 *       formula used in NAME2NUM and make the number smaller than the
 *       square root of MAXINT defined in /std/macros.h
 *
 * /Mercade, 4 June 1994
 *
 * Revision history:
 */

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

/*
 * NAME2NUM(s, r, c)
 *
 * This function can be used to get a random number within a certain range.
 * The special effect is that every player gets the same number each time
 * the function is called. Therewith you can give player individually
 * adjusted hints or solutions.
 *
 * s - the name of the player solving the quest
 * r - the range for the random, the functions returns in [0..(r-1)]
 * c - a special code number, should be unique for each quest
 */
#define NAME2NUM(s, r, c) \
    call_other((COMMON_DIR + "lib/name2num"), (s), (r), (c))

#define DOMAIN_NAME         "Gondor"

#define MOVING_FLOOR_GROUP  
#define MOVING_FLOOR_BIT    
#define MOVING_FLOOR_EXP    
#define MOVING_FLOOR_NAME   "CIRITH UNGOL MOVING FLOOR"
#define MOVING_FLOOR_CODE   29067
#define MOVING_FLOOR_HINTS  ({ })

/*
 * /d/Gondor/mordor/obj/balance_colour.c
 */
#define BALANCE_RWB_GROUP       0
#define BALANCE_RWB_BIT         0
#define BALANCE_RWB_EXP       500
#define BALANCE_RWB_NAME    "CIRITH UNGOL RWB BALANCE"
#define BALANCE_RWB_CODE    10253
#define BALANCE_RWB_HINTS   ({ "CGFL", "RTJB", "WVRB", "DLVG", "ZNKM", \
			       "CQWX", "LHNP", "SFMK", "SHDJ", "TPXZ" })

/*
 * /d/Gondor/mordor/obj/balance_mono.c
 */
#define BALANCE_MONO_GROUP  
#define BALANCE_MONO_BIT    
#define BALANCE_MONO_EXP    
#define BALANCE_MONO_NAME   "CIRITH UNGOL MONO BALANCE"
#define BALANCE_MONO_CODE   39861
#define BALANCE_MONO_HINTS  ({ })

