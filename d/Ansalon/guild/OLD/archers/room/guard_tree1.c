/* File name: guard_tree1.c
 *
 * The tree with an archer guarding entrance to the guild.
 *
 * Blizzard, 5.11.2003.
 *
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include "/d/Krynn/qualinesti/local.h"
#include "../guild.h"

#define   CAMP_ROOM         GUILD_ROOM + "entrance.c"

inherit   "/std/room.c";

mixed     dis_check();
int       climb(string args);
string    ground_desc();
string    camp_desc();

object    guard;


public void
create_room()
{
    set_short("on the tree, high above the ground");
    set_long("You are standing on a solid oaken branch high above the " +
	     "ground. Not so far to the south over the treetops you see the " +
	     "high towers of Qualinost. The city amazes you with its " +
	     "beauty. From this place you have also perfect view on the " +
	     "forest below.\n");
	     
    add_item(({"camp", "encampment"}), &camp_desc());
    add_item(({"path", "ground", "forest"}), &ground_desc());
    add_item(({"treetops", "treetop"}),
        "You climb the trunk a bit higher and look around. The forest " +
        "stretches out in all directions. To the south you see " +
        "the towers of Qualinost.\n");
    add_item(({"tower", "towers", "qualinost", "Qualinost"}),
        "Not so far in the distance, you see the high towers of the " +
        "elven city of Qualinost.\n");
 
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_M_NO_ATTACK, &dis_check());
    
    reset_room();
    
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
   (CAMP_ROOM)->load_me();
   return ({    (CAMP_ROOM),
                "[at] [on] [the] 'ground' / 'path'",
                "on the ground",
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
    
    seen = FILTER_LIVE((CAMP_ROOM)->subinventory());
    seen = FILTER_CAN_SEE(seen, this_player());
    
    if (sizeof(seen))
    {
	return "The Qualinesti forest stretches out in all directions. " +
	    "There is a path leading through the bushes down below you. " +
	    "The archers' training camp is to the north.\n" +
	    "You see " + COMPOSITE_LIVE(seen) +
	    " standing on the ground.\n";
    }
    else
    {
	return "The Qualinesti forest stretches out in all directions. " +
	    "There is a path leading through the bushes down below you. " +
	    "The archers' training camp is to the north.\n";
    }
}

string
camp_desc()
{
    return "Just to the north, the elven archers have set their training " +
        "camp.\n";
}

climb(string args)
{
    if (args != "down")
    {
	notify_fail("Climb down?\n");
	return 0;
    }
    
    write("You climb down to the ground swiftly.\n");
    tell_room(this_object(), QCTNAME(this_player()) +
	      " climbs down to the ground.\n", ({this_player()}));
    tell_room(CAMP_ROOM, QCTNAME(this_player()) +
	      " arrives climbing down from one of the trees.\n", 
	      ({this_player()}));
    this_player()->move_living("M", CAMP_ROOM);
    
    return 1;
}		

mixed
dis_check()
{
    if (environment(this_player()) == this_object() &&
	this_player()->query_base_stat(SS_DIS) < 90)
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

public void
reset_room()
{
    if ( !guard )
    {
	guard = clone_object(GUILD_NPC + "guard1");
	guard->move(TO, 1);
        guard->command("hide");
    }
    
    ::reset_room();
}
