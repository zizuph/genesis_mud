/* 	bronze left gauntlet for the bronze knight in the crystalline palace

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

    if(str != "gauntlets" && str != "bronze gauntlets")
	return 0;

    rgauntlet = present("bronze_rgauntlet", environment(this_object()));

    if(!rgauntlet)
    {
	notify_fail("You only have a left-handed bronze gauntlet.\n");
	return 0;
    }

    tp = TP;
    rgauntlet->move(environment(tp));
    move(environment(tp));
    clone_object(ARMOUR("bronze_gauntlets"))->move(tp);
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
    add_action("attach", "join");
}

void
create_armour()
{
    set_name( ({ "bronze_lgauntlet", "gauntlet" }) );
    set_adj( ({ "left", "left-handed", "bronze" }) );
    set_short("left-handed bronze gauntlet");
    set_long("This is a left-handed bronze gauntlet.\n");
    set_ac(21);
    set_at(A_L_HAND);
    set_am( ({ 1, 0, -1 }) );
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
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