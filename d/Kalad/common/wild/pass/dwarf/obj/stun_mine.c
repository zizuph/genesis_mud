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
   set_remove_time(30);
   set_stop_verb("stop");
   set_fail_message("You can't do that! You are too busy with mining. "+
      "To stop mining, write 'stop'.\n");
   set_stop_message("You stop mining for coal.\n");
   set_stop_fun("stop_mining");
   set_alarm(2.0,3.0,"mine_msg");
}

mine_msg()
{
   string msg;
   switch(random(6))
   {
      case 0: msg="You hit the rock hard with your pickaxe.\n"; break;
      case 1: msg="The pickaxe bounches back as you hit pure rock.\n"; break;
      case 2: msg="You hit loose some coal.\n"; break;
      case 3: msg="The pickaxe sinks deeply into the coal-vein.\n"; break;
      case 4: msg="A larger piece of coal rolls down in front of "+
         "your feet as the pickaxe hits hard into the coal-vein.\n"; break;
      case 5: msg="A shower of coal-dust makes you cough loudly.\n"; break;
      default: break;
   }
   E(TO)->catch_msg(msg);
   tell_room(E(E(TO)),QCTNAME(E(TO))+" mines for coal.\n",E(TO));
}
