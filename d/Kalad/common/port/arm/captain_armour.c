inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("armour");
    set_adj("over-sized");
    add_adj("leather");
    set_long("An extremely large suit of leather armour. It has been "+
      "crafted to fit the immense girth of an overweight person. Several layers "+
      "of leather have been added to the otherwise standard armour, giving "+
      "added protection to the wearer.\n");
    set_ac(15);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,500);
    add_prop(OBJ_I_VOLUME,10000);
    add_prop(OBJ_I_WEIGHT,10000);
}
