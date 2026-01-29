inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
   set_soft_amount(150);
   set_alco_amount(10);
   set_name("brew");
   set_adj("imported");
   set_short("imported brew");
   set_pshort("imported brews");
   set_long("This golden ale was imported most likely from the " +
      "islands surrounding the Bloodsea of Istar. This drink is " +
      "a favourite of the sailors of this region. \n");
   add_prop(OBJ_I_WEIGHT, 150);
   add_prop(OBJ_I_VOLUME, 150);
}
