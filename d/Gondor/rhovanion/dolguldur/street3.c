/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/street3.c
 *
 * Varian - November 2020
 */

#pragma strict_types

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
 
inherit RHOVANION_DIR + "dolguldur/std/base";

/*
 * Function name:        create_dg_room()
 * Description  :        Creates the dg from from the base file
 *                       /d/Gondor/rhovanion/dolguldur/std/base.c
 */
void 
create_dg_room()
{

    set_items_city();
    set_items_ruins();
    
    set_short("Dol Guldur");
    set_long("The " + VBFC("light_type") + " from the " + VBFC("day_time") + 
        " " + VBFC("sun_moon") +  " peers out from behind the dark " +
        "clouds which blanket Dol Guldur, illuminating the narrow street " +
        "you are wandering along. The city wall follows the west side " +
        "of the street, while everything else nearby seems to be a " +
        "massive pile of rubble gathered at the foot of the broken tower " +
        "which stands in the middle of the city. The only clear path away" +
        "from here is to follow the street back south towards the city " +
        "gates.\n");

    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are somewhere at the end of this road " +
        "to the south.\n");
    add_item( ({"street", "wall street"}),
        "This street follows the wall west of the gates in the restored " +
        "parts of Dol Guldur.\n");
    add_item( ({"wall", "city wall", "walls", "city walls"}),
        "The city walls of Dol Guldur rise up immediately before you as " +
        "this street follows them around the perimeter of the city.\n");

    set_no_exit_msg( ({"northeast"}),
        "Some of the rubble and ruins of Dol Guldur prevent you from " +
        "going in that direction! You are going to have to find another " +
        "way around.\n");
    set_no_exit_msg( ({"northwest", "west", "southwest", "south"}),
        "Yup, the city wall is definately restored! You will have to " +
        "go through the city gate if you want to get to the other side " +
        "of the wall.\n");

    add_exit(DG_DIR + "ruins7", "east", "@@climb@@", 5, 1);
    add_exit(DG_DIR + "street2", "south", 0, 3, 0);
}

/* A message which indicates climbing through the rubble when using 
   the hidden exits. */
int
climb()
{
    write("With a great deal of effort, you climb over broken blocks " +
        "of stone and wooden beams as you leave the main road.\n");
    return 0;
}