/* created by Aridor, 03/17/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("warhammer");
    add_name("hammer");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_adj("heavy");
    set_short("heavy warhammer");
    set_long("It's a heavy looking warhammer. It " +
	     "does appear very well crafted and sturdy.\n");
    set_default_weapon(20, 38, W_CLUB, W_BLUDGEON, W_BOTH);
    set_likely_break(4);
    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_WEIGHT, 16000);
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

