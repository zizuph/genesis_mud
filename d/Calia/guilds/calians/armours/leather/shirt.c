/* 	leather shirt for the knight's son in the crystalline palace

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name( ({ "shirt", "leather", "armor", "armour" }) );
    set_adj("leather");
    set_short("leather shirt");
    set_long(
	"This is a leather shirt.\n"
    );
    set_ac(5);
    set_at(A_BODY);
    set_am( ({ -1, 0, 1 }) );
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 1000);
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