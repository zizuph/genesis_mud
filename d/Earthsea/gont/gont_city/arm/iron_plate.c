/*  iron armour for seamen at Gont Port
*   Amelia 3/8/98
*/

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

#define ARMOUR_CLASS 25

public void
create_armour()
{
    set_name("platemail");
    set_adj(({"blackened","iron"}));
    set_short("blackened iron platemail");
    set_long("A platemail made from blackened "+
        "iron, created by a special process to prevent rust. "+
        "It provides good protection for the chest and shoulders.\n");
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
