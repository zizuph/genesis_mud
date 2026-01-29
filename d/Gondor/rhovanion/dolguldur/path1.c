/*
 * Road to Dol Guldur - /d/Gondor/rhovanion/dolguldur/path1.c
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

    set_items_road();
    set_herbs_1();
    
    set_short("Road to Dol Guldur");
    set_long("The " + VBFC("light_type") + " from the " + VBFC("day_desc") + 
        " " + VBFC("sun_moon") + " falls down around you as you wander " +
        "down this ancient road. The black trees of Mirkwood forest " +
        "tower above the thick bushes and tall brown grass which line " +
        "the edge of the trail. Off in the distance to the northeast, " +
        "you can see the broken ruins of Dol Guldur jaggedly cutting into " +
        "the horizon. The path also winds off to the southwest towards the " +
        "distant Anduin river.\n");
    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");
    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");
    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");

    set_no_exit_msg( ({"north", "east", "southeast", "south", "west",
            "northwest"}),
        "You take a tentative step towards the dark shadows beneath " +
        "the black trees of Mirkwood, but they seem to suddenly " +
        "crowd together in response to you, preventing you from " +
        "entering the forest.\n");

    add_exit(DG_DIR + "path2", "northeast", 0, 3, 0);
    add_exit("/d/Shire/anduin/west/wbs5", "southwest", 0, 3, 0);
}