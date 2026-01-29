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
    set_name("sabre");
	add_name("icy_sabre");
	add_name("sword");
	add_name("sabre_quest_item");
	add_name("sabre_quest_ob5");
	set_adj("icy");
	set_short("icy sabre");
	set_long("A strange sabre which appears to be made of ice. " +
	"The blade is very sharp and could probably do some real damage.\n");
	set_default_weapon(25, 35, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 2600);
	add_prop(OBJ_I_WEIGHT, 1700); /*It's ice...not metal*/
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
