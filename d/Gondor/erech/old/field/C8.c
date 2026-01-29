/*
 * C8.c
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
    set_areatype(AREATYPE_MARSH); /* Areatype, check ~Gondor/defs.h
				    * for specifications */
    set_area("southern");          /* southern, central or northern */
    set_areadesc("mire");         /* jupp */
    set_grass("long");             /* grass description */
    set_areaname("Erech");         /* name of the area */
    set_water("dark muddy");
    set_treetype("willow");
    set_extraline("It is a bit misty, and some trees can be seen here. " +
        "It is thorugly wet, and everywhere sounds of dripping and water " +
        "is heard. Through the mist a river can be seen east and " +
	"south of here.");
                                   /* set extra longdesc */
 
    vale_items();
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("swamp");

    add_exit(E_VALE + "C9.c", "south", &blocked_river(), 3, 1);
    add_exit(E_FIELD + "D8.c", "east", &blocked_river(), 3, 1);
    add_exit(E_VALE + "B8.c", "west", &to_road(), 2, 1);
    add_exit(E_VALE + "C7.c", "north", &to_road(), 2, 1);
}






