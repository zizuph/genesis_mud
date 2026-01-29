/*
 * coded by Amelia 7/26/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include <stdproperties.h>
#include "defs.h"

private object bonesman, *kargs = allocate(3);

public void
reset_room()
{
    int i = 3;

    while(--i >= 0)
    {
        if(!objectp(kargs[i]))
        {
            kargs[i] = clone_object(KARGS[random(sizeof(KARGS))]);
            kargs[i]->move(this_object());
            kargs[i]->command("emote charges in, screaming in Kargish!");
        }
    }

    if(!objectp(bonesman))
    {
        bonesman = clone_object(
            "/d/Earthsea/gont/tenalders/npc/karg_bonesman"
        );
        bonesman->move(this_object());
        bonesman->command("emote strolls in beating a drum.");
    }
}

public void
create_earthsea_room()
{
    set_short("Tunnel hallway.");
    set_long("The network of underground caves seems to become " +
        "a tower, that goes downward into the depths of the earth. " +
        "The pressure of tons of rock weighs down above and around " +
        "you.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_NCAVETUNNEL);
    add_tell("Moisture drips down the walls.\n");
    add_tell("The drums beat loudly making your head hurt!\n");
    add_exit("tower_3", "southeast");
    add_exit("cave_center", "south");
    reset_room();
    set_tell_time(120);
}
