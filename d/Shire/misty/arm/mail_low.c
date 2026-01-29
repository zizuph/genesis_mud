#pragma save_binary

inherit "/std/armour";

#include <formulas.h>
#include <wa_types.h>
#include "/d/Shire/sys/defs.h"

#define ARMOUR_CLASS 17+random(3)

void
create_armour()
{
    set_name("chainmail");
    add_name("mail");

    set_adj("iron");

    set_short("iron chainmail");
    set_pshort("iron chainmails");

    set_long("This mail is made by goblins.  It is made of iron "+
      "and looks strong.  It is typical goblin armour.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);
    set_am( ({ -3, 0, 3 }) );

    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) + random(101) - 50);
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
