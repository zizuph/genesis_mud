inherit "/std/leftover";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_leftover()
{
   set_name("heart");
   add_name("ghoul heart");
   add_name("heart of the ghoul");
   set_long("This is the decaying remains of a ghouls' heart.\n");
   set_decay_time(60);
   set_amount(2000);
   add_prop("_korat_heart_type",1);
}
