/*
 * bracers_leather.c
 *
 * Leather bracers to provide armour on the forearm.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/common/arm/bracers_base";

public void
create_khalakhor_armour()
{
    set_long("These soft leather bracers are sturdily " +
        "crafted and fit snugly on the forearm of the " +
        "wearer.\n");
    create_bracers("leather");
}
