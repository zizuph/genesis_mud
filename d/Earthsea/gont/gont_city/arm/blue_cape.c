#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 15

public void
create_armour()
{
    set_name("cape");
    set_pname("capes");
    set_adj("blue");
    set_adj("royal");
    set_short("handsome blue cape");
    set_pshort("handsome blue capes");
    set_long("A handsome blue cape. A beautifully made cape meant for " +
        "a hero.\n");
    set_ac(ARMOUR_CLASS);
    set_at(A_ROBE);
    set_am( ({-2,-2,0}) );
    add_prop(OBJ_I_WEIGHT, 2000 + (random(50) -  25));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(25) + 200);
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
