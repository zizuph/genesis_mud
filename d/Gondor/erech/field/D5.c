/*
 * D5.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "vale.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();
       int          blocked();

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
    set_extraline("To the north, a ridge and a strange hill rise up in front "
        + "of the distant, towering White Mountains. A bit to the north the " +
        "sound of running water can be heard. The field is dark green, " +
        "with a few bushes and small trees scattered across it.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();
    white_mountains();

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FIELD + "C4.c", "northwest", &on_field(), 3, 1);
    add_exit(E_FIELD + "E5.c", "east", &on_field(), 3, 1);
    add_exit(E_VALE + "C5.c", "west", &blocked_path(), 3, 1);
    add_exit(E_VALE + "D6.c", "south", &blocked_path(), 3, 1);
    add_exit(E_VALE + "D4.c", "north", &blocked_river(), 3, 1);
    add_exit(E_FIELD + "E6.c", "southeast", &blocked(), 3, 1);
}

/*
 * Function name:    blocked()
 * Description  :    Blocks the path with the right message.
 * Returns      :    1 = Blocked
 */
int
blocked()
{
    write("You struggle to push through the bushes, but to no avail.\n");
    return 1;
}



