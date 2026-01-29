inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* black steel shortsword, by Sarr */
void
create_weapon()
{
    ::create_weapon();
set_name("small axe");
   add_name("axe");
   set_adj("spiked");
    set_long(
    "This is an axe with a sturdy hilt and a sharp blade. "+
    "It is finely crafted and balanced with a sharp spike.\n");
    set_hit(35);
    set_pen(25);
    set_wt(W_AXE);
    set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,800);
   add_prop(OBJ_I_VALUE,600);
}

