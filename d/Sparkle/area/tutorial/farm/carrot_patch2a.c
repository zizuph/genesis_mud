/*
 *  /d/Sparkle/area/tutorial/farm/carrot_patch2a.c
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
#define            CROP_TYPE        "carrot"  /* what's planted here? */
#define            LOCATION         "mid"     /* where in the field?  */
#define            BUNNY_NUM        3         /* how many bunnies?    */

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

    add_exit("carrot_patch3", "northeast");
    add_exit("carrot_patch2", "southwest");

    reset_room();
} /* create_crop_room */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and objects as needed
 */
public void
reset_room()
{
    clone_bunny(BUNNY_NUM, "rabbit");
} /* reset_room */

