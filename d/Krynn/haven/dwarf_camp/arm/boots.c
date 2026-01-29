inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "../../local.h"

public void
create_armour()
{
    set_name("boots");
    set_pname("boots");
    add_name(({"armour","pair of boots","pair of iron boots"}));
    add_pname(({"armours","pairs of boots","pairs of iron boots"}));
    set_adj(({"heavy","bulky"}));
    set_short("pair of heavy iron boots");
    set_pshort("pairs of heavy iron boots");
    set_ac(15);
    set_at(A_FEET);
    set_am( ({0,0,0}) );
    set_long("This is obviously dwarven in construction. Only a " +
      "dwarf would wear something like this. It is made of thick " +
      "iron chains, interwoven to create an extremely strong " +
      "armour, although bulky.\n");
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
}

