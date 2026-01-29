inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("apron");
    set_adj("sticky");
    add_adj("leather");
    set_long("A small leather apron, about halfling-sized. On it are several "+
      "dried stains from spilt beer and sweat.\n");
    set_ac(9);
    set_am(({-5,-5,5}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,250);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_WEIGHT,1000);
}
