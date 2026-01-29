inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include <filter_funs.h>
int did_pull;

create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   
   set_short("base of bell tower");
   set_long("This is a small room at the base of the "+
      "bell tower in the Central District of Kabal. The top of the tower " +
      "is not visible as the center of the tower is filled by a circular wall. " +
      "The walls are made of thick, interlaying blocks of granite. " +
      "A staircase spirals up around the walls and a doorway to the " +
      "west and east leads out of the tower."+
      " For some reason, the whole floor is filled with "+
      "fine-grained sand and some coiled up ropes that hangs from the tower above you.\n");
   
   hear_bell = 4; /*deafening: inside bell tower*/
   
   add_exit(CENTRAL(tower/sleep_room),"west",0,-1,-1);
   add_exit(CENTRAL(citadel/bell1),"east",0,-1,-1);
   add_exit(CENTRAL(tower/stair1),"up","@@start_up@@",3,-1);
   
   add_item(({"stair","stairs","staircase","spiral staircase"}),
      BS("They are made of hard stone and curve up, out of sight, " +
         "around the walls of the tower.\n"));
   add_item(({"circular wall","wall","walls"}), BS(
         "The walls are made of thick, interlaying blocks of granite. " +
         "There is an outter and inner wall. " +
         "\n"));
   add_item("outer wall",BS(
         "This is the outside wall of the tower. It is made of " +
         "thick, interlaying blocks of granite.\n"));
   add_item("inner wall",BS(
         "The inner wall is circular and fills the center of the tower. " +
         "It is  made of thick, interlaying blocks of granite.\n"));
   
   add_item(({"rope","ropes"}),"Several ropes lies coiled "+
      "up on the floor here. Some of them seems to be hanging from "+
      "something far up in the tower. Maybe its the ropes used to control "+
      "the bell?\n");
   add_item("sand","The sand is of a fine grain, and its spread evenly "+
      "out on the floor like a soft carpet.\n");
   set_alarm(0.0,0.0,"reset_room");
} 

init()
{
   ::init();
   add_action("pull_rope","pull");
}

reset_room()
{
   did_pull = 0;
}

int
pull_rope(string str)
{
   object hvem;
   hvem = TP;
   notify_fail("Pull what?\n");
   if (!str || str!="rope") return 0;
   TP->catch_msg("You pull a rope with all your might.\n");
   say(QCTNAME(TP)+" pulls a rope with all "+ TP->query_possessive()+" might!\n");
   set_alarm(1.0,0.0,"test_pull",hvem);
   return 1;
}

test_pull(object who)
{
   int str;
   str = who->query_base_stat(SS_STR);
   if (str<50 || did_pull)
      {
      who->catch_msg("Nothing happens...all you managed to do was to "+
         "hurt your hands on the rope.\n");
      say(QCTNAME(who)+" peers at the rope that "+
         who->query_pronoun()+" could not move an "+
         "inch.\n");
      return;
   }
   else
      {
      did_pull = 1;
      who->catch_msg("You suddenly stand with the rope in your hands, "+
         "with more coming down from the tower each second.\n");
      say(QCTNAME(who)+" managed to pull the rope down, and new lenghts "+
         "of rope starts to coil up on the floor.\n");
      set_alarm(2.0,0.0,"first_fall",who);
   }
}

first_fall(object who)
{
   tell_room(TO,"You think you can hear something falling...\n");
   set_alarm(3.0,0.0,"second_falling",who);
}

second_falling(object who)
{
   tell_room(TO,"Now you are sure something heavy is falling "+
      "towards you!\n");
   set_alarm(2.0,0.0,"final_fall",who);
}

final_fall(object ob)
{
   int dex;
   object who;
   tell_room(TO,"THUMP!!!\n");
   if (who = present(ob));
   {
      dex = who->query_base_stat(SS_DEX);
      switch (dex)
      {
         case 0..50:
         who->heal_hp(-200);
         who->catch_msg("A huge sack filled with sand "+
            "crashes into you from above. It knocks you out cold.\n");
         if (who->query_hp()<=0) who->do_die(TO);
         say("Suddenly a huge sack of sand crashes into "+QCTNAME(who)+
            ", knocking "+who->query_objective()+" cold.\n");
         break;
         case 51..90:
         who->catch_msg("A huge sack of sand crashes into your shoulder as you "+
            "managed to move your head away in the fraction of a "+
            "second before it hit you.\n");
         say("A huge sack of sand crashes into "+QCTNAME(who)+
            ". "+who->query_pronoun()+" managed to move "+
            "away "+who->query_possessive()+
            " in time.\n");
         who->heal_hp(-100);
         if (who->query_hp()<=0) who->do_die(TO);
         break;
         case 91..110:
         who->catch_msg("In time you managed to move away from the "+
            "huge sack, but it "+
            "hits your foot hard.\n");
         say(QCTNAME(who)+" managed to move away in time as a huge sack of "+
            "sand falls down. It hits "+who->query_possessive()+
            " foot though.\n");
         who->heal_hp(-50);
         if (who->query_hp()<=0) who->do_die(TO);
         break;
         default:
         tell_room(TO,"A huge sack of sand hits the ground hard!\n");
         break;
       }
   }
   tell_room(TO,"The sack explodes when its fall ended so adruptly. "+
      "Sand spreads out like a silvery cloud in the room, but "+
      "soon settles slowly on the floor like a carpet.\n");
   set_alarm(1.0,0.0,"make_cackle");
   return;
}

make_cackle()
{
   tell_room(TO,"Someone cackles crazily far up in "+
      "the tower.\n");
}



start_up()
{
   TP->catch_msg("You start to walk up the steep stairway.\n");
   say(QCTNAME(TP)+" starts to walk up the steep stairway.\n");
}
