/*
 *  /d/Sparkle/area/tutorial/farm/radish_patch1.c
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
#define            CROP_TYPE        "radish" /* what's planted here? */
#define            LOCATION         "s"      /* where in the field?  */
#define            BUNNY_NUM        0        /* how many bunnies?    */
#define     TUTORIAL_CHAPTER        36       /* chapter for the sign */

/* Prototypes */
public void        create_crop_room();
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

    add_exit("radish_patch1a", "northeast");
    add_exit("barnyard", "south");
    add_exit("potato_patch1", "west", check_exit, 1, 0);

    reset_room();
} /* create_crop_room */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

    clone_bunny(BUNNY_NUM, "baby");
} /* reset_room */
