/* 	bronze gauntlets for the bronze knight in the crystalline palace

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
detach(string str)
{
    object tp;

    if(str != "gauntlets" && str != "bronze gauntlets")
	return 0;

    tp = TP;
    move(environment(tp));		/* temporary */
    clone_object(ARMOUR("bronze_lgauntlet"))->move(tp);
    clone_object(ARMOUR("bronze_rgauntlet"))->move(tp);
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
    set_name( ({ "pair", "gauntlets" }) );
    set_pname( ({ "pairs", "gauntlets" }) );
    set_adj("bronze");
    set_short("pair of bronze gauntlets");
    set_pshort("pairs of bronze gauntlets");
    set_long("This is a pair of bronze gauntlets.\n");
    set_ac(30);
    set_at(A_HANDS);
    set_am( ({ 2, 0, -2 }) );
    add_prop(OBJ_I_WEIGHT, 4000);
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