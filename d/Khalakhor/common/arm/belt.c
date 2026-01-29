/*
 * belt.c
 *
 * A simple leather belt.
 *
 * Khail - August 12, 1997
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"

#define AC 1

inherit "/std/armour";

public void
create_armour()
{
    set_name("belt");
    set_short("wide leather belt");
    set_pshort("wide leather belts");
    set_adj("wide");
    add_adj("leather");
    set_long("The wide leather belt is simple in " +
             "construction, adorned only by the heavy " +
             "brass buckle at one end.\n");
    
    set_ac(AC);
    set_at(A_WAIST);
    set_af(TO);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
}
