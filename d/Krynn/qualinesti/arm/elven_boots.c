/* 
 * File: elven_boots.c
 * High elven boots, worn by Qualinesti elves.
 *
 * Blizzard, 02/2003
 */

#pragma strict_types

inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

public void
create_armour()
{
    set_name("boots");
    add_name("armour");
    set_adj("elven");
    set_adj("leather");
    set_adj("high");
    set_short("pair of high boots");
    set_long("These high boots are nicely made of supple leather. They " +
        "are very light, allowing you to move silently in the forest.\n");
    set_default_armour(8, A_LEGS | A_ANKLES | A_FEET, (({ -1, 1, 0})), 0);
  
    add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
    add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8)+random(30));

}




