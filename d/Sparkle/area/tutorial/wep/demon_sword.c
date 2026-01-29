/*
 *  /d/Sparkle/area/tutorial/wep/demon_sword.c
 *
 *  A version of the demon weapons that can be found on castle guards
 *  in the Tutorial.
 *
 *  Created December 2005, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit WEP_DIR + "demon_weapon";


/* Prototypes */
public void        create_demon_weapon();


/*
 * Function name:        create_demon_weapon
 * Description  :        set up the weapon
 */
public void
create_demon_weapon()
{
    Weapon_Type = "sword";
} /* create_demon_weapon */
