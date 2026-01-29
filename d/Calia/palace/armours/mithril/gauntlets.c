/* 	mithril gauntlets for the white knight in the crystalline palace

    coder(s):   Glykron
    history:
                17. 6.94    euid added                      Glykron
                25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
init()
{
    ::init();
    add_action("detach", "detach");
    add_action("detach", "divide");
    add_action("detach", "split");
    add_action("detach", "separate");
}

int
detach(string str)
{
    object tp;

    if (str != "gauntlets" && str != "mithril gauntlets")
	return 0;

    tp = TP;
    move(environment(tp));		/* temporary */
    clone_object(ARMOUR("mithril_lgauntlet"))->move(tp);
    clone_object(ARMOUR("mithril_rgauntlet"))->move(tp);
    remove_object();
    write("Ok.\n");
    return 1;
}

void
create_armour()
{
    set_name("gauntlets");
    set_pname("gauntlets");
    set_adj("mithril");
    set_short("pair of mithril gauntlets");
    set_pshort("pairs of mithril gauntlets");
    set_long("This pair of gauntlets is made of a mithril alloy.\n");
    set_ac(25);
    set_at(A_HANDS);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 5000);
    seteuid(getuid());
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}