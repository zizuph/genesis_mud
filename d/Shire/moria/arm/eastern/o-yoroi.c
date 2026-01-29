#include "defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit BASE_ARMOUR;

CONSTRUCT_ARMOUR
{
    set_name(({"o-yoroi", "yoroi", "armour"}));
    add_adj(({"oriental", "shoulder"}));
    set_short("o-yoroi");
    set_long("This O-yoroi is an Oriental armour consisting of a " +
	     "strengthened box-like device that fits over the shoulders "+
	     "to provide torso protection for the wearer. It looks quite "+
	     "bulky, but gives improved protection over the other forms "+
	     "of Oriental armour.\n");

    set_ac(14);
    set_am(({1,1,-2}));
    set_at(A_NECK);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}

int *
query_shield_slots()
{
    return ({ A_TORSO });
}
