inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("vest");
    set_adj("tanned");
    add_adj("leather");
    set_long("A large vest fashioned from tanned and cured leather. It "+
      "seems to be of fairly good quality, though a bit weatherworn.\n");
    set_ac(15);
    set_am(({-5,-3,5}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,250);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_WEIGHT,1500);
}
