/*  A ringmail for the kargs at Gont */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#define ARMOUR_CLASS 17

public void
create_armour()
{
    set_name("ringmail");
    set_adj("bronze");
    set_short("bronze ringmail");
    set_long("A ringmail made from hard leather "+
        "tightly sewn with rings of bronze. It is made to cover "+
        "the chest and shoulders, and bears an insignia of "+
        "the Lord of Gont over the breast bone.\n");
    set_ac(ARMOUR_CLASS); 
    set_at(A_TORSO);
    set_am(({ -1, 2, -1 }));
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(100));
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
