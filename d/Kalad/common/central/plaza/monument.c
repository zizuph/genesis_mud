/* On top of the monument */
/* Made by Korat */
/* with good help from Napture */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <filter_funs.h>
#include <language.h>
#define DOWN_ROOM "/d/Kalad/common/central/plaza/sq_mon"
object *ob;
object ob1;
object ob2;
object ob3;


create_room()
{
   ::create_room();
   set_short("On the monument");
   
   if (DAY)
      set_long("You find yourself on the top of the monument, clinging to the head "+
      "of the Lord. From here you have a fantastic view of the plaza and its surroundings! "+
      "To the north you watch the flags on top of the gladiator arena sway in the wind, "+
      "and a bit more west the bronze bell in the Citadel's tower shimmers in the sun. "+
      "When you turn your head southwards, you watch amazed at the sparkling blue sea. "+
      "You feel that you could stay here for ages, lost in thoughts and just "+
      "marvel at the sight, hadn't it been for those pigeons that keeps flapping "+
      "their wings into your face.\n");
   
   else
      
   set_long("Its night in Kalad. You can't see much from here except the head of the "+
      "Lord that you are clinging onto. He looks really ugly, and you start to wonder "+
      "whether the statue does him justice or not.\n");
   
   add_exit(CENTRAL(plaza/sq_mon),"down",0,3);
   add_item(({"lord","head"}),"The head is made in bronze, and is dirtied "+
      "down in excrement from pigeons.\n");
   set_alarm(1.0,0.0,"reset_room");
}

void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/pigeon_quest");
      ob1 -> move_living("M", TO);
      tell_room(TO, "A pigeon comes flying in and lands on the bronze head.\n");
   }
   if(!ob2)
      {
      ob2  = clone_object("/d/Kalad/common/central/npc/pigeon");
      ob2 -> move_living("M", TO);
      tell_room(TO, "Another pigeon comes flying down, flapping its "+
         "wings into your face as it lands.\n");
   }
   if(!ob3)
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/pigeon");
      ob3 -> move_living("M", TO);
      tell_room(TO, "A new pigeon crashlands on the bronze head.\n");
   }
}
