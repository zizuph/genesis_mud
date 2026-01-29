inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("leggings");
    set_ac(23);
    set_at(A_LEGS);
    set_am( ({ 3, -2, 0 }) );
    add_adj("oiled");
    add_adj("cuir-boili");
    set_short("pair of oiled cuir-boili leggings");
    set_pshort("pairs of oiled cuir-boili leggings");
    set_long("Theese protective pieces of leather leggings have been " +
	     "oiled for shine and flexibility. They have a musty scent " +
             "and are decorated with carved dwarven runic art.\n");
    
    add_prop(OBJ_I_VOLUME, 650);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(23, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(23));
}

