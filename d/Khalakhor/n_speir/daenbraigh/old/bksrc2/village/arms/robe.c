inherit "/d/Khalakhor/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../village/village.h"
#include "../../nspeir.h"

void
create_khalakhor_armour()
{   
    set_name("robe");
    set_pname("robes");

    set_adj("rough");
    set_adj("woolen");

    set_short("rough woolen robe");
    set_pshort("woolen robes");

    set_long(BS("This robe looks thick and protecting from cold. It is woven from "+
		"rough wool and reinforced with some kind of unknown metallic threads.\n"));

    set_ac(VRCLASS);
    set_at(A_BODY);
    set_am(({2,2,2}));

    add_prop(OBJ_I_WEIGHT, 3400);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(VACLASS));

}
