/*
 * vest_cloth.c
 *
 * Common vest made from cloth.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/d/Khalakhor/common/arm/vest_base";

public void
create_armour()
{
    set_long("This vest is made from a tan-coloured " +
        "cloth, and is made for a loose fit. ");
    create_vest("tan", "cloth");
}