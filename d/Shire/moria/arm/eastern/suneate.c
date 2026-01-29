#include "defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit BASE_ARMOUR;

CONSTRUCT_ARMOUR
{
    set_name(({"suneate", "greaves"}));
    add_adj(({"oriental", "leg"}));
    set_short("pair of suneate");
    set_pshort("pairs of suneate");
    set_long("These are basically the Oriental equivalent to " +
	     "leg greaves. They are made of bamboo-splints laced " +
	     "to a leather base.\n");
    set_ac(9);
    set_am(({1,1,-2}));
    set_at(A_LEGS);
}
