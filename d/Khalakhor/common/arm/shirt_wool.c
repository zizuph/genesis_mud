/*
 * shirt_wool.c
 *
 * Common shirt made from wool.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/d/Khalakhor/common/arm/shirt_base";

public void
create_armour()
{
    set_long("The pullover shirt is made from a grey " +
        "wool. Loose-fitting, it's a bit itchy, but " +
        "otherwise warm and comfortable.\n");
    create_shirt("grey", "wool");
}