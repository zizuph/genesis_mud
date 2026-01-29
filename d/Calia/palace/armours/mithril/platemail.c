/* 	mithril armour for the white knight in the crystalline palace

    coder(s):   Glykron

    history:    24. 2.92    recovery added                  Glykron
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
    set_name( ({"platemail", "mail", "plate", "armor", "armour"}) );
    set_adj("mithril");
    set_short("suit of mithril platemail");
    set_pshort("suits of mithril platemail");
    set_long(BS(
	"This is an extremely well-crafted suit made of a strong mithril " +
	"alloy.  It covers the vital parts of the wearer.  " +
	"\n"));
    set_ac(36);
    set_at(A_BODY);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchanted" }) );
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); 
    add_prop(MAGIC_AM_ID_INFO, ({"This armour seems to have been enchanted " +
           "by a powerful sorcerer.\n", 20}));
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
