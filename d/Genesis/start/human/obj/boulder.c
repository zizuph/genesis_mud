/*
 * Changed to only break rules when wielded by NPCs.
 * 2007-04-27 - Cotillion
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>

#include "../defs.h"


void
create_weapon()
{
    set_name( ({"boulder", "stone"}) );
    set_adj("large");

    set_hit(70);
    set_pen(40);

    set_wt(W_CLUB);
    set_wf(TO);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 45000);
    //add_prop(OBJ_M_NO_BUY, 1);
    //add_prop(OBJ_M_NO_SELL, 1);

    set_long("This boulder must weigh several hundred kilos.\n");
    set_short("large boulder");
}



mixed
wield(object what)
{
    if  (!interactive(TP)) return 0; //Wielded by a NPC
	
	if  ((TP->query_skill(SS_WEP_CLUB) > 60) &&
		 (TP->query_base_stat(SS_CON) > 120) &&
		 (TP->query_base_stat(SS_STR) > 180))
		{
			write("You carefully feel the weight of the huge boulder.\n");
			return 0;
		}

    TP->add_fatigue(-random(200) - 10);
    return "You attempt, foolishly, to wield the huge boulder. You are "+
	"lucky you did not injure yourself.\n"
	+ "You feel more tired.\n";
}


mixed
unwield(object what)
{
    set_hit(1);
    set_pen(1);
    return 0;
}
