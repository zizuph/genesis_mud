inherit "/std/paralyze";
#include "/d/Kalad/defs.h"
/* by korat */
void
create_paralyze()
{
   set_name("stun");
   set_long("A paralyze.\n");
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_INVIS, 99);
   add_prop(OBJ_I_NO_DROP,1);
   set_remove_time(10);
   set_stop_verb("slutt");
   set_fail_message("You are stunned!\n");
   set_stop_message("You feel yourself able to move again.\n");
   set_alarm(1.0, 0.0, "set_time");
}

void
set_time()
{
   int time;
   time = random(50)+20;
   if (time<10) time = 10;
   TO->set_remove_time(time);
}
