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
   set_remove_time(20);
   set_stop_verb("slutt");
   set_fail_message("You can't do that! Right now you are too "+
      "busy with getting loose.\n");
   set_stop_message("You managed to tear yourself out of the web.\n");
   set_alarm(2.0,3.0,"mine_msg");
}

mine_msg()
{
   string msg;
   E(TO)->catch_msg("You fight to get loose from the cobweb.\n");
   tell_room(E(E(TO)),QCTNAME(E(TO))+" fights to get out of the cobweb.\n",E(TO));
}
