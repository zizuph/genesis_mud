/*
 * Dol Guldur - /d/Gondor/rhovanion/dolguldur/main3.c
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
    set_long("You are on a wide road, where the " + VBFC("day_desc") + " " +
        VBFC("sun_moon") + " peeks through the dark clouds above to " +
        "shine down upon the ruined city of Dol Guldur. Debris from the " +
        "collapsed buildings have been moved clear of the main road, " +
        "making it difficult to go anywhere but northeast to the large " +
        "tower which looms nearby, or the city gates which are somewhere " +
        "at the end of the road southwest of here. Unlike the southwest " +
        "corner of town, this part of Dol Guldur has not been restored " +
        "yet.\n");

    add_item( ({"gate", "city gate", "gates", "city gates"}),
        "The gates of Dol Guldur are at the end of this road to the " +
        "southwest.\n");
    add_item( ({"main road", "wide road", "road"}),
        "This appears to be the main road of Dol Guldur, running in a " +
        "straight line from the ruined tower to the city gates.\n");
    add_item( ({"tower", "broken tower", "ruined tower"}),
        "Just up ahead to the northeast, you see this ruined tower " +
        "rising high above the rest of the city.\n");

    set_no_exit_msg( ({"north", "east", "southeast", "northwest"}),
        "Some of the rubble and ruins of Dol Guldur prevent you from " +
        "going in that direction! You are going to have to find another " +
        "way around.\n");

    add_exit(DG_DIR + "tower", "northeast", 0, 3, 0);
    add_exit(DG_DIR + "ruins1", "east", "@@climb@@", 5, 1);
    add_exit(DG_DIR + "main2", "southwest", 0, 3, 0);
    add_exit(DG_DIR + "ruins4", "west", "@@climb@@", 5, 1);
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