/* created by Macker 06/30/94 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/icewall/local.h"

inherit MELT_BASE

create_weapon()
{
	set_name("knife");
	add_name("icy_knife");
	add_name("dagger");
	set_pname("knives");
	set_pshort("knives");
	set_adj("icy");
	set_short("icy knife");
	set_long("This is a knife made entirely of ice. The handle is " +
	"a bit slippery, but it is very sharp.\n");
	set_default_weapon(12, 19, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH);
	add_prop(OBJ_I_VOLUME, 1000);
	add_prop(OBJ_I_WEIGHT, 1000);
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
