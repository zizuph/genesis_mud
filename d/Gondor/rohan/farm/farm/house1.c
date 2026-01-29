/*
 *	/d/Gondor/rohan/farm/farm/house1.c
 *	It belongs to a small farm in the Ered Nimrais.
 *
 *	Coded by Olorin, Nov 1992.
 *
 *	Modification log:
 *	29-Jan-1997, Olorin:	General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* How easy is it to find the corpse? */
#define MIN_AWARE	40 

public void    reset_room();

static object *Dunlist = allocate(2);

public void
create_gondor() 
{
    set_short("a small cottage");
    set_long(BSN("This is the only room of the small cottage. A whole family "
        + "seems to have lived here. Now the cottage is deserted and has been "
	+ "plundered. There are several blood stains on the floor, and someone "
        + "has made a heap from the furniture and burned it."));
    add_exit(FARM_DIR + "farm/yard1", "north", 0);

    add_item("heap", "The furniture has been burned. You can recognize "
        + "the remains of a table and of a large wooden bed. From the rest "
        + "only ashes remain.\n");
    add_item("furniture", "The furniture has been burned. You can recognize "
        + "the remains of a table and of a large wooden bed. Of the rest only "
        + "ashes remain.\n");
    add_item("corpse", "The corpse is lying in the ashes, hidden by the "
        + "half-burned furniture. It was mutilated before it was burned. This "
        + "was probably the farmer who lived on this farm. You still can see "
        + "that he was a rohirrim, and you wonder what happened to his family.\n");
    add_item( ({"ash", "ashes"}), "These ashes look like what remains "
        +  "of the furniture. There is a corpse lying in them.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    reset_room();
}

public void
reset_room() 
{
    clone_npcs(Dunlist, NPC_DIR + "farm/dunlending", 10.0);
}

public string
do_search(object player, string str)
{
    int     skill = player->query_skill(SS_AWARENESS);
    
    if (strlen(str) && ((str == "heap") || (str =="furniture") || (str =="ashes")))
    { 
	if (skill > (MIN_AWARE / 2 + random(MIN_AWARE) + 1))
        {
	    return "There is a corpse lying in ashes, hidden by the "
		+  "half-burned furniture.\n";
	}
	return "You cannot find anything but a half-burned table and bed, but "
	    +  "you cannot see what is lying under it.\n";
    }
    return 0; 
}

