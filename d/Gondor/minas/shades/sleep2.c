/*
 *      /d/Gondor/minas/shades/sleep2.c
 *
 *      Coded by Sithas
 *
 *      Modification log:
 *       3-mar-97, Olorin:      Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object *Shades = allocate(2),
               Shade;

public void
create_gondor() 
{
    set_short("sleep chamber in the Shades hideout");
    set_long(BSN("The room is lit by oil-lamps hanging from the ceiling. " +
        "Four beds line the walls, two on the east wall and two " +
        "on the west. The room is fairly clean, and does not seem " +
        "to hold any sort of personal items. Probably better that " +
        "way in case a speedy exit is required. A small table stands " +
        "in the middle of the room, a few chairs around it. There is " +
        "only one exit, and that is to the north."));

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    add_item("oil-lamp","An oil-lamp hangs from the ceiling on a rusty black chain.\n");
    add_item("walls","The walls are made of grey-white stone.\n");
    add_item("table",BSN("The table stands in the middle of the room. Looking " +
        "closer you can see many nicks and marks carved into the table.")); 
    add_item("chairs","Four chairs stand around the table, well used as the stain on them has begun to fade.\n");
    add_item(({"bed","beds"}),"Simple cots with nothing but thin blankets on them.\n");
    add_item(({"carvings","carving","marks","nicks",}),BSN(
        "Nothings special just the outcome of long boring hours of nothing " +
            "to do. 'Shades Rule' can be found carved numerous times into the " +
            "wood of the chairs and tables."));

    add_exit(SHADES_DIR + "hall2","north",0,1);

    reset_room();
}

public void
reset_room()
{
    clone_npcs(Shades, SHADES_DIR + "shade", -1.0);
    Shade = clone_npc(Shade, SHADES_DIR + "shade2");

    Shades[0]->team_join(Shades[1]);
    Shades[0]->team_join(Shade);
}
