/*
 * waterdeep/std/waterdeep_wep.c
 * Standard file for weapons from the City of Waterdeep
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types
#pragma no_clone

#include "../defs.h"

inherit "/std/weapon";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_waterdeep_weapon()
{
    // Redefine
}

void
create_weapon()
{
    setuid();
    seteuid(getuid());

    add_prop(IS_WATERDEEP_ITEM, 1);
    create_waterdeep_weapon();
}
