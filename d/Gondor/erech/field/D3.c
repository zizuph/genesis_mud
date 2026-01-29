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
    set_extraline("To the north the White Mountains tower up, and " +
        "at their foot winds a road. The field is dark green, " +
        "with a few bushes and small trees scattered across it. " +
        "To the west a ridge with a strange hill at its end rises. " +
	    "The ridge seems a little less steep here.");
                                   /* set extra longdesc */
  
    vale_items();
    field_items();
    hill_items();
    white_mountains();

    add_item(({"ridge"}), "A steep ridge rises above the field and up "
	     + "towards a plateou futher up. Rocks and small cracks are "
	     + "visible all over the ridge here.\n");
    add_item(({"plateau"}), "The ridge seems to give way to a plateau "
         + "higher up.\n");
    add_item(({"rock", "rocks", "crack", "cracks", "small crack",
         "small cracks"}), "Rocks and small cracks mar the ridge here, "
         + "probably allowing adequate grip for climbing.\n");
    add_item(({"road"}), "A road winds its way along the base of the "
         + "mountains in the distance.\n");
    
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
        case "the ridge":
        case "up the ridge":
        case "up ridge":
        case "up":
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
    write("You climb up the ridge.\n");
    say(QCTNAME(this_player()) + " leaves climbing " +
	"up the ridge.\n");
    this_player()->move_living("M", E_VALE + "C3", 1, 0);
    say(QCTNAME(this_player()) + " arrives climbing.\n");
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


