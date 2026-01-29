/* 	silver left glove for the silver knight in the crystalline palace

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
detach(string str)
{
    object tp;

    if (str != "gloves" && str != "silver gloves")
	return 0;

    tp = TP;
    move(environment(tp));		/* temporary */
    clone_object(ARMOUR("silver_lglove"))->move(tp);
    clone_object(ARMOUR("silver_rglove"))->move(tp);
    remove_object();
    write("Ok.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("detach", "detach");
    add_action("detach", "divide");
    add_action("detach", "split");
    add_action("detach", "separate");
}

void
create_armour()
{
    set_name( ({ "pair", "gloves" }) );
    set_pname( ({ "pairs", "gloves" }) );
    set_adj("silver");
    set_short("pair of silver gloves");
    set_pshort("pairs of silver gloves");
    set_long("This is a pair of light silver gloves.\n");
    set_ac(35);
    set_at(A_ARMS);
    set_am( ({ 2, 0, -2 }) );
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 4000);
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