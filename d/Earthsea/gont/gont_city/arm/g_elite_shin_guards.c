#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 27

public void
create_armour()
{
    set_name("guards");
    set_pname("guardses");
    set_adj("shiny");
    set_adj("steel");
    set_short("pair of steel shin guards");
    set_pshort("pairs of steel shin guards");
    set_long("This pair of shin guards is standard issue for the" +
        " elite Gont guards. The polished steel seems to shine" +
        " like the sun. It seems well made and quite" +
        " protective.\n");
    set_ac(ARMOUR_CLASS);
    set_at(A_LEGS);
    set_am( ({1,1,1}) );
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
