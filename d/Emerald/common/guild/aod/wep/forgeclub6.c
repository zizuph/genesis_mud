/*
 *  /d/Emerald/common/guild/aod/wep/forgeclub6.c
 *
 *  One of the 10 club types that can be forged at the Army of Darkness
 *  Headquarters. The club's quality is on a scale of 0-9 with 9
 *  being highest. Look at the filename to see what level this one
 *  is. For complete information on the details of each club,
 *  refer to the inherited file.
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
 *
 *  2019-01-15: Carnak
 *      These items will now break from item expiration
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_WEP_DIR + "forged_weapon";


/* Prototypes */
public void        create_forged_weapon();


/*
 * Function name:        create_forged_weapon
 * Description  :        set up the weapon
 */
public void
create_forged_weapon()
{
    set_wep_level(6); /* darksteel face mallet */
} /* create_forged_weapon */

varargs void
remove_broken(int silent = 0)
{
    /* This was added so it can break from item expiration */
    if (calling_function() == "item_expiration_break") 
        ::remove_broken(silent);
    
    return;
}


int
set_dull(int du)
{
    return 0;
}