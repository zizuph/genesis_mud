inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* A Sarr Industries production */

void
create_armour()
{
    ::create_armour();
    set_name("teddy");
    set_adj("black");
    add_adj("lace");
    set_short("black lace teddy");
    set_long("A very sexy teddy with silky lace.\n");
    set_ac(1);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,15);
    add_prop(OBJ_I_VALUE,8);
}

