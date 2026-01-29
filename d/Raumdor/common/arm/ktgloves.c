inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* torn black gloves, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("gloves");
    set_adj("torn");
    add_adj("black");
    set_short("torn black gloves");
    set_long("These black leather gloves look worn and used. They are "+
      "ripped in some places, and smell of death and decay.\n");
    set_ac(10);
    set_at(A_HANDS);
    add_prop(OBJ_I_WEIGHT,400);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_VALUE,10);
}
