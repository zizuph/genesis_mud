/* 
 * /d/Kalad/common/wild/pass/falling.c
 * Purpose    : This is the room players are moved to when they fall. They take damage
 * Located    : Caravan route
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

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
   set_short("Falling");
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
   
   set_alarm(3.0,0.0,"halfway",ob);
}

void
halfway(object ob)
{
   if (!ob || !present(ob, this_object()))
      return;
   
   tell_room("/d/Kalad/common/wild/pass/shaft", "You hear a loud noise and suddenly you see ");
   
   if (living(ob))
      {
      tell_object(ob, "The ground is getting closer.\n");
      tell_room("/d/Kalad/common/wild/pass/shaft", QTNAME(ob));
   }
   else
      tell_room("/d/Kalad/common/wild/pass/shaft", LANG_ASHORT(ob));
   
   tell_room("/d/Kalad/common/wild/pass/shaft", " fall through the shaft and "+
      "continue down.\n");
   
   set_alarm(3.0,0.0,"land",ob);
}

void
land(object ob)
{
   if (!ob || !present(ob, this_object()))
      return;
   
   tell_room("/d/Kalad/common/wild/pass/w6", "You hear a horrible noise from above, "+
      "suddenly you see ");
   
   if (living(ob))
      {
      tell_room("/d/Kalad/common/wild/pass/w6", QTNAME(this_player()) + " slam into the ground.\n");
      
      ob->move("/d/Kalad/common/wild/pass/w6");
      
      tell_object(ob, "You slam into the ground with terrible force!\n");
      ob->heal_hp(-500);
      
      if (ob->query_hp() < 1)
         ob->do_die(this_object());
   }
   else
      {
      tell_room("/d/Kalad/common/wild/pass/w6", LANG_ASHORT(ob) + " fall down.\n");
      ob->move("/d/Kalad/common/wild/pass/w6");
   }
}

