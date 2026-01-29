inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
    set_name("guards");
    set_ac(31);
    set_at(A_LEGS);
    set_am( ({ 5, -3, -2 }) );
    add_adj("white");
    add_adj("shin");
    set_short("pair of white shin guards");
    set_pshort("pairs of white shin guards");
    set_long("A pair of white shin guards, they are made of some white " +
	     "colored metal, which looks like a kind of steel.\n");
    add_prop(OBJ_I_VOLUME, 650);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(31, A_LEGS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(31));

}
