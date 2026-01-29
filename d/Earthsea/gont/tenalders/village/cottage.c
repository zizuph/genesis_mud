/*
 * Farmer cottage
 * Coded by Amelia 11/22/97
 * contains dish of cream for cat quest
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>
#include <macros.h>

private object ashel;
private int cream_found = 0;

public void
create_earthsea_room()
{
    object door;

    set_short("Small cottage");
    set_long("This is a very small but cosy cottage. " +
        "In the center of the room you see a wooden table, which is " +
        "set as if the inhabitant had just finished breakfast and " +
        "left in a hurry before washing up. There is a " +
        "feather bed against the south wall with a patchwork quilt. " +
        "Flower-print curtains cover the window on the east wall " +
        "but allow light to enter. In the corner behind the door " +
        "there is a rack with an old tattered cloak. An oak walking staff " +
        "stands alone in the corner.\n");
    add_item((({"wooden table", "table", "crockery", "dishes"})),
        "The wooden table occupies the center of the room " +
        "and contains some crockery with the remains of breakfast.\n");
    add_item((({"cloak", "rack", "old tattered cloak",
        "tattered cloak" })),
        "The rack is made of wood and has several hooks for " +
        "hanging cloaks. There is one old cloak on it now, " +
        "which looks like it has seen a lot of use.\n");
    add_item((({"feather bed", "bed", "quilt", "patchwork quilt"})),
        "There is a feather bed with a patchwork quilt lying " +
        "on it.\n");
    add_item((({"curtains", "window", "flower-print curtains" })),
        "Some colourful curtains cover the window and permit " +
        "some privacy, however, they are thin enough to let in " +
        "lots of light.\n");
    add_item((({"staff", "oak staff", "oak walking staff",
        "walking staff"})),
        "Standing in the corner you see a walking staff made " +
        "from oak, which looks like it is awaiting its master's " +
        "return.\n");
    reset_room();
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "find_stuff");
    add_prop(OBJ_I_SEARCH_TIME, 3);
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/cottage_in");
    door->move(this_object());
}

public void
reset_room()
{
    cream_found = 0;

    if(!ashel)
    {
        ashel = clone_object("/d/Earthsea/gont/tenalders/npc/ashel");
        ashel->move(this_object(), 1);
    }
}

public string
find_stuff(object player, string str)
{
    object cream, tp = this_player(), to = this_object();

    if(str == "table" || str == "wooden table" ||
        str == "dishes" || str == "crockery")
    {
        if(!cream_found)
        {
            seteuid(getuid(to));
            cream = clone_object("/d/Earthsea/gont/tenalders/obj/items/cream");
            cream->move(tp, 1);
            cream_found = 1;
            tell_room(to, QCTNAME(tp) + " finds something on the " +
                "table.\n", ({ tp }));
            return "You find a " + cream->query_short() + ".\n";
        }
    }

    return "You find nothing of interest there.\n";
}
