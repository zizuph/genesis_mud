/*
 * Coded by Ckrik, June 1998 
 * A Karg camp.
*/

#pragma strict_types
#pragma no_clone

inherit "/d/Earthsea/gont/tenalders/std/base_karg_camp";

#include "defs.h"
#include <stdproperties.h>

private object karg_1, karg_2, karg_3, karg_4;

public void
create_camp()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
    add_long("There is a large tent here. The camp extends to the north, " +
        "east, and west.\n");
    add_item(({"tent", "large tent"}),
        "The large canvas tent stands before you. A tent flap " +
        "covers the entrance to the tent.\n");
    add_item(({"flap", "entrance","tent flap"}),
        "The tent flap is just a large piece of canvas that covers the " +
        "entrance to the tent.\n");
    add_exit("karg_camp06", "north");
    add_exit("karg_camp04", "east");
    add_exit("karg_camp10", "west");
    reset_room();
}

public void
reset_room()
{
    object to = this_object();

    if((!objectp(karg_1)) && (!objectp(karg_2)) && (!objectp(karg_3)) &&
        (!objectp(karg_4)))
    {
        karg_1 = clone_object(KARG3);
        karg_1->move(to);
        karg_1->command("emote strides in.");
        karg_2 = clone_object(KARG3);
        karg_2->move(to);
        karg_2->command("emote strides in.");
        karg_3 = clone_object(KARG3);
        karg_3->move(to);
        karg_3->command("emote strides in.");
        karg_4 = clone_object(KARG5);
        karg_4->move(to);
        karg_4->command("emote strides in.");
    }
}

public int
tent(string str)
{
    if(str == "tent")
    {
        this_player()->move_living("entering the tent",
            "/d/Earthsea/gont/tenalders/south_path/camp_1/tent07");
        return 1;
    }

    return notify_fail("Enter what? The tent?\n");
}

public void
init()
{
    ::init();
    add_action(tent, "enter");
}
