/* 	mithril shield for the white knight in the crystalline palace

    coder(s):   Glykron

    history:    24. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron
                 9. 2.92    modified                        Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    set_name("shield");
    set_adj("mithril");
    set_short("mithril shield");
    set_long(BS(
	"This is a shiny shield made of mithril with a knight head on the " +
	"front.  " +
	"It is perfectly shaped, very strong, light, and unscratched.  " +
	"\n"));
    set_ac(27);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 5000);
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