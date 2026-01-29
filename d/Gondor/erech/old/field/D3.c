/*
 * D3.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "vale.c";

#include <macros.h>
#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void         create_area_room();
void                climbing_ridge();

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
    set_area("northern");          /* southern, central or northern */
    set_areadesc("field");         /* jupp */
    set_grass("long");             /* grass description */
    set_areaname("Erech");         /* name of the area */
    set_extraline("To the north the White Mountains towers up, and " +
        "at its foot a road can be seen. The field is dark green, " +
        "some bushes and small trees are scatered over the field. " +
        "To the west a ridge with a strange hill at its end raises. " +
	"The ridge is not so steep here as the rest, so it might be " +
        "climbable.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();

    add_item("ridge", "A steep ridge raises from the field and up " +
	     "towards a plateou futher up. It is rocks and small cracks " +
	     "all over the ridge, making it look like an easy target for " +
	     "climbing.\n");
    
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_VALE);

    add_herbs("field");

    add_exit(E_FIELD + "D2.c", "north", &on_field(), 3, 1);
    add_exit(E_FIELD + "E3.c", "east", &on_field(), 3, 1);
    add_exit(E_VALE + "D4.c", "south", &blocked_path(), 3, 1);
    add_exit(E_FIELD + "C3.c", "west", &blocked_path(), 3, 1);
    add_exit(E_FIELD + "E4.c", "southeast", &on_field(), 3, 1);
}

/*
 * Function name:    init()
 * Description  :    Adds extra commands to the room
 */
public void
init()
{
    ::init();
    add_action("do_climb", "climb");
}

public int
do_climb(string dir)
{
    if (dir)
    {
        switch(dir)
	{
	    case "ridge":
	        climbing_ridge();
		return 1;
		break;
	     default:
	         write("Climb what?\n");
		 return 1;
		 break;
	}
    }
}

void
climbing_ridge()
{
    write("You climbs up the ridge.");
    say(QCTNAME(this_player()) + " leaves climbing " +
	"up the ridge.");
    this_player()->move_living("M", E_VALE + "C3", 1, 0);
    say(QCTNAME(this_player()) + " arrives climbing.");
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


