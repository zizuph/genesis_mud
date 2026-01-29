/*
 *  /d/Sparkle/area/tutorial/farm/garlic_patch2.c
 *
 *  A vegetable patch in Farmer Brown's Farm north of Greenhollow
 *  in the Genesis Tutorial.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit FARM_DIR + "crop_room";

/* Definitions */
#define            CROP_TYPE        "garlic"  /* what's planted here? */
#define            LOCATION         "nw"      /* where in the field?  */
#define            BUNNY_NUM        5         /* how many bunnies?    */

/* Prototypes */
public void        create_crop_room();
public void        init();
public void        reset_room();


/*
 * Function name:        create_crop_room
 * Description  :        set up the room with farm presets
 */
public void
create_crop_room()
{
    plant_crop(CROP_TYPE);
    set_field_location(LOCATION);
    add_field_items();

    add_rabbit_hole();

    add_exit("garlic_patch1a", "southwest");
    add_exit("garlic_patch2a", "northeast");
    add_exit("garlic_patch2", "down", &enter_hole("down"), 0, 1);

    reset_room();
} /* create_crop_room */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(throw_stuff, "throw");
    add_action(throw_stuff, "drop");
    add_action(throw_stuff, "toss");
    add_action(throw_stuff, "put");
    add_action(enter_hole, "climb");
    add_action(enter_hole, "enter");
    add_action(enter_hole, "go");
} /* init */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and objects as needed
 */
public void
reset_room()
{
    clone_bunny(BUNNY_NUM, "jack");
} /* reset_room */

