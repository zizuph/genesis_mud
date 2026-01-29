/*
 *  /d/Sparkle/area/tutorial/obj/crop_potato.c
 *
 *  A crop that can be pulled from the fields in the Tutorial.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit OBJ_DIR + "crop";


/* Prototypes */
public void        create_crop();


/*
 * Function name:        create_crop
 * Description  :        set up the crop
 */
public void
create_crop()
{
    Crop_Type = "potato";
} /* create_crop */
