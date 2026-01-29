/* Clown suit by Sarr */
inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
void
create_armour()
{
    ::create_armour();
    set_name("suit");
    set_adj("clown");
    set_long(
     "Its a brightly colored clown suit. The kind you find on fools.");
    set_ac(2);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT,800);
    add_prop(OBJ_I_VOLUME,800);
    add_prop(OBJ_I_VALUE,800);
}

