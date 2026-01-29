inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "/d/Krynn/haven/local.h"

public void
create_armour()
{
    set_name("helm");
    set_pname("helms");
    add_name(({"armour", "helmet"}));
    add_pname(({"armours", "helmets"}));
    set_adj(({"dented", "steel"}));
    set_short("dented steel helm");
    set_pshort("dented steel helms");
    set_ac(20);
    set_at(A_HEAD);
    set_am( ({0,0,0}) );
    set_long("This is an old, but still adequate, steel helm. It's "+
      "probably dwarven, judging from the craft and the horns on "+
      "either side, which the dwarves favour.\n");
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}

