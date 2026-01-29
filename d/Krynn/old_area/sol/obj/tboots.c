inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("boots");
    set_ac(25);
    set_at(A_FEET);
    add_adj("spurred");
    add_adj("grimy");
    set_long("This pair of boots is disgusting. They may have " +
             "once been golden in colour, but it is impossible to tell " + 
             "for sure, as they are inundated with worn-in grime. " +
             "The back of each boot carries a spur, so they seem to " +
             "be used for riding.\n");
    set_short("pair of grimy spurred boots");
    set_pshort("pairs of grimy spurred boots");
    add_prop(OBJ_I_VOLUME, 1400);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
}

