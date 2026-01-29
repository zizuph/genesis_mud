#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 33

public void
create_armour()
{
    set_name("mask");
    set_pname("masks");
    set_adj("blue");
    set_adj("steel");
    set_short("blue steel mask");
    set_pshort("blue steel masks");
    set_long("A blue face mask. This mask offers great " +
        "protection. It not only covers the wearer's entire " +
        "head, it also covers the wearer's neck.\n");
    set_ac(ARMOUR_CLASS);
    set_at(A_HEAD);
    set_am( ({2,2,2}) );
    add_prop(OBJ_I_WEIGHT, 2000 + (random(250)));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50));
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
