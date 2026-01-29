inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* black steel shortsword, by Sarr */
void
create_weapon()
{
    ::create_weapon();
    set_name("shortsword");
    add_name("sword");
    set_adj("black");
    add_adj("steel");
    set_long(
    "This is a sword with a short blade made of black steel. You can barely\n"+
    "see any light reflected off its blade. The hilt is black and decorated\n"+
    "with some silver ornaments that gleam brightly in the light.\n");
    set_hit(35);
    set_pen(25);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VOLUME,800);
   add_prop(OBJ_I_VALUE,600);
}

