inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* worn black boots, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("boots");
    set_adj("worn");
    add_adj("black");
    set_short("worn black boots");
    set_long("These old, dirty boots look like they are made from some "+
    "strong, black leather. They are riped in some places, but still look "+
    "usable.\n");
    set_ac(10);
    set_at(A_FEET);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,3200);
    add_prop(OBJ_I_VALUE,30);
}
