#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

public void
create_terel_armour()
{
    set_name("robe");
    set_adj("black");

    set_short("black robe");
    set_long("A jet black robe, somewhat tattered.\n");
    set_ac(30);
    set_at(A_ROBE);
    set_am(({0, 0, 0}));
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, 100);
}
