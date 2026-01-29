inherit "/std/weapon";
inherit "/d/Immortal/rogon/open/tell";
inherit "/d/Immortal/rogon/open/message";

#include "defs.h"
#include <wa_types.h>
#include "/sys/stdproperties.h"
#include <macros.h>
#include <formulas.h>
#include <stdproperties.h>

void

create_weapon()
{

    set_name(({"maul","bolgard","flail"}));
    set_short("mithril flail");
    set_wt(W_CLUB);
    set_pname(({"mauls","bolgards","flails"}));
    set_long(break_string("This huge maul is made for crushing bodies "
	    +"and smashing the guts out of humans. It is made of the "
	    +"finest Mithril from Khazad-dum. \n", 76));

    set_adj(({"mithril","ruling"}));

    set_default_weapon(35, 40, W_CLUB, W_BLUDGEON, W_BOTH, 0);

    add_prop(OBJ_I_WEIGHT, 25000);
    add_prop(OBJ_I_VOLUME, 20000);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35, 40) + random(100) + 30);

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

init()
{
    ::init();
    add_action("do_smash", "smash");
    add_action("do_love", "love");
}

int
do_smash(string arg)
{
    if (!id(arg))
	return 0;
    action("$N $smash some peanuts with $p flail!\n");
    return 1;
}

int
do_love(string arg)
{
    if (!id(arg))
	return 0;
    action("$N $kiss $p flail with great passion and $shout out: THIS is MY Club!\n");
    return 1;
}
