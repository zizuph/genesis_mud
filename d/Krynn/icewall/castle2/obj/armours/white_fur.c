/* Navarre Feb 2007: Changed to use correct AC for calculations */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


inherit "/lib/keep";

void
create_armour()
{
    set_name("fur");
    set_ac(15);
    set_at(A_ROBE);
    set_adj("heavy");
    add_adj("white");
    set_short("heavy white fur");
    set_long("This heavy white fur has been torn off the back of a " +
      "polar bear. It is smelly and ill kept - a sad remain of a once " +
      "proud and wild animal.\n");
    add_prop(OBJ_I_VOLUME, 8075);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
}


