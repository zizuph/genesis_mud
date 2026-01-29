/*
 * Elven camp near Dol Guldur - /d/Gondor/rhovanion/dolguldur/path6.c
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
    set_long("The " + VBFC("light_type") + " from the " + VBFC("day_desc") + 
        " " + VBFC("sun_moon") + " shines brightly into the middle of a " +
        "clearing inside Mirkwood forest. The path you have been following " +
        "runs out from the clearing to both the northwest and southwest, " +
        "darting back into the shadowy depths of Mirkwood. The walls of " +
        "Dol Guldur are barely visible at times through the black trees " +
        "to the east. In the middle of the clearing, it appears that " +
        "someone has set up a small camp.\n");

    add_item( ({"clearing", "camp", "small camp"}),
        "A small camp has been set up in the middle of this clearing, " +
        "bearing a distinctly elvish air. Three small tents cluster " +
        "together around large flat rock.\n");
    add_item( ({"tent", "small tent", "tents", "small tents"}),
        "There are three small tents here, but they are currently empty.\n");
    add_item( ({"rock", "large rock", "flat rock", "large flat rock"}),
        "It appears as if this large rock was recently moved here, the " +
        "surface is unusually flat allowing it to be used almost like a " +
        "makeshift table.\n");

    add_tell("A tingling shiver runs down your back as you feel unseen " +
        "eyes peering out from the shadows of Mirkwood forest, watching " +
        "you.\n");

    add_npc(DG_DIR + "npc/silmelen");
    add_npc(DG_DIR + "npc/scout", 3);

    set_no_exit_msg( ({"north", "northeast", "east", "south", "southwest",
            "west"}),
        "You attempt to leave the path and enter Mirkwood forest, but " +
        "the underbrush is too thick. You stumble and end up falling " +
        "back onto the hard dirt of the path.\n");

    add_exit(DG_DIR + "path5", "southeast", 0, 3, 0);
    add_exit(DG_DIR + "mirk1", "northwest", "@@path@@", 3, 1);
    
    add_exit(DG_DIR + "mirk2", "west", "@@path@@", 3, 1);
    add_exit(DG_DIR + "mirk3", "north", "@@path@@", 3, 1);
    add_exit(DG_DIR + "mirk7", "southwest", "@@path@@", 3, 1);
}

/* A message decribing the correct path */
int
path()
{
    write("You manage to follow the trail deeper into Mirkwood.\n");
    return 0;
}