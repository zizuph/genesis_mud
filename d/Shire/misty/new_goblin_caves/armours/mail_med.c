#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"

#define ARMOUR_CLASS 24+random(3)

void
create_armour()
{
    set_name("mail");

    set_adj("nasty");

    set_short("nasty mail");
    set_pshort("nasty mails");

    set_long("This mail was made by goblins. It is not the best "+
      "armour that you ever seen but still it is very good if you realize "+
      "that it is goblin made.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ -2, -2, 4 }) );

    add_prop(OBJ_I_WEIGHT, 8400);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(151) - 75);
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
