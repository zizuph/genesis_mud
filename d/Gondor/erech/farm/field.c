/*
 * field.c
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
    set_areatype(AREATYPE_FARMLAND); /* Areatype, check ~Gondor/defs.h
				      * for specifications */
    set_area("central");             /* southern, central or northern */
    set_areadesc("field");           /* jupp */
    set_grass("long");               /* grass description */
    set_areaname("Erech");           /* name of the area */
    set_extraline("Between the furrows you can see rows of vegetables of " +
	"all different types. Small hills rise up around the field in " +
        "all directions, while some mountains tower to the north.");
                                     /* set extra longdesc */
  
    vale_items();
    add_item("snow", "Snow covers the tops of the mountains to the " +
        "north.\n");
    add_item("vegetables", "The farmers have a variety of vegetables " +
        "planted in the field.\n");
    add_item(({"ground", "dirt", "soil"}), "The soil in these parts is " +
        "rich and fertile.\n");
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FARM + "yard.c", "east", 0, 4, 0);
}


