inherit "/std/leftover";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_leftover()
{
   set_name("skin");
   set_adj("sapphire");
   add_adj("dragon");
   set_long("An extremely large set of scales, and judging by their "+
      "glittering blue color, they appear to have once belonged to a "+
      "sapphire dragon.\n");
   add_prop(OBJ_I_VALUE,5184);
   set_decay_time(1000);
   set_amount(100000);
}
