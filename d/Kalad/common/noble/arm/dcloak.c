inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* Black studded leather armour, by Sarr */
void
create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("hooded");
    add_adj("black");
    set_short("black hooded cloak");
    set_long("A dark cloak with a hood.\n");
   set_ac(8);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,500);
}

