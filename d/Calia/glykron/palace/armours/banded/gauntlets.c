/* 	the banded gauntlets worn by the guardian knight in the
	crystalline palace

    coder(s):   Glykron
    history:
                17. 6.94    euid added                      Glykron
                25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron

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
}

int
detach(string str)
{
    object tp;
    if (str != "gauntlets" && str != "banded gauntlets")
	return 0;
    tp = TP;
    move(environment(tp)); /* temporary */
    clone_object(ARMOUR("banded_lgauntlet"))->move(tp);
    clone_object(ARMOUR("banded_rgauntlet"))->move(tp);
    remove_object();
    write("Ok.\n");
    return 1;
}

void
create_armour()
{
    set_name("gauntlets");
    set_pname("gauntlets");
    set_adj("banded");
    set_short("pair of banded gauntlets");
    set_pshort("pairs of banded gauntlets");
    set_long("This is a pair of banded gauntlets.\n");
    set_ac(16);
    set_at(A_L_HAND | A_R_HAND);
    set_am( ({ 2, 0, -2 }) );
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
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