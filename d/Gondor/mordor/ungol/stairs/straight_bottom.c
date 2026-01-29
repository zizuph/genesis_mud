/*
 * /d/Gondor/mordor/ungol/stairs/sstair_b.c
 *
 * This is a part of the Straight Stair. I like these kind of rooms that have
 * all the fancy stuff in a default file.
 *
 * /Mercade, 22 November 1993
 *
 * Revision History:
 */

inherit "/d/Gondor/mordor/ungol/stairs/std_straight.c";

#include "/d/Gondor/defs.h"
#include "stairs.h"
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#define UP_ROOM (STAIRS_DIR + "straight1")

void
create_room()
{
    set_short("The bottom of the Straight Stair in the Mountains of Shadow");
    set_long(BSN("There is the first stair leading high into the Mountains " +
        "of Shadow. From here the Straight Stair goes almost straight up. " +
        "To the west is a narrow opening in the rock, hiding this stair."));

    add_mountain();
    add_stair();
    add_walls();
    add_item( ({ "opening", "narrow opening", "west wall" }),
        BSN("In the west wall you see a narrow opening. It hides the stair " +
        "from people that aren't too observative."));

    add_exit(STAIRS_DIR + "path4", "west");

    add_prop(ROOM_I_NO_ME_SUN, 1);
    add_prop(OBJ_S_WIZINFO,
        BSN("This room is the foot of the Straight Stair. The first stair " +
        "on the journey to Torech Ungol, Shelobs lair. A player that tries " +
        "to climb this stair might just find himself lying hurt or even " +
        "dead in this room and those that survive will have to climb the " +
        "Winding Stair before they enter the lair and face Shelob... " +
	"/Mercade"));
}

/*
 * Function name: do_down
 * Description  : This is a redefinition to make sure that you cannot climb
 *                down in this room.
 * Arguments    : string str - the command line argument.
 * Returns      : 0 - always
 */
int
do_down(string str)
{
    NFN0("You cannot climb down any further.");
}

/*
 * Function name: query_room_up
 * Description  : This is an ugly function to allow me to define UP_ROOM
 *                in this file and access it from the inherited file.
 */
string
query_room_up()
{
    return UP_ROOM;
}

/*
 * Function name: hit_living_with_falling_object
 * Description  : This function is called when something falls on your head.
 * Arguments    : obj - the object that comes falling in.
 */
void
hit_living_with_falling_object(object obj)
{
    object victim;
    object *players;
    int    prop = obj->query_prop(STAIRS_I_I_AM_FALLING_DOWN);
    int    hp;

    players = all_inventory(TO);
    players = FILTER_PLAYERS(players);
    players = filter(players, "not_falling", TO);
    players -= ({ obj });

    victim = STRAIGHT_CHANCE_CATCH_FALLING_OBJECT(players);

    if (!objectp(victim))
    {
	return;
    }

    hp = -STRAIGHT_HP_REDUCTION_ON_HIT(obj, victim, prop);
LOG("Falling on " + LOG_NAME(victim) + " hp: " + victim->query_hp() +
	hp + ", prop: " + prop + ".");
    victim->heal_hp(hp);

    if (victim->query_hp() <= 0)
    {
	tell_room(TO, QCTNAME(victim) + " is very unfortunate since " +
	    (living(obj) ? QTNAME(obj) : LANG_THESHORT(obj)) + " hits " +
	    OBJECTIVE(victim) + " falling down the stair and " +
	    PRONOUN(victim) + " dies as a consequence of the impact.\n",
	    ({ obj, victim }) );
	victim->catch_msg("You are definitely in the wrong place at the " +
	    "wrong time since " +
	    (living(obj) ? QTNAME(obj) : LANG_THESHORT(obj)) +
	    " lands on your head, causing your death on impact.\n");

	if (living(obj))
	{
	    obj->CATCH_MSG(" happens to be in the wrong place at the wrong " +
		"time since you land on " + POSSESSIVE(victim) +
		" head, causing " + POSSESSIVE(victim) + " death on impact.",
		victim);
	}

LOG(LOG_NAME(victim) + " died by a falling object.");
	victim->do_die(TO);
	return;
    }

    tell_room(TO, QCTNAME(victim) + " is very unfortunate since " +
	(living(obj) ? QTNAME(obj) : LANG_THESHORT(obj)) + " hits " +
	OBJECTIVE(victim) + " falling down the stair, hurting " +
	OBJECTIVE(victim) + " severely.\n",
	({ obj, victim }) );
    victim->catch_msg("You are definitely in the wrong place at the wrong " +
	"time since " + (living(obj) ? QTNAME(obj) : LANG_THESHORT(obj)) +
	" lands on your head, hurting your severely.\n");

    if (living(obj))
    {
	obj->CATCH_MSG(" happens to be in the wrong place at the wrong " +
	    "time since you land on " + POSSESSIVE(victim) +
	    " head, hurting " + OBJECTIVE(victim) + " severely.",
	    victim);
    }
}

/*
 * Function name: living_comes_falling_in
 * Description  : This function is called when a living falls into the room.
 * Arguments    : obj - the player that comes falling in.
 */
void
living_comes_falling_in(object obj)
{
    int prop = obj->query_prop(STAIRS_I_I_AM_FALLING_DOWN);
    int hp;

    LTELL_ROOM(TO, obj, "Suddenly, and with an awful noise, ",
	" comes tumbling down the Straight Stair.", obj);
    obj->catch_msg(BSN("... and finally you fall onto some solid rock."));

    hit_living_with_falling_object(obj);

    hp = -STRAIGHT_HP_REDUCTION_ON_FALL(obj, prop);
    obj->remove_prop(STAIRS_I_I_AM_FALLING_DOWN);
LOG(LOG_NAME(obj) + " falls " + prop + ", hp: " + obj->query_hp() + hp +
	", fatigue: " + obj->query_fatigue() + "(" +
	obj->query_max_fatigue() + ").");
    obj->heal_hp(hp);

    if (obj->query_hp() <= 0)
    {
	obj->catch_msg(BSN("The impact with the rock here at the bottom " +
	    "of the Straight Stair causes you do die."));
	LTELL_ROOM(TO, obj, "The impact with the rock here at the bottom " +
	    "of the Straight Stair causes ", " to die.", obj);

	obj->do_die(TO);
    }
}

/*
 * Function name: object_comes_falling_in
 * Description  : This function is called when an object falls into the room.
 * Arguments    : obj - the object that comes falling in.
 */
void
object_comes_falling_in(object obj)
{
    tell_room(TO, BSN("Suddenly, and with a rumbling noise, " +
	LANG_ASHORT(obj) + " comes tumbling down the Straight Stair."));

    hit_living_with_falling_object(obj);

    obj->remove_prop(STAIRS_I_I_AM_FALLING_DOWN);
}

/*
 * Function name: enter_inv
 * Description  : This function is called when an object enters the room.
 *                If it came falling, a message will be given, otherwize
 *                nothing happens.
 * Arguments    : obj  - the entering object
 *                from - the object 'obj' came from
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!(obj->query_prop(STAIRS_I_I_AM_FALLING_DOWN)))
    {
        return;
    }

    if (living(obj))
    {
        living_comes_falling_in(obj);
    }
    else
    {
	object_comes_falling_in(obj);
    }
}

/*
 * Function name: no_fall_down
 * Description  : This function is meant to indicate that people cannot
 *                fall down from this since they are already below.
 * Returns      : 1 - always
 */
int
no_fall_down()
{
    return 1;
}
