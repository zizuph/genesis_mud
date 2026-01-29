/* by Nerull */

#include "defs.h"
inherit "/std/armour";

void
create_armour()
{
    ::create_armour();
    set_name("helm");
    add_adj("black");
    set_short("black helm");
    set_long("This is a black horned helm of steel. It covers most of the " +
    "head, and looks rather uncomfortable to wear.\n"); 
    set_ac(25);
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,200);

}
