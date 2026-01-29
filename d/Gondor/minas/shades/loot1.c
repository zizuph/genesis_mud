/*
 *      /d/Gondor/minas/shades/loot1.c
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

static object  Talin;

public void
create_gondor() 
{
    set_short("a small chamber");
    set_long(BSN("This is a small room used by a high ranking " +
        "member of the Shades. There is a desk here with a single " +
        "chair. An oil-lamp hangs from the ceiling giving light to " +
        "the room. Like the rest of the hideout the walls are made " +
        "of a grey-white stone."));
    
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"oil-lamp","lamp","oil lamp"}),BSN("The oil-lamp hangs " +
        "by a chain from the ceiling, giving light to the room."));
    add_item(({"wall","walls"}),BSN("The walls are made of a grey-white " +
        "stone, they seem very solid."));
    add_item("desk","The desk is made of dark stained oak, no drawers at all.\n");
    add_item("chair","The chair is made of a dark stained oak, nothing special about it.\n");
    add_item("chain","The chain is made of steel and looks sturdy.\n");
    add_item("ceiling","The ceiling is made of a grey-white stone, a chain hangs from it.\n");

    add_exit(SHADES_DIR + "hall3", "southwest", 0, 1);

    reset_room();
}

public void
reset_room() 
{
    Talin = clone_npc(Talin, SHADES_DIR + "talin");
}
