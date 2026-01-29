/*
 *  /d/Sparkle/area/tutorial/arm/demon_helm.c
 *
 *  A version of the demon armour that can be found on castle guards
 *  in the Tutorial.
 *
 *  Created December 2005, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit ARM_DIR + "demon_armour";


/* Prototypes */
public void        create_demon_armour();


/*
 * Function name:        create_demon_armour
 * Description  :        set up the armour
 */
public void
create_demon_armour()
{
    Armour_Type = "helm";
} /* create_demon_armour */
