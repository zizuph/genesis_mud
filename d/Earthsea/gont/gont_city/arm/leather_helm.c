/*
 *   armour for the seamen at Gont Port
 *   Amelia 3/8/98
 */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>

#define ARMOUR_CLASS 20

public void
create_armour()
{
    set_name(({"helm", "helmet"}));
    add_adj("leather");
    set_short("brown leather helmet");
    set_long("A helmet made of hardened leather "+
        "with earflaps to protect the ears.\n");
    set_at(A_HEAD);
    set_ac(ARMOUR_CLASS);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));
    add_prop(OBJ_I_VOLUME, 200);
}

public string 
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
