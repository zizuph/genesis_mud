/*
 * Coded by Ckrik, June 1998 
 * A Karg camp landing.
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
    add_long("The camp extends to the east and south.\n");
    add_exit("karg_camp05", "east");
    add_exit("karg_camp09", "south");
    reset_room();
}

public void
reset_room()
{
    add_prop(ROOM_S_MAP_FILE, "tenalders_map.txt");
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
        karg_3 = clone_object(KARG4);
        karg_3->move(to);
        karg_3->command("emote strides in.");
        karg_4 = clone_object(KARG5);
        karg_4->move(to);
        karg_4->command("emote strides in.");
    }
}
