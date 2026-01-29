inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
    set_name("bandana");
    set_short("green bandana");
    set_long("This green bandana is simply a large piece of " +
      "cloth that can be wrapped around the head.\n");
    set_ac(2);
    set_am(({0,0,0}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 200);
}
