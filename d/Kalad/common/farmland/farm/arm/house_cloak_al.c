/* Modified by Zignur 20171017 */

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

void
create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("black");
    set_short("black cloak of the house of Alexander");
    set_long("This black cloak is made of very soft, "+
    "fine woven cotton. A large emblem, along with the colors of this cloak, "+
    "mark it as property of the house of Alexander.\n");
    set_ac(3);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,380);
}

