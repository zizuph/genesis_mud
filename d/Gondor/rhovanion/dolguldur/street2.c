/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/street2.c
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
    
    set_short("Dol Guldur");
    set_long("You are on a narrow street that runs along the western " +
        "wall of Dol Guldur. An open doorway in a long, low shack to " +
        "the east opens up into a loud tavern. The tavern is clearly " +
        "the busiest place you have seen in Dol Guldur, with what " +
        "appears to be a mixture of humans and orcs drinking themselves " +
        "into violent, drunken stupors. The street follows the wall " +
        "north and towards the city gates to the southeast.\n");

    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are somewhere at the end of this road " +
        "to the southeast.\n");
    add_item( ({"street", "wall street"}),
        "This street follows the wall west of the gates in the restored " +
        "parts of Dol Guldur.\n");
    add_item( ({"wall", "city wall", "walls", "city walls"}),
        "The city walls of Dol Guldur rise up immediately before you as " +
        "this street follows them around the perimeter of the city.\n");
    add_item( ({"tavern", "loud tavern", "low shack", "long shack",
            "shack", "long low shack"}),
        "There is an open entrance into a very loud, and very busy, " +
        "tavern just east of here.\n");

    add_tell("Loud shouts and racuous laughter ripple out from the " +
        "nearby tavern.\n");
    add_tell("The sound of tables breaking and mugs shattering " +
        "echoes out from the tavern.\n");

    set_no_exit_msg( ({"northeast"}),
        "Some of the rubble and ruins of Dol Guldur prevent you from " +
        "going in that direction! You are going to have to find another " +
        "way around.\n");
    set_no_exit_msg( ({"northwest", "west", "southwest", "south"}),
        "Yup, the city wall is definately restored! You will have to " +
        "go through the city gate if you want to get to the other side " +
        "of the wall.\n");

    add_exit(DG_DIR + "street3", "north", 0, 3, 0);
    add_exit(DG_DIR + "tavern", "east", 0, 0, 0);
    add_exit(DG_DIR + "street1", "southeast", 0, 3, 0);
}