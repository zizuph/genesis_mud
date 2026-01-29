inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

create_armour()
{
   ::create_armour();
   set_name("boots");
   set_short("supple leather boots");
   set_long("These boots are made from a hide you've never seen before. "+
      "They are as tough as adamantine, yet as supple as the "+
      "finest deerskin.\n");
   add_adj(({"leather"}));
   set_default_armour(20,A_FEET, 0, 0);
}
