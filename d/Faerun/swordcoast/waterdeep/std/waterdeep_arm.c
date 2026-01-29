/*
 * waterdeep/std/waterdeep_arm.c
 * Standard file for armour from the City of Waterdeep
 *
 * Created by Brine, Feb 2021
 */

#pragma strict_types
#pragma no_clone

#include "../defs.h"

inherit "/std/armour";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_waterdeep_armour()
{
    // Redefine
}

void
create_armour()
{
    setuid();
    seteuid(getuid());
    add_prop(IS_WATERDEEP_ITEM, 1);
    create_waterdeep_armour();
}
