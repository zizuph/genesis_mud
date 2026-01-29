inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <macros.h>/* Many nice macros, among them QCTNAME */
#include <stdproperties.h> /* Properties, LIVE_S_EXTRA_SHORT */
#include <language.h>/* Some nice definitions when playing with words. */
/* by Antharanos */
void
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_NO_TIME_DESC,1);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Falling through the air");
   set_long("You are falling rapidly towards the ground. You have a nice\n" +
      "view from here though....\n");
   
   add_prop(ROOM_M_NO_ATTACK, "You cannot fight while falling.\n");
   
   add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
}

void
init()
{
   ::init();
   
   add_action("quit", "quit");/* Don't let anyone quit himself out. */
}

int
quit(string str)
{
   write("No no, you can't escape this fall that easy.\n");
   return 1;
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   
   if (living(ob))
      {
      tell_object(ob, "You feel unhappy not standing on solid ground.\n");
      add_prop(LIVE_S_EXTRA_SHORT, " is also falling.\n");
   }
   
   set_alarm(3.0, 0.0, "halfway", ob);
}

void
halfway(object ob)
{
   if (!ob || !present(ob, this_object()))
      return;
   
   if (living(ob))
      {
      tell_object(ob, "The ground is getting closer.\n");
   }
   
   set_alarm(3.0, 0.0, "land", ob);
}

void
land(object ob)
{
   if (!ob || !present(ob, TO))
      return;
   
   tell_room("/d/Kalad/common/wild/pass/uc/d1","You hear a horrible noise from above, "+
      "suddenly you see ");
   
   if (living(ob))
      {
      tell_room("/d/Kalad/common/wild/pass/uc/d1",QCTNAME(TP) + " slam into the ground.\n");
      
      ob->move("/d/Kalad/common/wild/pass/uc/d1");
      
      tell_object(ob, "You slam into the ground with terrible force!\n");
      ob->command("look");
      ob->heal_hp(-250);
      
      if (ob->query_hp() < 1)
         ob->do_die(TO);
   }
   else
      {
      tell_room("/d/Kalad/common/wild/pass/uc/d1", LANG_ASHORT(ob) + " fall down.\n");
      ob->move("/d/Kalad/common/wild/pass/uc/d1");
   }
}
