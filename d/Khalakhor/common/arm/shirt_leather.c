/*
 * shirt_leather.c
 *
 * Common shirt made from soft leather.
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
    set_long("The pullover shirt is made from soft " +
        "brown leather, probably deerskin. It affords " +
        "only a little protection, but is soft and " +
        "very comfortable.\n");
    create_shirt("brown", "leather");
}
