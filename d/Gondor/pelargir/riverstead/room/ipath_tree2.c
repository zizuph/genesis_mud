/*
 *  NCAMP_ROOM + "ipath_tree2.c"
 *
 *  A woodland tree. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 28 September 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void        	create_gondor();
public string      	long_desc();
public string		b_message();

static object *Orc = allocate(2);

public void
create_gondor()
{
    set_short("high up in a large oak tree");
    set_long(&long_desc());

    sky_add_items();

    add_item(({"room", "area", "surroundings", "place", "woodland", 
        "tree", "woods"}), long_desc);
            
    add_item(({"branch", "branches", "leaf", "leaves"}), "The branches "
        + "form a barrier through which it is hard to see. That they are "
        + "presently covered with leaves only adds to the opaque nature of "
        + "your surroundings.\n");
    add_item(({"path", "meandering path"}), "As the tree stands in the center "
        + "of the path, you can view it by looking straight down. Yikes! That "
        + "made you queasy. Better hold on tight.\n");
    add_item(({"river", "anduin", "anduin river"}), "From here you get a clear "
        + "view of the Anduin, mightiest of rivers in Middle Earth. "
        + "There seems to be some sort of settlement built on the near bank.\n");
    add_item(({"bank", "settlement", "near bank"}), "On the bank of the Anduin "
        + "you see what look like small huts of the kind used by the peasant "
        + "farmers of the region.\n");
    add_item(({"hut", "huts"}), "The huts are made of wood, with roofs of straw. "
        + "The people who live there are obviously not wealthy, but skilled in "
        + "the craft of dwellings that keep out the elements.\n");
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(NCAMP_ROOM + "ipath_tree.c", "down", b_message, 2, 1);

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Orc, NCAMP_NPC + "orc_spy", -1.0);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}

public string
b_message()
{
    object actor;
    actor = this_player();
    
    write("You carefully move down the branches to a lower spot in the tree.\n");
    tell_room(environment(actor), QCTNAME(actor) + " carefully moves down the "
        + "branches to a lower spot in the tree.\n", 
        ({actor}));
}

string
long_desc()
{
    return "You have climbed into the highest branches of a grand oak tree. "
        + "Although the many branches and leaves below you obscure it, you can "
        + "still see parts of the meandering path below the tree."
        + sky_desc() 
        + " To the east, you get a clear view of the mighty river Anduin.\n";
}
