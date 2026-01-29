inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("armour");
    set_adj("small");
    add_adj("halfling");
    set_long("A tiny suit of leather armour, used by halfings.\n");
    set_ac(15);
    set_am(({0,0,5}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,400);
    add_prop(OBJ_I_VOLUME,2500);
    add_prop(OBJ_I_WEIGHT,25000);
}
