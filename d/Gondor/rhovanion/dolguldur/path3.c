/*
 * Road to Dol Guldur - /d/Gondor/rhovanion/dolguldur/path3.c
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
    set_herbs_2();
    
    set_short("Road to Dol Guldur");
    set_long("It is " + VBFC("day_desc") + " in Rhovanion, as you follow " +
        "the remains of an ancient road which cuts through Mirkwood " +
        "forest. Long brown grass and thick shrubs huddle at the feet " +
        "of the towering black trees which line the road, while " +
        "sinister shadows lurk beyond. The " + VBFC("daylight_desc") +
        " illuminates the ruins of Dol Guldur which rises before you " +
        "immediately to the northeast. The path also trails off to the " +
        "southwest where it meets up with the Anduin river.\n");

    add_item( ({"city", "dol guldur", "ruins"}),
        "The entrance to Dol Guldur rises up before you, a bustle of " +
        "activity beyond the open city gates shows that it is " +
        "currently inhabited.\n");
    add_item( ({"gate", "gates", "city gate", "city gates"}),
        "The thick wooden gates of Dol Guldur are currently open, " +
        "granting access into the city beyond.\n");
    add_item( ({"bushes", "bush", "shrub", "shrubs", "shrubbery"}),
        "Several bushes huddle up beneath the black trees of Mirkwood " +
        "forest, rustling in the wind, watching you in malicious silence " +
        "as you follow the road to Dol Guldur. You also happen to see " +
        "what appears to be a hidden path winding off to the northwest!\n");

    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");
    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");
    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");
    add_tell("You can hear harsh, gutteral shouts echoing out through " +
        "the city gates.\n");

    set_no_exit_msg( ({"north", "east", "southeast", "south", "west"}),
        "You take a tentative step towards the dark shadows beneath " +
        "the black trees of Mirkwood, but they seem to suddenly " +
        "crowd together in response to you, preventing you from " +
        "entering the forest.\n");

    add_exit(DG_DIR + "path4", "northwest", 0, 3, 1);
    add_exit(DG_DIR + "entrance", "northeast", 0, 3, 0);
    add_exit(DG_DIR + "path2", "southwest", 0, 3, 0);
}