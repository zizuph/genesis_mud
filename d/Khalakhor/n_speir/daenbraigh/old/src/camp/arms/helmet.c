/*
 * Goblin garrison - regular chainmail
 * TAPAKAH, 04/2005
 */
#pragma strict_types

inherit "/d/Khalakhor/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../camp/camp.h"

void
create_khalakhor_armour()
{   
    set_name("helmet");
    set_pname("helmets");

    set_adj("rough");
    set_adj("iron");

    set_short("rough iron helmet");
    set_pshort("iron helmets");

    set_long("This helmet serves the regular troops of the goblin garrison\n"+
	     "It is rough and made of tempered iron, and looks to be quite a\n"+
	     "protective armour.\n");

    set_ac(ACLASS);
    set_at(A_HEAD);
    set_am(({-1,-1,1}));

    add_prop(OBJ_I_WEIGHT, 2400);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ACLASS));
    add_prop(GG_PROPERTY,1);
}
