/*
 * bracers_hard_leather.c
 *
 * Hardened leather bracers to provide armour on the
 * forearm.
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
    set_long("These bracers have been crafted from " +
        "thick, hardened leather, and would serve " +
        "as fairly solid protection for your arms.\n");
    create_bracers("hardened leather");
}
