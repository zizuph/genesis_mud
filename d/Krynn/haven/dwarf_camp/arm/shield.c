inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "/d/Krynn/haven/local.h"

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    add_name("armour");
    add_pname("armours");
    set_adj(({"heavy", "oak", "wooden"}));
    set_short("heavy oak shield");
    set_pshort("heavy oak shields");
    set_ac(20);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_long("This is heavy shield made of hardened oak wood, like "+
      "the Neidar, or hill dwarves, prefer. It is dented and full "+
      "of nicks and crevices, having obviously seen a lot of use.\n");
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 5500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}

