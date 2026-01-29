inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("long");
    add_adj("flowing");
    set_long("The cloak is so long it could as well be called a cape, for it "+
      "is over five feet in length. Although made of a light material, the "+
      "substance looks particularly tough. It seems to flutter about with "+
      "the slightest of movements.\n");
    set_ac(4);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,360);
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_WEIGHT,1500);
}
