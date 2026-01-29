inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* Black studded leather armour, by Sarr */
void
create_armour()
{
    ::create_armour();
    set_name("gloves");
    set_adj("leather");
    add_adj("black");
    set_short("pair of black leather gloves");
    set_long("A pair of hardened leather gloves.\n");
   set_ac(5);
   set_at(A_HANDS);
   add_prop(OBJ_I_VALUE,500);
}

