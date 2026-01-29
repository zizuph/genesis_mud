/*
 * E6.c
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
    set_extraline("To the north a strange hill is seen infront of the " +
        "panorama view of the White Mountains. The field is dark green, " +
        "some bushes and trees are scatered over the field. The sound of " +
        "running water can be heard to the south and to the east.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FIELD + "D5.c", "northwest", &on_field(), 3, 1);
    add_exit(E_FIELD + "F5.c", "northeast", &river_pass(), 4, 1);
    add_exit(E_FIELD + "E5.c", "north", &blocked(), 3, 1);
    add_exit(E_VALE + "D6.c", "west", &to_road(), 2, 1);
    add_exit(E_FIELD + "E7.c", "south", &blocked_river(), 3, 1);
    add_exit(E_FIELD + "F6.c", "east", &blocked_river(), 3, 1);
}

/*
 * Function name:    blocked()
 * Description  :    Blocks the path with the right message.
 * Returns      :    1 = Blocked
 */
int
blocked()
{
    write("You strive your way through the bushes, but have to give up.\n");
    return 1;
}


