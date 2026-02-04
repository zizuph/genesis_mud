inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include <macros.h>

create_weapon()
{
    set_name("axe");
    set_adj("mecien's");
    set_short("Mecien's first axe");
    set_long(
   "This was Mecien's first axe, which he used to punish those " +
   "that displeased him.  It is shiny, and well cared for, but " +
   "not very sharp.  Mecien created a larger, sharper axe, because " +
   "he was placed in the position to use it more.  He gave this one " +
   "to King Bor-El.\n");
    set_hit(30);
    set_pen(30);
    set_wt(W_AXE);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 8000);
}
