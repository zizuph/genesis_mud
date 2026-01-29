inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("armour");
    set_adj("leather");
    set_long("A typical suit of leather armour, it is designed to provide "+
      "minimal protection to the wearer's torso. Upon the front of this "+
      "armour is an image of a dark sun.\n");
    set_ac(15);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,250);
    add_prop(OBJ_I_VOLUME,1800);
    add_prop(OBJ_I_WEIGHT,1800);
}
