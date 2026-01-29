#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h> 
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Shade1, Shade2, Shade3;

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
               "only one exit, and that is to the south."));
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    add_item("oil-lamp","An oil-lamp hangs from the ceiling on a rusty black chain.\n");
    add_item("walls","The walls are made of grey-white stone.\n");
    add_item("table",BSN("The table stands in the middle of the room. Looking " +
           "closer you can see that more then a few thieves have thought " + 
           "they were masters in wood carving rather than thievery."));
    add_item("chairs","Four chairs stand around the table, well used as the stain on them has begun to fade.\n");
    add_item(({"bed","beds"}),"The beds are plain cots, with simple blankets on them.\n");
    add_item(({"carvings","carving"}),BSN(
            "Looking at the carvings you can see most of them are nothing " +
            "but mindless scribbling. 'Shades Rule' can be found in numerous " +
            "spots on the table, and as you look you find one on a chair."));
    add_exit(SHADES_DIR + "hall3", "south", 0, 1);
    reset_room();
}

public void
reset_room()
{
    Shade1 = clone_npc(Shade1, SHADES_DIR + "shade");
    Shade2 = clone_npc(Shade2, SHADES_DIR + "shade2");
    Shade2->team_join(Shade1);
    Shade3 = clone_npc(Shade3, SHADES_DIR + "shade");
    Shade3->team_join(Shade1);
}

