/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>

#include "../defs.h"

void
create_armour()
{
    set_name("mail");
    add_name("chainmail");
    set_short("dwarven mithril chainmail");
    set_adj(({"dwarven","mithril"}));
    set_long("This mail is made of mithril chains, skillfully forged by\n"+
             "dwarven craftsmen.\n");

    set_ac(31);
    set_am(({-1,1,0})); /* impale,slash,bludgeon */

    set_at(A_TORSO|A_ARMS);
    add_prop(OBJ_I_WEIGHT,17000);
    add_prop(OBJ_I_VOLUME,8000);
}
