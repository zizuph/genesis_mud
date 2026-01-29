/*
 *  /d/Sparkle/area/tutorial/farm/garlic_patch3.c
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
#define            LOCATION         "n"       /* where in the field?  */
#define            BUNNY_NUM        4         /* how many bunnies?    */

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
    set_extraline("A dirt track runs northwest toward what appears to"
      + " be a henhouse.");

    plant_crop(CROP_TYPE);
    set_field_location(LOCATION);
    add_field_items();

    add_item( ({ "track", "dirt track" }),
        "The dirt track passes out of the field, heading northwest.\n");
    add_item( ({ "henhouse", "house", "hen house", "northwest" }),
        "The henhouse looks somewhat derelict.\n");

    add_exit("turnip_patch3", "south");
    add_exit("garlic_patch2a", "southwest", check_exit, 1, 0);
    add_exit("henhouse", "northwest");

    reset_room();
} /* create_crop_room */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and objects as needed
 */
public void
reset_room()
{
    clone_bunny(BUNNY_NUM, "jack");
} /* reset_room */

