/* 	white cloak for the white knight in the crystalline palace

    coder(s):   Glykron

    history:    24. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("cloak");
    set_adj("white");
    set_short("white cloak");
    set_long("This is a dazzling white cloak.\n");
    set_ac(15);
    set_at(A_ROBE);
    set_am( ({0, 0, 0}) );
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 5000);
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