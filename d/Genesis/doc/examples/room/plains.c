#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>

#define OAK_ROOM "/doc/examples/room/oak.c"

inherit "/std/room";

string branch_desc();
int climb(string args);

object orc;

public void
create_room()
{
    set_short("under the oak");
    set_long("You are standing under a great oak. Around you a vast " +
	     "plain stretches out in every direction. The brisk wind " +
	     "ripples furiously through the thick grass.\n");
    
    add_item(({"oak", "great oak"}), "The oak look quite old. It would " +
	     "require at least three men to circle its trunk and it " +
	     "stretches its branches high and wide.\n");
    add_item(({"branches", "foliage" }), &branch_desc());

    add_prop(ROOM_I_INSIDE, 0);
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
   (OAK_ROOM)->load_me();
   return ({    (OAK_ROOM),
                "[on] [in] [the] 'oak' / 'branches' / 'tree'",
                "in the oak",
                "the plain below" });
}

public void
init()
{
    add_action(climb, "climb");
}

int
climb(string args)
{
    if (args != "up" && args != "oak" && args != "tree")
    {
	notify_fail("Climb oak?\n");
	return 0;
    }
    
    write("You climb up the trunk of the oak.\n");
    tell_room(this_object(), QCTNAME(this_player()) +
	      " climbs up the trunk of the oak.\n", ({ this_player() }));
    tell_room(OAK_ROOM, QCTNAME(this_player()) + " arrives from below.\n",
	      ({ this_player() }));
    this_player()->move_living("M", OAK_ROOM);
    return 1;
}		

string
branch_desc()
{
    object *seen;
    
    seen = FILTER_LIVE(OAK_ROOM->subinventory());
    seen = FILTER_CAN_SEE(seen, this_player());
    
    if (sizeof(seen))
    {
	return "The branches stretches far over your head.\n" +
	    "You see " + COMPOSITE_LIVE(seen) + " clinging to " +
	    "a thick branch high above you.\n";
    }
    else
    {
	return "The branches stretches far over your head.\n";
    }
}

public void
reset_room()
{
    // This orc is a sittin duck.
    
    if (!orc)
    {
	orc = clone_object("/std/monster");
	orc->set_race_name("orc");
	orc->set_adj("stray");
	orc->set_short("stray orc");
	orc->set_long("It looks lost and folorn, an easy pray for " +
		      "hunting elves.\n");
	orc->add_chat("Hilfe!");
	orc->add_chat("Me miss mi Uruk.");
	orc->set_chat_time(65);
	orc->add_act("sniff");
	orc->add_act("sob");
	orc->set_act_time(45);	
	orc->set_stats(({ 40, 30, 40, 25, 25, 20 }), 10);
	orc->add_prop(LIVE_I_NEVERKNOWN, 1);
	orc->heal_hp(2000);
	orc->move(this_object(), 1);
    }

    ::reset_room();
}
