/*
 * Goblin garrison - regular chainmail
 * TAPAKAH, 04/2005
 */
inherit "/d/Khalakhor/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../camp/camp.h"

void
create_khalakhor_armour()
{   
    set_name("cloak");
    set_pname("cloaks");

    set_adj("rough");
    set_adj("woolen");

    set_short("rough woolen cloak");
    set_pshort("woolen cloaks");

    set_long("This cloak serves the regular troops of the goblin garrison\n"+
	     "It is rough and made of thick wool, and looks to be quite\n"+
	     "warm and protective.\n");

    set_ac(ACLASS);
    set_at(A_ROBE);
    set_am(({-2,-2,0}));

    add_prop(OBJ_I_WEIGHT, 2400);
    add_prop(OBJ_I_VOLUME, 1800);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ACLASS));
    add_prop(GG_PROPERTY,1);
}
