/*     Created by:      Korat 100195
 *     purpose:		Barracks
 *     Location:         
 *     Modified:        Toby, 970918 (fixed typos)
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"

int guards_present;
int alarmday;
int alarmnight;
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Barracks");
   if (DAY)
      set_long("Along the sides of the room you see several wooden beds "+
      "that looks to have been recently occupied. In the middle of the "+
      "room there is a table with some chairs around it. Some guards "+
      "sit there and play cards. You see another room north of you.\n");
   else
      set_long("Along the sides of the room you see several wooden beds "+
      "with some guards sleeping in them. In the middle of the room "+
      "there is a table with some chairs around it. The table is "+
      "littered with cards, showing signs of a game having "+
      "recently been played.\n");
   
   add_exit(CENTRAL(barracks/barracks2),"north",0,-1,-1);
   add_exit(CENTRAL(plaza/sq_west),"southeast","@@move_out",0,1);
   
   add_item (({"table"}),"A simple wooden table, ruined by several "+
      "carvings and food-stains. You see several cards scattered "+
      "on it.\n");
   add_item (({"cards","card"}),"The cards are normal "+
      "playing cards; hopefully all the 52 of them are there.\n");
   add_item (({"bed","beds"}),"The wooden beds are mounted onto the "+
      "walls. they are small and probably not very comfortable.\n");
   add_item (({"guard","guards"}),"@@exa_guards");
   add_item (({"chair","chairs"}),"A simple construction used to "+
      "relax in when one eats or play cards...\n");   
   
   if (DAY)
      {
      if (alarmnight) remove_alarm(alarmnight);
      alarmday = set_alarm(20.0,60.0,"card_playing");
      alarmnight = 0;
   }
   else
      {
      if (alarmday) remove_alarm(alarmday);
      alarmday = 0;
      alarmnight = set_alarm(20.0,60.0,"snore_loud");
   }
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   guards_present = 0;
   alarmday = 0;
   alarmnight = 0;
}

card_playing()
{
   tell_room (TO,"The guards starts to argue over the game..."+
      "Seems like one of them tried to cheat, again!\n");
}

snore_loud()
{
   tell_room (TO,"You hear some loud snoring from one "+
      "of the beds.\n");
}
exa_guards()
{
   if(TP->query_base_stat(SS_DIS) < 50)
      {
      write ("You don't dare to disturb the guards!\n");
      say(QCTNAME(TP) + " tries to force himself to disturb "+
         "the guards, but lacks the courage.\n");
      return 1;
   }
   if (DAY)
      say (QCTNAME(TP) + " bends over a guards shoulder, examining his "+
      "cards...They do not look very pleased for this interuption of "+
      "their game. Not at ALL!!\n");
   else
      say (QCTNAME(TP) + " walks up to the beds and starts to examine "+
      "them...They do not look very pleased for this interruption of "+
      "their sleep. Not at ALL!!\n");
   if(guards_present)
      return "The guards decide to ignore you totally.\n";
   guards_present = 1;
   set_alarm(2.0,0.0,"wake_guards");
   return "The guards do not look pleased at all, being "+
   "disturbed by you!\n";
}

wake_guards()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/militia_barracks");
      ob1 -> arm_me();
      ob1 -> move_living("M", this_object());
      tell_room(TO,"The guard stands up, visibly angry.\n");
      ob1 -> command("kill "+ QTNAME(TP));
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/militia_barracks");
      ob2 -> arm_me();
      ob2 -> move_living("M", this_object());
      tell_room(TO,"The guard stands up, visibly angry.\n");
   }
   if (!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/militia_barracks");
      ob3 -> arm_me();
      ob3 -> move_living("M", this_object());
      tell_room(TO,"The guard stands up, visibly angry.\n");
   }
   if (!objectp(ob4))
      {
      ob4 = clone_object("/d/Kalad/common/central/npc/militia_barracks");
      ob4 -> arm_me();
      ob4 -> move_living("M", this_object());
      tell_room(TO,"The guard stands up, visibly angry.\n");
   }
   if (!objectp(ob5))
      {
      ob5 = clone_object("/d/Kalad/common/central/npc/militia_barracks");
      ob5 -> arm_me();
      ob5 -> move_living("M", this_object());
      tell_room(TO,"The guard stands up, visibly angry.\n");
   }
   ob1->team_join(ob2);
   ob1->team_join(ob3);
   ob1->team_join(ob4);
   ob1->team_join(ob5);
   return;
}

move_out()
{
   TP->catch_msg(
      "You walk through the doorway, leaving the barracks and the smell "+
      "of sweat behind you.\n");
   return 0;
   
}
