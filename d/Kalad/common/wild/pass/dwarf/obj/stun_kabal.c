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
   set_fail_message("You are paralyzed!!\n");
   set_stop_message("You feel your own blood start to flow freely again.\n");
   set_alarm(1.0, 0.0, "set_time");
}

void
set_time()
{
   int time;
   time = 130-(E(TO)->query_base_stat(SS_DIS));
   if (time<10) time = 10;
   if (time > 50) time = 50;
   TO->set_remove_time(time);
   write("Time of plex is: "+time+"\n");
}
