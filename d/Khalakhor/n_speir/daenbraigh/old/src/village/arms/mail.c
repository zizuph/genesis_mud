/*
 * Goblin village - smith's mail
 * TAPAKAH, 09/2005
 */
#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       

#include "../../village/village.h"

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{   
    set_name("mail");
    set_pname("mails");

    set_adj("sturdy");
    set_adj("ring");

    set_short("sturdy ring mail");
    set_pshort("ring mails");

    set_long("This mail is sturdy and made of thick rings, and looks to be "+
	     "quite heavy and protective.");

    set_ac(V_ACLASS*2);
    set_at(A_TORSO);
    set_am(({1,1,1}));

    add_prop(OBJ_I_WEIGHT, 6400);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(V_ACLASS*2));

}
