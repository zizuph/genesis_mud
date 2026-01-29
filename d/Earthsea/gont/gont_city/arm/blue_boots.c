#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 30

public void
create_armour()
{
    set_name("boots");
    set_pname("bootses");
    set_adj("blue");
    set_adj("steel");
    set_short("pair of blue steel boots");
    set_pshort("pairs of blue steel boots");
    set_long("A pair of blue steel boots. It is very well made. " +
        "A fur interior makes this pair of boots extremely " +
        "comfortable, and the steel exterior makes them highly " +
        "protective.\n");
    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);
    set_am( ({2,2,2}) );
    add_prop(OBJ_I_WEIGHT, 2500 + (random(25) -  10));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(25) - 10);
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
