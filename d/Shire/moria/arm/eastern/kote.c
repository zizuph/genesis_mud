#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit BASE_ARMOUR;

CONSTRUCT_ARMOUR
{
    set_name( ({"kote", "sleeves"}) );
    set_short("pair of kote");
    set_pshort("pairs of kote");
    set_adj(({"oriental"}));
    set_long("These are a pair of Oriental armoured sleeves, constructed "+
	     "of bamboo bound to woven straw to protect the lower arms " +
	     "of the wearer.\n");
    set_ac(5);
    set_am(({0,1,-1}));
    set_at(A_ARMS);
}

