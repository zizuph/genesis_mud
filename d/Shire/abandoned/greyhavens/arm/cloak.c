/* Adapted from Anri's hobbit's equipment */
/* Standard hobbits equipment coded by Anri */
inherit "/std/armour";

#include "/sys/macros.h"
#include <stdproperties.h>
#include <wa_types.h>
#include "/sys/formulas.h"

void
create_armour()
{ set_name("cloak");
    set_short("short cloak");
    set_long("This is a short, stylish cloak.  It is trimmed " +
      "with fur, and is made for elves.\n");
    set_adj(({"short","stylish"}));
    set_ac(30);
    set_at(A_ROBE);
    set_am(({1,-2,1}));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12)-random(10));
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_WEIGHT,950);
}

string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void init_recover(string arg)
{
    init_arm_recover(arg);
}
