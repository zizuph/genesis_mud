/*
 * G6.c
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
    set_areatype(AREATYPE_FARMLAND); /* Areatype, check ~Gondor/defs.h
				      * for specifications */
    set_area("central");             /* southern, central or northern */
    set_areadesc("field");           /* jupp */
    set_grass("long");               /* grass description */
    set_areaname("Erech");           /* name of the area */
    set_extraline("To the north the White Mountains dominates the view, " +
        "while a strange hill can be seen to the northwest. The field is " +
        "dark green, and some bushes and small trees are scatered over the " +
        "field. Some buildings is visible to the northwest, behind a white " +
        "fence. A bit to the north the sound of running water can be heard.");
                                     /* set extra longdesc */
  
    vale_items();
    field_items();
    add_item( ({ "fence", "white fence" }), "This is a white fence, made to " +
        "keep the wild animals out, and the farm's herd on the inside. It " +
        "has a simple construction of two horisontal planks with vertical " +
        "planks nailed to it.\n");
    add_item( ({"building","buildings","farm","house","houses","barn"}), 
	"Behind the fence you see " +
        "large red barn and a smaller white house, with a tiled roof.\n");
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FIELD + "F6.c", "west", &on_field(), 3, 1);
    add_exit(E_FIELD + "H5.c", "northeast", &on_field(), 3, 1);
    add_exit(E_FIELD + "G5.c", "north", &river_pass(), 4, 1);
    add_exit(E_VALE + "G7.c", "south", &to_road(), 2, 1);
    add_exit(E_VALE + "H6.c", "east", &to_road(), 2, 1);
    clone_object(E_OBJ + "fgate1.c")->move(this_object());
}

