/*
 * shirt_cloth.c
 *
 * Common shirt made from cloth.
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
    set_long("This shirt is made from a tan-coloured " +
        "cloth, and is made for a loose fit.\n");
    create_shirt("tan", "cloth");
}