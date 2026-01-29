inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("questring");
    add_name("ring");
    set_adj("sparkling");
    set_short("sparkling ring");
    set_long("This is a very beautiful sparkling ring. Engraved on "+
    "the side you see: Lord Aemilius IV.\n");
    set_ac(0);
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT,40);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,500);
}

