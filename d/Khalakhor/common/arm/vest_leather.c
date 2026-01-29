/*
 * vest_leather.c
 *
 * Common vest made from leather.
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
  set_long("This vest is made from a thin, soft leather. " +
           "Probably deerskin or some similar material, it's " +
           "quite comfortable to wear. ");
  create_vest("brown", "leather");
}
