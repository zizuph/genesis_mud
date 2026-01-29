#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit BASE_ARMOUR;

CONSTRUCT_ARMOUR
{
    set_name( ({"armour", "haraate", "hara-ate", "plate", 
		"breastplate"}) );
    set_short("hara-ate");
    set_adj(({"oriental", "breast"}));
    set_long("You are looking at an Oriental style type of armour. "+
	     "It is a breastplate constructed of metal plates fastened "+
	     "to a leather jerkin, most often used by the Samarai.\n");
    set_ac(21);
    set_am(({1,1,-2}));
    set_at(A_TORSO);
}

