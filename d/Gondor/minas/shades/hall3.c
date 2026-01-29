#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Shade1, Shade2;

public void
create_gondor()
{
    set_short("hallway in the Shades hideout");
    set_long(BSN("This hallway leads back south to the entrance of the " +
               "hideout. To the north seems to be a sleep chamber of " +
               "some sorts. The walls here are sturdy and made of stone. " +
               "To then northeast there is another exit. That room is " +
               "dark, very dark. An oil-lamp hangs giving the little " + 
               "light that is here."));
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    add_item(({"oil-lamp","oil lamp","lamp"}),
        "An oil-lamp hangs from the ceiling by a rusty chain, providing the little light that is in here.\n");
    add_item("walls","The walls are made of grey-white stone.\n");
    add_exit(SHADES_DIR + "sleep1", "north",0,1);
    add_exit(SHADES_DIR + "hall1","south", 0, 1);
    add_exit(SHADES_DIR + "loot1", "northeast",0, 1);
    reset_room();
}

public void
reset_room()
{
    Shade1 = clone_npc(Shade1, SHADES_DIR + "shade");
    Shade2 = clone_npc(Shade2, SHADES_DIR + "shade2");
    Shade2->team_join(Shade1);
}

