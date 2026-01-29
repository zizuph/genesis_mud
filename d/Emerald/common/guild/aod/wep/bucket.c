/*
 *  /d/Emerald/common/guild/aod/wep/bucket.c
 *
 *  Brofus' bucket!
 *
 *  Copyright (c) June 2006, by Cooper Sherry (Gorboth)
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
    set_wep_level(10); /* twisted sheet of scrap iron */
} /* create_forged_weapon */

