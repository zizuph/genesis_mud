/*
 *  /d/Emerald/common/guild/aod/arm/forgearm11.c
 *
 *  One of 12 armours that can be forged at the Army of Darkness
 *  Headquarters. The armour's quality is on a scale of 0-11 with 11
 *  being highest. Look at the filename to see what level this one
 *  is. For complete information on the details of each armour,
 *  refer to the inherited file.
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ARM_DIR + "forged_armour";


/* Prototypes */
public void        create_forged_armour();


/*
 * Function name:        create_forged_armour
 * Description  :        set up the armour
 */
public void
create_forged_armour()
{
    set_arm_level(11); /* pair of vast darksilver bracers */
} /* create_forged_armour */

