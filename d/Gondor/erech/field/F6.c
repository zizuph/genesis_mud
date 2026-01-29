/*
 * F6.c
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
    set_areatype(AREATYPE_BUSHES); /* Areatype, check ~Gondor/defs.h
				    * for specifications */
    set_area("central");          /* southern, central or northern */
    set_areadesc("field");         /* jupp */
    set_grass("long");             /* grass description */
    set_areaname("Erech");         /* name of the area */
    set_extraline("To the north the White Mountains dominate the view, " +
        "while a strange hill can be seen to the northwest. The sound " +
        "of running water can be heard from the north and west. The field " +
        "dark green, and some bushes and trees are scattered across it.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FIELD + "E7.c", "southwest", &on_field(), 3, 1);
    add_exit(E_FIELD + "G6.c", "east", &on_field(), 3, 1);
    add_exit(E_FIELD + "F5.c", "north", &blocked_river(), 3, 1);
    add_exit(E_VALE + "F7.c", "south", &blocked_path(), 3, 1);
}






