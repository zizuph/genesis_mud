/*
 * E7.c
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
    set_extraline("Some white mountain tops are seen over the landscape. " +
        "The field is dark green, and some bushes are scatered over the " +
	"field. A bit to the north the sound of running water can be " +
	"heard. There is a thicket of bushes to the west.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FIELD + "E6.c", "north", &blocked_river(), 3, 1);
    add_exit(E_VALE + "E8.c", "south", &blocked_path(), 3, 1);
    add_exit(E_FIELD + "D7.c", "west", &on_field(), 3, 1);
    add_exit(E_FIELD + "D8.c", "southwest", &on_field(), 3, 1);
    add_exit(E_FIELD + "F6.c", "northeast", &on_field(), 3, 1);
    add_exit(E_VALE + "F7.c", "east", &on_field(), 3, 1);
}






