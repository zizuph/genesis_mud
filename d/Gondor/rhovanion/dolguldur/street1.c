/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/street1.c
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
    set_long("The " + VBFC("light_type") + " from the " + VBFC("day_desc") +
        " " + VBFC("sun_moon") + " drifts down upon this narrow street " +
        "as it follows the wall along the perimeter of Dol Guldur. A " +
        "large building dominates your view to the east, almost completely " +
        "obscuring the tall broken tower in the middle of the city. A " + 
        "long, low shack sprawls along the north side of the road, a " +
        "popular tavern by the sounds of it. The city wall covers the " +
        "other side of the road, with the city gates just a short " +
        "distance away to the southeast.\n");

    add_item( ({"building", "large building"}),
        "There is a large building east of here. It appears to be quite " +
        "solidly built and well maintained. You cannot see any way to " +
        "enter it from here however.\n");
    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are nearby, at the end of this road " +
        "to the southeast.\n");
    add_item( ({"street", "wall street"}),
        "This street follows the wall west of the gates in the restored " +
        "parts of Dol Guldur.\n");
    add_item( ({"wall", "city wall", "walls", "city walls"}),
        "The city walls of Dol Guldur rise up immediately before you as " +
        "this street follows them around the perimeter of the city.\n");
    add_item( ({"tavern", "loud tavern", "low shack", "long shack",
            "shack", "long low shack"}),
        "Just north of the road here you see a long, low shack sprawling " +
        "across this part of Dol Guldur. Judging by ear, it sounds like " +
        "it is probably a tavern. A loud tavern.\n");

    add_tell("Loud shouts and racuous laughter ripple out from the " +
        "nearby tavern.\n");
    add_tell("The sound of tables breaking and mugs shattering " +
        "echoes out from the low shack just north of here.\n");

    set_no_exit_msg( ({"northeast", "east"}),
        "Try as you might, you cannot find an entrance into the large " +
        "building from here!\n");
    set_no_exit_msg( ({"west", "southwest", "south"}),
        "Yup, the city wall is definately restored! You will have to " +
        "go through the city gate if you want to get to the other side " +
        "of the wall.\n");
    set_no_exit_msg( ({"north"}),
        "There does not appear to be a way into the tavern from this " +
        "direction, you might have to go a bit farther up the road " +
        "to the main entrance.\n");

    add_exit(DG_DIR + "street2", "northwest", 0, 3, 0);
    add_exit(DG_DIR + "entrance", "southeast", 0, 3, 0);
}