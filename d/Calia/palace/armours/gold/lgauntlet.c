/* 	gold left gauntlet for the gold knight in the crystalline palace

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
    object tp, rgauntlet;

    if(str != "gauntlets" && str != "gold gauntlets")
	return 0;

    rgauntlet = present("gold_rgauntlet", environment(this_object()));

    if(!rgauntlet)
    {
	notify_fail("You only have a left-handed gold gauntlet.\n");
	return 0;
    }

    tp = TP;
    rgauntlet->move(environment(tp));
    move(environment(tp));
    clone_object(ARMOUR("gold_gauntlets"))->move(tp);
    rgauntlet->remove_object();
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
    set_name( ({ "gold_lgauntlet", "gauntlet" }));
    set_adj( ({ "left", "left-handed", "gold" }));
    set_short("left-handed gold gauntlet");
    set_long("This is a left-handed gold gauntlet.\n");
    set_ac(10);
    set_at(A_L_HAND);
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