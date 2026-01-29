/*
 * bracers_scale.c
 *
 * These bracers are leather, covered in metal plates.
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
        "leather, and have had steel plates riveted " +
        "to them to form good armour.\n");
    create_bracers("scale mail");
}
