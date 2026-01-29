inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
    set_name("robe");
    add_name("dark-robe");
    set_ac(25);
    set_at(A_ROBE);
    set_adj("hooded");
    add_adj("dark");
    set_short("hooded dark-robe");
    set_long("This long black robe is typical of those " +
      "magic users that have passed the Test of High Sorcery " +
      "and have chosen the evil path to walk down.\n");
    add_prop(OBJ_I_VOLUME, 4750);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(3, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
}


