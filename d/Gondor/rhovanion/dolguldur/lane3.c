/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/lane3.c
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
    set_long("You have effectively reached the end of this small lane, " +
        "as the broken piles of debris visible in the " 
        + VBFC("daylight_desc") + " appear to block any further passage " +
        "into the city. On the south side of the lane, the walls of " +
        "Dol Guldur have been fully restored as they stretch from " +
        "the city gates to circle around the entire city. The jagged " +
        "peak of the broken tower that rises up in the middle of the city " +
        "stands out in the " + VBFC("daylight_desc") + ", with massive " +
        "piles of broken rubble laying at its feet. The only exit appears " +
        "to be back west towards the city gates.\n");

    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are somewhere at the end of this road " +
        "to the west.\n");
    add_item( ({"street", "wall street"}),
        "This lane follows the wall east of the gates in the restored " +
        "parts of Dol Guldur.\n");
    add_item( ({"wall", "city wall", "walls", "city walls"}),
        "The city walls of Dol Guldur rise up immediately before you as " +
        "this lane travels along them.\n");

    set_no_exit_msg( ({"northwest", "north", "east"}),
        "Some of the rubble and ruins of Dol Guldur prevent you from " +
        "going in that direction! You are going to have to find another " +
        "way around.\n");
    set_no_exit_msg( ({"southwest", "south", "southeast"}),
        "Yup, the city wall is definately restored! You will have to " +
        "go through the city gate if you want to get to the other side " +
        "of the wall.\n");

    add_exit(DG_DIR + "ruins3", "northeast", "@@climb@@", 5, 1);
    add_exit(DG_DIR + "lane2", "west", 0, 3, 0);
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