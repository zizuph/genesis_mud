/*Created by Macker 07/20/94*/

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
/*
#include "../local.h"
*/



create_weapon()
{
	set_name("pole");
	set_adj("fishing");
	set_adj("wooden");
	set_long("It is a fishing pole. Nothing special.\n");
	set_default_weapon(20, 10, W_POLEARM, W_BLUDGEON, W_BOTH);
	add_prop(OBJ_I_VOLUME, 1200);
	add_prop(OBJ_I_WEIGHT, 1000);
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
