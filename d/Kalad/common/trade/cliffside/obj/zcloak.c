inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

create_armour()
{
   ::create_armour();
   set_name("cloak");
   set_short("silk cloak");
   set_long("A silken cloak that has a hood and reaches to the feet. "+
      "It is very light and seems to shimmer as if possessing "+
      "some hidden power.\n");
   set_adj(({"silk"}));
   set_default_armour(2, A_ROBE | A_HEAD, 0, 0);
}
