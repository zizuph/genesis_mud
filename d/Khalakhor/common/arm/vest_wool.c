/*
 * vest_wool.c
 *
 * Common vest made from wool.
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
    set_long("This vest is made from a grey wool. It's " +
        "rather itchy, but thick and warm. ");
    create_vest("grey", "wool");
}