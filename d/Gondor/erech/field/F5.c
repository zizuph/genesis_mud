/*
 * F5.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "vale.c";

#include <cmdparse.h>
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
    set_extraline("To the north the White Mountains dominates the " +
	"view, while to the west a strange hill is seen at the end of " +
        "ridge. The sound of running water is heard from all directions, " +
        "making it dificoult to hear other sounds. The field is dark " +
        "green, some bushes and small trees are scatered over the field.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FIELD + "F4.c", "north", &on_field(), 3, 1);
    add_exit(E_FIELD + "E6.c", "southwest", &river_pass(), 4, 1);
    add_exit(E_FIELD + "G5.c", "east", &river_pass(), 4, 1);
    add_exit(E_FIELD + "F6.c", "south", &blocked_river(), 3, 1);
    add_exit(E_FIELD + "E5.c", "west", &blocked_river(), 3, 1);
}

