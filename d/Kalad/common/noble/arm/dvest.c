inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* Black studded leather armour, by Sarr */
void
create_armour()
{
    ::create_armour();
    set_name("vest");
    set_adj("studded");
    add_adj("black");
    add_adj("leather");
    set_short("black studded leather vest");
    set_long(
    "This black leather armour is covered with silver studs. It is light,\n"+
    "but looks like it can protect well.\n");
   set_ac(25);
   set_at(A_TORSO);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,700);
   add_prop(OBJ_I_VALUE,500);
}

