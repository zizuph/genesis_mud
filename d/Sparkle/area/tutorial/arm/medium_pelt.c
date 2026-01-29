/*
 *  /d/Sparkle/area/tutorial/obj/medium_pelt.c
 *
 *  A version of the pelt that can be found on animals in the Tutorial.
 *
 *  Created December 2005, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit ARM_DIR + "pelt";


/* Prototypes */
public void        create_pelt();


/*
 * Function name:        create_pelt
 * Description  :        set up the pelt
 */
public void
create_pelt()
{
    Pelt_Type = "medium";
} /* create_pelt */
