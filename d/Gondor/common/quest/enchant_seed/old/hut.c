/*
 *	/d/Gondor/common/quest/enchant_seed/hut.c
 *
 *	A hut in Druedain Forest where a retired ranger lives.
 *
 *	Coded by Elessar 1992
 *
 *	Modification log:
 *	15-Feb-1997, Olorin:	General revision.
 */	
#pragma strict_types

inherit "/d/Gondor/std/room.c";
#include "/d/Gondor/common/guild/lib/binbit.h"

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Ranger;

public void
create_gondor()
{
    set_short("inside a small hut");
    set_long(BSN("The inside of the hut seems just as small as the " +
	"outside indicated. There is not much here except a bed, a " +
	"chair and table, and a fireplace where a few cooking pots " +
        "are stacked on the mantelpiece. There is also a faint " +
	"odour of herbs in here, giving a certain freshness to the " +
	"air. An open door leads out, and a small window lets some " +
	"light in above the bed. The walls are of lumber, and " +
	"looks quite solid. On one wall you see a little shelf."));

    add_prop(ROOM_I_INSIDE,1);

    add_item("bed","It has been slept in quite recently.\n");
    add_item("chair","Home-made, of wood. Quite rickety and old actually.\n");
    add_item("table","The table is even more rickety than the chair.\n");
    add_item("fireplace","There is no fire in the fireplace right now.\n"+
        "On the mantelpiece are some cooking pots used in the fireplace.\n");
    add_item("shelf", "There is nothing on the shelf.\n");
    add_item("pots","The cooking pots are clean and empty. The occupant\n"+
	   "probably has some sense of hygiene.\n");
    add_item("mantelpiece","There are some cooking pots upon the mantelpiece.\n");
    add_item("window","It is just a plate of glass fit into the wall, impossible\n"+
	   "to open.\n");
    add_item("door","The door is open, letting light and fresh air into the hut.\n");
    add_cmd_item( ({ "green book from shelf", 
		     "little book from shelf",
		     "book from shelf", "spellbook from shelf", }), 
		  ({ "get", "take", }), 
		  "You don't see any books on the shelf.\n");

    add_exit(COMMON_DIR + "quest/enchant_seed/garden", "out", 0, 0);

    reset_room();
}

public void
reset_room()
{
    Ranger = clone_npc(Ranger, COMMON_DIR + "quest/enchant_seed/rranger");
}

