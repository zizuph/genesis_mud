inherit "/d/Khalakhor/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../village/village.h"
    set_name("shirt");
    set_pname("shirts");

    set_adj("rough");
    set_adj("woolen");

    set_short("rough woolen shirt");
    set_pshort("woolen shirts");

    set_long("This shirt is rough and made of thick wool, and looks to be quite\n"+
	     "warm and protective.\n");

    set_ac(VRCLASS);
    set_at(A_BODY);
    set_am(({2,2,2}));

    add_prop(OBJ_I_WEIGHT, 3400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(VACLASS));

}
