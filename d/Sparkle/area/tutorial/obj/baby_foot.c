/*
 *  /d/Sparkle/area/tutorial/obj/baby_foot.c
 *
 *  A loot item that can be taken from the rabbits on the farm in the
 *  Tutorial area.
 *
 *  Created December 2005, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit OBJ_DIR + "foot";


/* Prototypes */
public void        create_foot();


/*
 * Function name:        create_foot
 * Description  :        set up the foot
 */
public void
create_foot()
{
    Foot_Type = "baby";
} /* create_foot */
