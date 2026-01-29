inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>



void
create_armour()
{
    set_name("helmet");
    set_ac(20);
    set_at(A_HEAD);
    set_am( ({ -5, 0, 5 }) );
    set_adj("horned"); 
    set_short("horned helmet");
    set_long("This is the typical head gear of a dwarf " +
      "from the hills... an impressive steel helmet with " +
      "two stubby horns protruding from its sides.\n");
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(9, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9));
}

