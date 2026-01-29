/*
 * /d/Gondor/mordor/ungol/stairs/stairs.h
 *
 * This is a file that defines some macros and variables that I use at the
 * stairs leading to Torech Ungol, Shelobs lair.
 *
 * /Mercade, 22 November 1993
 *
 * Revision history:
*  Jan 2000, Morbeche:  Since Adv Guild climb skill has gone
*                            from 50 to 30, need to adjust 
*                             difficulty
 */

#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <stdproperties.h>

/*
 * STAIRS_I_I_AM_FALLING_DOWN is the property that is used if a player falls
 * down on the stairs.
 */
#define STAIRS_I_I_AM_FALLING_DOWN "_stairs_i_i_am_falling_down"

/*
 * STAIRS_SEE_FALL_ADD_PANIC_LIVING is the level of panic you get added if
 * you see a living and STAIRS_SEE_FALL_ADD_PANIC_SOMETHING if you see
 * something falling down the stairs.
 */
#define STAIRS_SEE_FALL_ADD_PANIC_LIVING    40
#define STAIRS_SEE_FALL_ADD_PANIC_SOMETHING 15

/*
 * STRAIGHT_STAIR_FATIGUE_DOWN is the fatigue if you climb down.
 * STRAIGHT_STAIR_FATIGUE_UP   is the fatigue if you climb up.
 *
 * The level is dependant the encumerance of the player, p.
 */
#define STRAIGHT_STAIR_FATIGUE_DOWN(p) \
    (((p)->query_encumberance_weight() / 12) + 8)
#define STRAIGHT_STAIR_FATIGUE_UP(p) \
    (((p)->query_encumberance_weight() / 8) + 10)

/*
 * STRAIGHT_PLAYER_CLIMB_UP is the formula that is used to determine whether
 * the player can climb up, STRAIGHT_PLAYER_CLIMB_DOWN is used when p tries
 * to climb down.
 */
#define STRAIGHT_PLAYER_FAIL_UP(p)                                  \
    (random(96) >                                                  \
	(((p)->query_fatigue() * 50) / (p)->query_max_fatigue()) + \
    ((p)->query_skill(SS_CLIMB) -5) * 2) 
//    (p)->query_skill(SS_CLIMB))
#define STRAIGHT_PLAYER_FAIL_DOWN(p)                                \
    (random(95) >                                                  \
	(((p)->query_fatigue() * 50) / (p)->query_max_fatigue()) + \
((p)->query_skill(SS_CLIMB) - 5) * 2)
//  (p)->query_skill(SS_CLIMB))

/*
 * STRAIGH_STAIR_OBJECT_FALLS_DOWN is a random generator that is used to
 * determine whether an object falls down the stairs.
 *
 * o Is the object to test and p the player that caused o to enter the room.
 */
#define STRAIGHT_STAIR_OBJECT_FALLS_DOWN(o, p) \
    (random(50 + (p)->query_stat(SS_DEX) +     \
	(p)->query_skill(SS_ACROBAT)) < 40)

/*
 * STRAIGHT_HP_REDUCTION_ON_FALL defines the reduction in HP on a living o
 * that falls down for i 'parts' of the stair.
 */
#define STRAIGHT_HP_REDUCTION_ON_FALL(o, i) \
    ((((o)->query_prop(OBJ_I_WEIGHT) * (i) * (i)) / 625) + 50)

/*
 * STRAIGHT_CHANCE_CATCH_FALLING_OBJECT(o) returns the object of an array
 * of objects o that gets a falling object on his/her head.
 */
#define STRAIGHT_CHANCE_CATCH_FALLING_OBJECT(o) \
    ((random(10) < sizeof(o)) ? (o)[random(sizeof(o))] : 0)

/*
 * STRAIGHT_HP_REDUCTION_ON_HIT defines the reduction in HP if a victim v
 * gets an object o on his/her head after i 'falls' of the stair.
 */
#define STRAIGHT_HP_REDUCTION_ON_HIT(o, v, i) \
    ((((o)->query_prop(OBJ_I_WEIGHT) * (i) * (i)) / 625) + 10)

/*
 * LOG is a macro used to log certain actions. The time is automatically
 * added to it.
 */
#define LOG(text) \
   log_file("straight_stair", ctime(time()) + " " + (text) + "\n")
#define LOG_NAME(player) sprintf("%-12s", (player)->query_real_name())

