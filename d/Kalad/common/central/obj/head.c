inherit "/std/leftover";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_leftover()
{
   set_name("head");
   add_name("decapitated head");
   set_long("This is the decaying remains of a head. "+
      "You notice that it has been cleanely cut off from "+
      "the rest of the body, a sign of an intentional "+
      "decapitation.\n");
   set_decay_time(120);
   set_amount(5000);
}
