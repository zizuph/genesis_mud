/*
 * H5.c
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
    set_extraline("To the north the White Mountains dominated the view, " +
        "while to the west a strange hill is seen. The field is dark " +
        "green, some bushes and small trees are scatered over the field. " +
        "The sound of running water can be heard to the north and to the " +
        "west.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FIELD + "G6.c", "southwest", &on_field(), 3, 1);
    add_exit(E_FIELD + "G5.c", "west", &river_pass(), 4, 1);
    add_exit(E_VALE + "H6.c", "south", &blocked_path(), 3, 1);
    add_exit(E_VALE + "I5.c", "east", &blocked_path(), 3, 1);
    add_exit(E_VALE + "H4.c", "north", &blocked_path(), 3, 1);
}
