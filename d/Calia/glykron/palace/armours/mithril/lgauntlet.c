/* 	mithril left gauntlet for the white knight in the crystalline palace

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
    add_action("attach", "attach");
    add_action("attach", "group");
    add_action("attach", "pair");
}

int
attach(string str)
{
    object tp, rgauntlet;

    if (str != "gauntlets" && str != "mithril gauntlets")
	return 0;

    rgauntlet = present("mithril_rgauntlet", environment(THIS));

    if(!rgauntlet)
    {
	notify_fail("You only have a left-handed mithril gauntlet.\n");
	return 0;
    }

    rgauntlet->move(environment(TP));	/* temporary */
    move(environment(TP));		/* temporary */
    clone_object(ARMOUR("mithril_gauntlets"))->move(TP);
    rgauntlet->remove_object();
    remove_object();
    write("Ok.\n");
    return 1;
}

void
create_armour()
{
    set_name( ({ "gauntlet", "mithril_lgauntlet" }) );
    set_adj( ({ "left", "left-handed", "mithril" }) );
    set_short("left-handed mithril gauntlet");
    set_long("This left-handed gauntlet is made of a mithril alloy.\n");
    set_ac(17);
    set_at(A_L_HAND);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 1250);
    add_prop(OBJ_I_VOLUME, 2500);
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