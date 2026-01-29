/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's parlour
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>

private int basket_found = 0;

public void
create_earthsea_room()
{
    object door;
    set_short("Entry way");
    set_long("The entrance to this hut has a low " +
        "ceiling, where you can see the thatched roofing " +
        "over the support poles. It is sparsely furnished " +
        "with just a carpet on the packed earthen floor " +
        "and a wooden shelf for storage. There is a " +
        "low arched doorway leading northwest.\n");
    add_item((({"ceiling", "thatched roofing", "poles",
        "roofing", "support poles"})),
        "You can see the inner side of the roofing, " +
        "constructed of sod and thatch, where " +
        "there is a dense network of roots. " +
        "Lodge poles of pine support the edifice.\n");
    add_item((({"carpet", "earthen floor",
        "packed earthen floor"})),
        "The earthen floor is dug below ground level " +
        "a short step, and is packed hard as rock. " +
        "The faded red carpet is long and rectangular, " +
        "going from the door to the exit in the " +
        "north.\n");
    add_item((({"shelf", "wooden shelf"})),
        "There is a wooden shelf attached to the wall, " +
        "apparently for storing things on.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "find_basket");
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_exit("witch_kitchen", "northwest");
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/witch_door_e");
    door->move(this_object());
    reset_room();
}

public void
reset_room()
{
    basket_found = 0;
}

public string
find_basket(object player, string str)
{
    object basket;

    if((str == "shelf" || str == "wooden shelf") &&
        (!basket_found))
    {
        basket = clone_object("/d/Earthsea/gont/tenalders/obj/items/basket");
        basket->move(player);
        basket_found = 1;
        return "You find a basket on the shelf!\n";
    }

    return "You find nothing of interest there.\n";
}
