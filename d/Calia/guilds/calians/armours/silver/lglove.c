/* 	silver left glove for the silver knight in the crystalline palace

    coder(s):   Glykron
    history:
                17. 6.94    euid added                      Glykron
                25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour.c";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

int
attach(string str)
{
    object tp, rglove;

    if(str != "gloves" && str != "silver gloves")
	return 0;

    rglove = present("silver_rglove", environment());

    if(!rglove)
    {
	notify_fail("You only have a left-handed silver glove.\n");
	return 0;
    }

    tp = TP;
    rglove->move(environment(tp));	/* temporary */
    move(environment(tp));		/* temporary */
    clone_object(ARMOUR("silver_gloves"))->move(tp);
    rglove->remove_object();
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
    set_name( ({ "silver_lglove", "glove" }) );
    set_adj( ({ "left", "left-handed", "silver" }) );
    set_short("left-handed silver glove");
    set_long("This is a light left-handed silver glove.\n");
    set_ac(24);
    set_at(A_L_ARM);
    set_am( ({ 1, 0, -1 }) );
    add_prop(OBJ_I_WEIGHT, 1250);
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