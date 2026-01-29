/*
 * Hidden path near Dol Guldur - /d/Gondor/rhovanion/dolguldur/path4.c
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

    set_items_path();
    set_herbs_1();
    
    set_short("Hidden path outside Dol Guldur");
    set_long("It is " + VBFC("day_desc") + " inside Mirkwood forest as "+
        "you follow a hard dirt path as it skirts around the edge of " +
        "the city of Dol Guldur. Tall black trees surround you in " +
        "every direction, as the hidden path twists and weaves its " +
        "way through the forest. You can follow the path to either " +
        "the northwest or southeast here.\n");

    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");

    set_no_exit_msg( ({"north", "northeast", "east", "south", "southwest",
            "west"}),
        "You attempt to leave the path and enter Mirkwood forest, but " +
        "the underbrush is too thick. You stumble and end up falling " +
        "back onto the hard dirt of the path.\n");

    add_exit(DG_DIR + "path5", "northwest", 0, 3, 0);
    add_exit(DG_DIR + "path3", "southeast", 0, 3, 0);
}