/*
 * Road to Dol Guldur - /d/Gondor/rhovanion/dolguldur/path2.c
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
    set_long("You are on an ancient road which appears to lead towards " +
        "the ruins of Dol Guldur which are visible beneath the " +
        VBFC("light_type") + " on the northeastern horizon. Mirkwood " +
        "forest surrounds you, its shadowy depths hiding behind " +
        "the tall black trees which line the road as they tower above you. " +
        "Far away to the southwest, the road will take you back to the " +
        "Anduin river.\n");

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

    add_exit(DG_DIR + "path3", "northeast", 0, 3, 0);
    add_exit(DG_DIR + "path1", "southwest", 0, 3, 0);
}