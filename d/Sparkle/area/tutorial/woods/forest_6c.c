/*
 *  /d/Sparkle/area/tutorial/woods/forest_6c.c
 *
 *  A part of the Sterling Woods in Silverdell.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit WOODS_DIR + "forest_room";

/* Definitions */
#define     TREE_TYPE        "silverwood" /* what's growing here? */
#define     LOCATION         "e"          /* where in the woods?  */
#define     TUTORIAL_CHAPTER  45          /* the chapter for the sign */

/* Prototypes */
public void        create_forest_room();
public void        reset_room();


/*
 * Function name:        create_forest_room
 * Description  :        set up the room with forest presets
 */
public void
create_forest_room()
{
    plant_trees(TREE_TYPE);
    set_forest_location(LOCATION);
    add_woods_items();

    add_exit("forest_5d", "southwest");
    add_exit("forest_5c", "west");
    add_exit("forest_5b", "northwest");

    reset_room();
} /* create_forest_room */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    clone_animal();
    reset_herbs();

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */

