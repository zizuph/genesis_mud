inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

/* A shiny merchant's dagger, by Sarr */

void
create_weapon()
{
    ::create_weapon();
   set_name("dagger");
   add_adj("black");
   add_adj("curved");
   set_short("wicked dagger");
    set_long( 
      "This is a wicked looking dagger with a black blade. It "+
     "is made of an unknown metal, and looks rather deadly.\n");
    set_hit(20);
    set_pen(20);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT,800);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE,800);
}

