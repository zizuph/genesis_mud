/* created by Macker 06/29/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

inherit MELT_BASE

create_weapon()
{
	set_name("longsword");
	add_name("icy_longsword");
	add_name("sword");
	set_adj("icy");
	set_short("icy longsword");
	set_long("A longsword made of pure ice! It looks very sharp.\n");
	set_default_weapon(20,25, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
	add_prop(OBJ_I_VOLUME, 2000);
	add_prop(OBJ_I_WEIGHT, 1500); /*It's ice...not metal*/
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
