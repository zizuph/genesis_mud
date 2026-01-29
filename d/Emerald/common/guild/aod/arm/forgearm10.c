/*
 *  /d/Emerald/common/guild/aod/arm/forgearm10.c
 *
 *  One of 12 armours types that can be forged at the Army of Darkness
 *  Headquarters. The armour's quality is on a scale of 0-11 with 11
 *  being highest. Look at the filename to see what level this one
 *  is. For complete information on the details of each armour,
 *  refer to the inherited file.
 *
 *  Created February 2015, by Cooper Sherry (Gorboth)
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
    set_arm_level(10); /* fullplate of the behemoth */
} /* create_forged_armour */


/*
 * Function name:        exa_this_armour
 * Description  :        Yes, it is strange to mask the functionality
 *                       of exa/look, but here it is necessary to deal
 *                       with this unorthodox armour name.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        1 - we dealt with it in this function
 *                       0 - pass it on to the mudlib
 */
public int
exa_this_armour(string arg)
{
    if (arg != "breastplate of the behemoth" &&
        arg != "at breastplate of the behemoth")
    {
        return 0;
    }

    write(long());
    return 1;
} /* exa_this_armour */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(exa_this_armour, "exa");
    add_action(exa_this_armour, "look");
} /* init */
