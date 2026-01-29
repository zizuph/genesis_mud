/* created by Aridor, 03/17/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("hammer");
    set_adj("mining");
    set_short("mining hammer");
    set_long("It's a normal looking hammer, used for mining. It " +
	     "does appear very well crafted and sturdy.\n");
    set_default_weapon(10, 19, W_CLUB, W_BLUDGEON, W_ANYH);
    set_likely_break(1);
    set_likely_break(1);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 4000);
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

