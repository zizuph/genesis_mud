/*
 *  Pit trap base room by Igneous
 */
inherit "/d/Shire/std/room.c";

#include <tasks.h>
#include <ss_types.h>
#include "/d/Shire/common/defs.h"

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   
   if (!living(ob))
      return;
   //  pass is cloned to people who fall in the trap
   if (present("pass",ob))
      {
      ob->catch_msg("You scream loudly as you fall deep into a pit!\n");
      say(QCTNAME(ob)+" arrives screaming, as "+HE_SHE(ob)+" has fallen "+
         "into this pit with you.\n");
      //  They fell in so we hurt them now
      if (ob->query_hp() - 200 < 0)
         ob->heal_hp(-(ob->query_hp() / 3));  //  We don't want to kill them
      else 
         ob->heal_hp(-200);
      return;
   }
   ob->catch_msg("You climb carefully down into the pit.\n");
   say(QCTNAME(ob)+" carefully climbs down into the pit with you.\n");
}

public void
leave_inv(object ob,object to)
{
   ::leave_inv(ob,to);
   
   if (!living(ob))
      return;
   ob->catch_msg("You carefully climb your way out of the deep pit.\n");
   say(QCTNAME(ob)+" carefully makes "+HIS_HER(ob)+" way out of the "+
      "deep pit.\n");
}

void
init()
{
   ::init();
   
   add_action("climb","climb");
}

int
climb(string str)
{
   if (!str || str != "up" && str != "out")
      {
      notify_fail("Climb where?\n");
      return 0;
   }
   if (TP->query_fatigue() < 30)
      {
      write("You are to tired to climb out of the pit.\n");
      return 1;
   }
   TP->add_fatigue(-15);
   if (TP->resolve_task(TASK_ROUTINE, ({SS_CLIMB,TS_DEX})) >= 0)
   {
      //  success message is in the leave_inv function.
      if (TP->query_prop("trap_last_room"))
         TP->move_living("M",TP->query_prop("trap_last_room"));
      else
         TP->move_living("M",TP->query_prop(LIVE_O_LAST_ROOM));
      return 1;
   }
   write("You try to climb out of the pit but, slip and fall!\n");
   say(QCTNAME(TP)+" tries to climb out of the trap, but fails.\n");
   return 1;
}

int
query_is_pit_room()
{
   return 1;
}
