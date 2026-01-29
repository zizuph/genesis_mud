/* 	silver right glove for the silver knight in the crystalline palace

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
    object tp, lglove;

    if (str != "gloves" && str != "silver gloves")
	return 0;

    lglove = present("silver_lglove", environment());

    if (!lglove)
    {
	notify_fail("You only have a right-handed silver glove.\n");
	return 0;
    }

    tp = TP;
    lglove->move(environment(tp));	/* temporary */
    move(environment(tp));		/* temporary */
    clone_object(ARMOUR("silver_gloves"))->move(tp);
    lglove->remove_object();
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
    set_name( ({ "silver_rglove", "glove" }) );
    set_adj( ({ "right", "right-handed", "silver" }) );
    set_short("right-handed silver glove");
    set_long("This is a light right-handed silver glove.\n");
    set_ac(24);
    set_at(A_R_ARM);
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