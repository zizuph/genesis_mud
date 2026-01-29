inherit "/std/leftover";
#include "/d/Kalad/defs.h"
object ghoulheart;
/* by Antharanos */
void
create_leftover()
{
   set_name("heart");
   add_name("Kabal's heart");
   add_name("heart of Kabal");
   set_long("This is the heart of Kabal himself.\n");
   set_decay_time(200);
   set_amount(2000);
   add_prop("_korat_heart_type",2);
}
