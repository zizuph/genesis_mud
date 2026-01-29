/*
 *  /d/Sparkle/area/tutorial/woods/forest_1c.c
 *
 *  A part of the Sterling Woods in Silverdell.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit WOODS_DIR + "forest_room";

/* Definitions */
#define     TREE_TYPE         "oak"    /* what's growing here? */
#define     LOCATION          "w"      /* where in the woods?  */
#define     TUTORIAL_CHAPTER   38      /* the chapter for the sign */

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

    add_exit("forest_2b", "northeast");
    add_exit("forest_2c", "east");
    add_exit("forest_2d", "southeast");
    add_exit("river", "west");

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
