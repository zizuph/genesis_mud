/*
A house for a simple family along the circle street
by Korat
mars 1995
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

object ob1;
object ob2;


void
create_room()
{
   ::create_room();
   hear_bell = 2;
   
   add_prop(ROOM_I_INSIDE, 1);
   
   set_short("A small house along the circle street");
   set_long(
      "This is the home of a family in the famous city of Kabal. "+
      "Along the walls you see a few small paintings, some furniture "+
      "and different decorative objects; A typical home. You see "+
      "an exit from where the smell of food wafts into your nose.\n");
   
   add_prop(ROOM_NO_TIME_DESC, 1);
   
   add_exit(CENTRAL(circle/s11),"out",0,-1,-1);
   add_exit(CENTRAL(circle/kitchen2),"southwest",0,-1,-1);
   
   add_item(({"furniture","chair","chairs","paintings"}),
      "The furniture, along with the paintings shows the sign "+
      "of a standard family that has managed to rise above "+
      "the poor conditions a lot of other individuals tend to "+
      "live in here in Kabal. Still, there is a long way to "+
      "the living conditions of the higher officials working "+
      "in the offices at the plaza. This must be the home of "+
      "a plain employee in the offices, working fourteen hours "+
      "each day.\n");
   
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/mother");
      ob1 -> arm_me();
      ob1 -> move_living("xxx",TO);
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/child");
      ob2 -> move_living("xxx",TO);
      ob1 -> team_join(ob2);
   }
}

init()
{
   ::init();
   add_action("play","play");
}


play(string str)
{
   notify_fail("Play with whom?\n");
   if (!str) return 0;
   if (str=="with child" || str=="with young human")
      {
      if (ob2)
         {
         write("You sit down and play some with the child.\n");
         say(QCTNAME(TP)+" sits down on the floor and plays some "+
            "with the child.\n");
         ob2->command("emote climbs up on a "+TP->query_nonmet_name()+" back.");
         set_alarm(2.0,0.0,"play1",TP);
         set_alarm(5.0,0.0,"play2",TP);
         set_alarm(8.0,0.0,"play3",TP);
         set_alarm(9.0,0.0,"play4",TP);
         return 1;
       }
   }
   return 0;
}

play1(object who)
{
   ob2->command("emote sits on a "+who->query_nonmet_name()+" shoudlers.");
   ob2->command("emote cackles with a happy glee.");
   ob2->command("shout Horse! Ruuuunnnnn....");
}
play2(object who)
{
   write("You run around in the room, making horse-noises.\n");
   say(QCTNAME(who)+" runs around in the room, making horse-noises.\n");
   ob2->command("emote kicks a "+who->query_nonmet_name()+
      " in the kidneys like spurring a horse on.");
   command("emote laughs happily.");
   write("Ouch! That hurts...\n");
}
play3(object who)
{
   if (random(2)==0)
      {
      ob2->command("emote grips around a "+who->query_nonmet_name()+" head "+
         "with his small hands.");
      write("The hands of the child blocks your vision!\n");
      say("The hands of the child blocks the sight of "+QTNAME(who)+"!\n");
      write("You crash into something!\n");
      say(QCTNAME(who)+" crashes into the wall!\n");
   }
}
play4(object who)
{
   write("You put the child down.\n");
   say(QCTNAME(who)+" puts the child down.\n");
   ob2->command("cry");
}

