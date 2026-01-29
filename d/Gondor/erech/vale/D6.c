/*
 * D6.c
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
    set_area("central");
    set_areadesc("valley side");
    set_areaname("Erech");
    set_extraline("This is a road following the western side of the " +
        "vale of Erech. A bit to the south the sound of running water " +
        "can be heard. To the north there is a strange hill.");

    path_items();
    vale_items();
    hill_items();
    remove_item("ridge");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_exit(E_VALE + "C5.c", "northwest", 0, 2, 0);
    add_exit(E_VALE + "C7.c", "southwest", 0, 2, 0);
    add_exit(E_FIELD + "E6.c", "east", &to_field(), 2, 1);

    reset_room();
}

void
reset_room()
{
    object o;

    o=clone_unique(E_NPC + "farmer", 6);
    o->move(this_object());
}
