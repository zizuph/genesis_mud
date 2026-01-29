#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>

#define PLAIN_ROOM "/doc/examples/room/plains"
#define BOW "/doc/examples/weapons/elven_bow"
#define ARROWS "/doc/examples/weapons/black_feathered_arrow"

inherit "/std/room.c";

mixed dis_check();
int climb(string args);
string ground_desc();

public void
create_room()
{
    set_short("on a thick branch");
    set_long("You are clinging to a thick oak branch perilously high " +
	     "above the ground.\n");
    add_item(({"ground", "plain" }), &ground_desc());
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_ATTACK, &dis_check());

    add_object(BOW);
    add_object(ARROWS);
}

/*
 * Function:    query_range_targets
 *
 * Description: Returns information about adjacent rooms
 *              that you can reach with missile weapons
 *              from this room.
 *
 * Arguments:   (object) The person that wishes to fire
 *              into an adjacent room.
 *
 * Returns:     An array with the following content. If
 *              there is more then one room accessible
 *              from this room, each room pads their
 *              values to the array.
 *
 * ({ path to remote room, 
 *    matching pattern with parse_command syntax, 
 *    description of remote room,
 *    description of this room as seen from remote room 
 *  })
 *
 * Note that upon making it possible to shoot across
 * rooms, you better make your npc:s able to respond
 * to it so they won't be sitting ducks.
 *
 */

mixed 
query_range_targets(object archer)
{
   seteuid(getuid(this_object()));
   (PLAIN_ROOM)->load_me();
   return ({    (PLAIN_ROOM),
                "[at] [on] [the] 'ground' / 'plain'",
                "on the plain",
                "the branches above" });
}

public void
init()
{
    add_action(climb, "climb");
}

string
ground_desc()
{
    object *seen;
    
    seen = FILTER_LIVE(PLAIN_ROOM->subinventory());
    seen = FILTER_CAN_SEE(seen, this_player());
    
    if (sizeof(seen))
    {
	return "The plain stretch out in all directions far " +
	    "below you.\nYou see " + COMPOSITE_LIVE(seen) +
	    " standing on the ground.\n";
    }
    else
    {
	return "The plain stretch out in all directions far " +
	    "below you.\n";
    }
}

int
climb(string args)
{
    if (args != "down")
    {
	notify_fail("Climb down?\n");
	return 0;
    }
    
    write("You climb down.\n");
    tell_room(this_object(), QCTNAME(this_player()) +
	      " climbs down to the ground.\n", ({this_player()}));
    tell_room(PLAIN_ROOM, QCTNAME(this_player()) +
	      " arrives climbing down from the oak.\n", ({this_player()}));
    this_player()->move_living("M", PLAIN_ROOM);
    
    return 1;
}		

mixed
dis_check()
{
    if (environment(this_player()) == this_object() &&
	this_player()->query_base_stat(SS_DIS) < 100)
    {
	return "No way! It is like 40 feet down to the ground! " +
	    "You are definatly going to hug this branch until " +
	    "you are nice and safe on the ground again.\n";
    }
    else
    {
	return 0;
    }
}

