/*
 * D7.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "vale.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();
       int          bush_block();

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
    set_extraline("Some white mountain tops can be seen over the landscape. " +
        "The sound of water can be heard from the north and west. " +
        "The field is dark green, and some bushes and small trees are " +
	"scattered over the field. There is a thicket of bushes to the east.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_VALE + "C7.c", "west", &blocked_river(), 3, 1);
    add_exit(E_FIELD + "D8.c", "south", &on_field(), 3, 1);
    add_exit(E_FIELD + "E7.c", "east", &bush_block(), 3, 1);
    add_exit(E_VALE + "D6.c", "north", &blocked_river(), 3, 1);
}

/*
 * Function name:    bush_block()
 * Description  :    Writes out the block message, and blocks the path.
 * Returns      :    1 to block the path.
 */
int
bush_block()
{
    write("The bushes are too close together to pass.\n");
    return 1;
}





