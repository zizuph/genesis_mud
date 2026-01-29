/* gresolle -92 */

#pragma save_binary
#pragma strict_types

inherit "/std/armour";

#include <wa_types.h>

#include "defs.h"

void
create_armour()
{
    set_name("mail");
    set_short("dwarven iron platemail");
    add_name("platemail");
    set_adj(({"dwarven","iron"}));
    set_long("This is an iron platemail.\n"+
             "You notice that it covers parts of the arms as well as the chest.\n");

    set_ac(20);
    set_am(({1,1,0})); /* impale,slash,bludgeon */

    set_at(A_TORSO|A_ARMS);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,8000);
}

