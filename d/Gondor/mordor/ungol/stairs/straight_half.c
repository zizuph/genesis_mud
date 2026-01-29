/*
 * /d/Gondor/mordor/ungol/stairs/sstair_h.c
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
#include <filter_funs.h>
#include <macros.h>
#include "stairs.h"
#include <stdproperties.h>

#define UP_ROOM   (STAIRS_DIR + "straight6")
#define DOWN_ROOM (STAIRS_DIR + "straight5")

/*
 * Function name: create_room
 * Description  : This function is called to create the room. For this room
 *                is slightly different from the other rooms on the Straight
 *                Stair I do not make a call to make_the_room(), but make
 *                necessary calls here.
 */
void
create_room()
{
    set_short("On a platform on the Straight Stair in the Mountains of " +
        "Shadow");
    set_long(BSN("This is a little platform on the Straight Stair leading " +
        "up and down in the Mountains of Shadow, Ephel Duath. On either " +
        "side of the stair are steep walls, making it impossible to escape " +
        "from this place another way than by climbing up or down the stair, " +
        "which might be a hard task to perform."));

    add_walls();
    add_mountain();
    add_stair();

    add_prop(ROOM_I_NO_ME_SUN, 1);
    add_prop(OBJ_S_WIZINFO,
        BSN("You are on the Straight Stair. The first stairs on the " +
        "journey to Torech Ungol, Shelobs lair. A player that tries to " +
        "climb this stair might just find himself lying hurt or even dead " +
        "at the foot or in this room halfway and those that survive will " +
	"have to climb the Winding Stairs before they enter the lair and " +
	"face Shelob... /Mercade"));
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
 * Function name: query_room_down
 * Description  : This is an ugly function to allow me to define DOWN_ROOM
 *                in this file and access it from the inherited file.
 */
string
query_room_down()
{
    return DOWN_ROOM;
}

/*
 * Function name: query_room_up
 * Description  : This is an ugly function to allow me to define UP_ROOM in
 *                this file and access it from the inherited file.
 */
string
query_room_up()
{
    return UP_ROOM;
}

/*
 * Function name: no_fall_down
 * Description  : This function is to make sure that you cannot fall down
 *                while trying to climb up. When climbing down, you can
 *                fall down.
 * Returns      : 1 - always.
 */
int
no_fall_down()
{
    return 1;
}
