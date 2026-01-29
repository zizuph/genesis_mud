/* 	golden shield for the gold knight in the crystalline palace

    coder(s):   Glykron

    history:    17/7/95     typo taken out                  Maniac
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
create_armour()
{
    set_name("shield");
    set_adj( ({ "gold", "golden" }) );
    set_short("gold shield");
    set_long("This is a shiny shield made of gold with a human face on the " +
	"front.  It is heavy, shiny, perfectly shaped, and very strong.  " +
	"\n");
    set_ac(28);
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