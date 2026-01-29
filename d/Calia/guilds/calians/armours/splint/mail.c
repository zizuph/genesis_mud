/* 	splint mail for the training knight in the crystalline palace

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
    set_name( ({ "splintmail", "armor", "armour", "mail" }) );
    set_adj("splint");
    set_short("splint mail");
    set_long(
	"This is splint mail.\n"
    );
    set_ac(21);
    set_at(A_BODY);
    set_am( ({ -1, 0, 1 }) );
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3000);
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