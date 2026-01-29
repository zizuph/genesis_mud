/*
 * I4.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit "/d/Gondor/common/lib/area_room";
inherit "/lib/unique";

inherit E_STD + "vale.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();

/*
 * Function name:    create_area_room()
 * Definition   :    Creates the room.
 */
public void
create_area_room()
{
    set_short("In the vale of Erech.");
    set_areatype(AREATYPE_ROAD);
    set_areaname("Erech");
    set_area("northern");
    set_areadesc("valley side");
    set_extraline("To the north the White Mountains towers up. A bit to the " +
        "south the bouldering sound of water can be heard. The valley side " +
        "is very steep here, the road seems to be masoned into the mountain " +
        "side. A road leads west and south.");

  path_items();
  vale_items();

  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

  add_exit(E_VALE + "H4.c", "west", 0, 2, 0);
  add_exit(E_VALE + "I5.c", "south", 0, 2, 0);

  reset_room();
}

void
reset_room()
{
    object o;

    o=clone_unique(E_NPC + "farmer", 6);
    o->move(this_object());
}
