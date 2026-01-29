/* 	silver shield for the silver knight in the crystalline palace

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron

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
    set_adj("silver");
    set_short("silver shield");
    set_long(BS("This is a shiny shield made of silver with a elven visage " +
	"on the front.  It is light, perfectly shaped, and rather strong.  " +
	"\n"));
    set_ac(20);
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