inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
    ::create_weapon();
    set_name("club");
    set_adj("billy");
    set_long("A darkened, almost black piece of carved wood around two "+
      "feet in length and relatively narrow for its size. It looks like the "+
      "perfect street brawling weapon.\n");
    set_hit(20);
    set_pen(8);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_VALUE,360);
    add_prop(OBJ_I_WEIGHT,2000);
    add_prop(OBJ_I_VOLUME,2000);
}
