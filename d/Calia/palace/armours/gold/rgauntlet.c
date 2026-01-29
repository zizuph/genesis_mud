/* 	gold right gauntlet for the gold knight in the crystalline palace

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

int
attach(string str)
{
    object tp, lgauntlet;

    if (str != "gauntlets" && str != "gold gauntlets")
	return 0;

    lgauntlet = present("gold_lgauntlet", environment(this_object()));

    if (!lgauntlet)
    {
	notify_fail("You only have a right-handed gold gauntlet.\n");
	return 0;
    }

    tp = TP;
    lgauntlet->move(environment(tp));	/* temporary */
    move(environment(tp));		/* temporary */
    clone_object(ARMOUR("gold_gauntlets"))->move(tp);
    lgauntlet->remove_object();
    remove_object();
    write("Ok.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("attach", "attach");
    add_action("attach", "group");
    add_action("attach", "pair");
}

void
create_armour()
{
    set_name( ({ "gold_rgauntlet", "gauntlet" }) );
    set_adj( ({ "right", "right-handed", "gold" }) );
    set_short("right-handed gold gauntlet");
    set_long("This is a right-handed gold gauntlet.\n");
    set_ac(10);
    set_at(A_R_HAND);
    set_am( ({ 1, 0, -1 }) );
    add_prop(OBJ_I_WEIGHT, 2500);
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