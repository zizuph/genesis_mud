/*
 * coded by Amelia 6/1/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>

private int bear_found = 0;

public void
create_earthsea_room()
{
    set_short("Troll cave");
    set_long("This appears to be the home of some " +
        "rather nasty creature. Damp and slimy, there are " +
        "bits of bone and dead fish heads lying about from " +
        "someone's supper. A heap of junk lies next to the wall.\n");
    add_item((({"junk", "heap", "heap of junk"})),
        "You see a heap of junk piled caringly next to the " +
        "wall, possibly the creature's treasure trove, stolen from " +
        "people's houses unaware.\n");
    add_item((({"bits of bone", "bone", "fish heads", "heads"})),
        "Bits of bone and slimy fish heads lie strewn about the floor " +
        "of the cave.\n");
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(OBJ_S_SEARCH_FUN, "find_junk");
    add_exit("under_bridge", "west");
}

public void
reset_room()
{
    bear_found = 0;
}

public string
find_junk(object player, string str)
{
    object bear;

    if(str == "junk" || str == "heap of junk" ||
        str == "heap")
    {
        if(!bear_found)
        {
            bear = clone_object("/d/Earthsea/gont/gont_city/obj/teddy_bear");
            bear->move(player);
            bear_found = 1;
            return "You find something warm and fuzzy in the heap!\n";
        }

        return "You find nothing in the junk.\n";
    }

    return "You find nothing of interest there.\n";
}
