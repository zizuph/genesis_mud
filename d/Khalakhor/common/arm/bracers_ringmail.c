/*
 * bracers_ringmail.c
 *
 * These bracers are leather, covered in iron rings.
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
    set_long("These bracers are made from sturdy " +
        "leather, to which has been sewn a series " +
        "of metal rings to increase their protection.\n");
    create_bracers("ringmail");
}
