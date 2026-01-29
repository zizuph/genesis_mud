inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("hat");
    set_adj("expensive");
    set_short("expensive hat");
    set_long("This large hat is studded with jewels and other fine "+
    "goodies. It looks very fancy and expensive.\n");
    set_ac(1);
    set_at(A_HEAD);
    add_prop(OBJ_I_WEIGHT,80);
    add_prop(OBJ_I_VOLUME,60);
    add_prop(OBJ_I_VALUE,250);
}

