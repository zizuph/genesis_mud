/*
 * B9.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

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
    set_areatype(AREATYPE_MARSH);  /* Areatype, check ~Gondor/defs.h
				    * for specifications */
    set_area("southern");          /* southern, central or northern */
    set_areadesc("mire");          /* jupp */
    set_grass("long");             /* grass description */
    set_areaname("Erech");         /* name of the area */
    set_water("dark muddy");
    set_treetype("willow");
    set_extraline("It is a bit misty, and some trees can be seen here. " +
        "Through the mist a river can be seen north and west of here. It " +
        "is thoroughly wet, and everywhere sounds of dripping and water " +
        "can be heard.");
                                   /* set extra longdesc */

    vale_items();
    add_item("river", "The river runs smoothly down here.\n");
    add_item("mist", "Some mist lies low over the muddy water.\n");
    add_item( ({"tree","trees"}), "Some willow trees still poke their " +
        "heads above the dark muddy water.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("swamp");

    add_exit(E_VALE + "B8.c", "north", &blocked_river(), 3, 1);
    add_exit(E_VALE + "A9.c", "west", &blocked_river(), 3, 1);
    add_exit(E_VALE + "B10.c", "south", &to_road(), 2, 1);
    add_exit(E_VALE + "C9.c", "east", &to_road(), 2, 1);
}






