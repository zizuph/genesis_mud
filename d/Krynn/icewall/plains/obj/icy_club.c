/* Created by Macker 7/27/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/icewall/local.h"

inherit MELT_BASE



create_weapon()
{
	set_name("club");
	add_name("icy_club");
	set_adj("ice");
	set_adj("big");
	set_long("It is a big club made of ice.\n");
	set_short("big ice club");
	set_default_weapon(25,30, W_CLUB, W_BLUDGEON, W_BOTH);
	add_prop(OBJ_I_VOLUME, 1900);
    add_prop(OBJ_I_WEIGHT, 1500);
	make_me_meltable();
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
