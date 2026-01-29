/*
 *  /d/Emerald/common/guild/aod/wep/shovel.c
 *
 *  Smorny's shovel!
 *
 *  Copyright (c) July 2006, by Cooper Sherry (Gorboth)
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
    set_wep_level(11); /* giant filthy shovel */
} /* create_forged_weapon */

