/*
 * A11.c
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
    set_area("southern");
    set_areadesc("field");
    set_areaname("Erech");
    set_extraline("This is the most southern part of the vale of " +
	"Erech, the vale is wide and open here. A bit to the west the " +
        "sound of running water can be heard.");

    vale_items();
    path_items();

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "B10.c", "northeast", 0, 2, 0);
    add_exit(TO_AMROTH, "southwest", 0, 2, 0);

    reset_room();
}

void
reset_room()
{
    object o;

    o=clone_unique(E_NPC + "farmer");
    o->move(this_object());
    o=clone_unique(E_NPC + "farmer");
    o->move(this_object());
}
