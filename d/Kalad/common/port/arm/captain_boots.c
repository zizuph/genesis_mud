inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("boots");
    add_name("large pair");
    add_name("pair");
    set_adj("extremely");
    add_adj("large");
    set_short("extremely large pair of boots");
    set_pshort("extremely large pairs of boots");
    set_long("A pair of leather boots so large that it would seem they belonged "+
      "to a hill giant! Whoever owns these boots must use them often, "+
      "for the leather is worn and cracked, and smells as if they were "+
      "soaked in sea water.\n");
    set_ac(12);
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE,420);
    add_prop(OBJ_I_VOLUME,3600);
    add_prop(OBJ_I_WEIGHT,3600);
}
