/*
 * Coded by Amelia, 4/10/98
 * farm in Gont
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>

private int manure, stuff_found;

public void
create_earthsea_room()
{
    set_short("Farm path");
    set_long("You are walking along a " +
        "dirt path on a farm. Just to the south you see " +
        "a large outbuilding constructed from old grey pine planks. " +
        "To the north is a cobblestone road. " +
        "There is a hay stack to the east of the outbuilding " +
        "and a huge heap of manure to the west.\n");
    add_item((({"manure", "heap of manure", "heap"})),
        "The manure is what the farmer spreads on the " +
        "fields for fertilizer.\n");
    add_item((({"outbuilding", "thatched roof"})),
        "The outbuilding is made from weathered pine planks, and " +
        "the planked roof is covered with thatch.\n");
    add_item((({"hay stack", "hay", "stack"})),
        "The stack of hay is about as high as a " +
        "tall man and is stacked into a round shape.\n");
    add_prop(OBJ_S_SEARCH_FUN, "find_stuff");
    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_exit("cobbled_road5", "north");
    add_exit("barn", "south");
    reset_room();
}

public void
reset_room()
{
    stuff_found = 0;
    manure = 1;
}

public string
find_stuff(object player, string str)
{
    object stuff, tp = this_player();

    switch(str)
    {
        case "hay":
        case "hay stack":
        case "stack":
            if(!stuff_found)
            {
                stuff = clone_object("/d/Earthsea/gont/tenalders/wep/pitchfork");
                stuff_found = 1;

                if(stuff->move(tp))
                {
                    stuff->move(this_object());
                }

                return "You find a " + stuff->query_short() +
                    " in the hay stack!\n";
            }
        break;
        case "manure":
        case "heap of manure":
        case "heap":
            if(manure)
            {
                clone_object(
                    "/d/Earthsea/gont/tenalders/obj/items/manure"
                )->move(tp, 1);
                manure = 0;
                return "You sift through the smelly manure " +
                    "and come up with a pile, as well as dirty hands.\n";
            }

            return "Yuk! You find nothing in the smelly manure.\n";
        break;
    }

    return "You find nothing of interest there.\n";
}
