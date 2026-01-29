/* 	mithril helmet for the white knight in the crystalline palace

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
    set_name("helmet");
    set_adj("mithril");
    set_short("mithril helmet");
    set_long("This is a large, pointy helmet made of a mithril alloy.\n");
    set_ac(22);
    set_at(A_HEAD);
    set_am( ({0, 0, 0}) );
    add_prop(OBJ_I_WEIGHT, 2500);
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