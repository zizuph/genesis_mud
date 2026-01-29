/*
 * Hidden path near Dol Guldur - /d/Gondor/rhovanion/dolguldur/path5.c
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
    set_herbs_2();
    
    set_short("Hidden path outside Dol Guldur");
    set_long("The " + VBFC("daylight_desc") + " filters through the "+
        "thick black trees of Mirkwood forest, barely giving you " +
        "enough light to see by. A hidden path cuts through the " +
        "forest here, curling around trees in a chaotic fashion, " +
        "but generally running from northwest to southeast. Glimpses " +
        "of Dol Guldur are momentarily visible to the east as you " +
        "follow the trail.\n");

    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");

    set_no_exit_msg( ({"north", "northeast", "east", "south", "southwest",
            "west"}),
        "You attempt to leave the path and enter Mirkwood forest, but " +
        "the underbrush is too thick. You stumble and end up falling " +
        "back onto the hard dirt of the path.\n");

    add_exit(DG_DIR + "path6", "northwest", 0, 3, 0);
    add_exit(DG_DIR + "path4", "southeast", 0, 3, 0);
}