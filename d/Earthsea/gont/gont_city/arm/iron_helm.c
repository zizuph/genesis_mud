/*
 *   armour for the seamen at Gont Port
 *   Amelia 3/8/98
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>

#define ARMOUR_CLASS 30

public void
create_armour()
{
    set_name(({"helm", "helmet"}));
    add_adj("blackened");
    add_adj("iron");
    set_short("blackened iron helmet");
    set_long("A helmet made of blackened iron "+
        "with a guard to protect the nose.\n");
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
