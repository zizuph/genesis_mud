/* 
 * File: dwarven_boots.c
 * Kragh's boots.
 *
 * Blizzard, 05/2003
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
    set_adj("dwarven");
    add_adj("leather");
    set_short("pair of dwarven boots");
    set_long("These heavy leather boots are reinforced with steel " +
        "bands, and have heavy metal caps on the toes. They are of sturdy " +
        "manufacture, meant for durbality and toughness - ugly, but " +
        "effective.\n");
    set_default_armour(10, A_FEET, (({ -1, 1, 0})), 0);
  
    add_prop(OBJ_I_WEIGHT, 900);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) + random(100) );

}




