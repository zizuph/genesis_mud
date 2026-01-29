/*
 * vest_hard_leather.c
 *
 * Common vest made from hardened leather.
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
    set_long("This vest is made from fairly thick " +
        "leather, and the leather's been boilded to harden " +
        "it somewhat. Thick metal studs decorate the " +
        "shoulders. ");
    create_vest("brown", "hard leather");
}