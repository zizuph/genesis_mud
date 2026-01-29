#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"

#define ARMOUR_CLASS 20+random(3)

void
create_armour()
{
    set_name("armour");

    set_adj("leather");

    set_short("leather armour");
    set_pshort("leather armours");

    set_long("lightweight moulded leather armour.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ -2, -2, 4 }) );

    add_prop(OBJ_I_WEIGHT, 4400);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(50) - 75);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
