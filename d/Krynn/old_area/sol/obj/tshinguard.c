inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("guards");
    set_ac(23);
    set_at(A_LEGS);
    set_am( ({ 3, -2, 0 }) );
    add_adj("rusty");
    add_adj("shin");
    set_short("pair of rusty shin guards");
    set_pshort("pairs of rusty shin guards");
    set_long("A pair of rusty shin guards, they were formerly coloured " +
	     "blue. They seem to be made out of some sort of steel. " +
             "They look like something someone picked up on the side " +
             "of the road.\n");
    add_prop(OBJ_I_VOLUME, 650);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(23, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(23));
}

