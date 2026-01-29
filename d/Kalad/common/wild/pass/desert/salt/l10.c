inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define LIZMAN "/d/Kalad/common/wild/pass/npc/liz_man"
object ob1;
object ob2;
/* by Antharanos */
public void
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("End of passageway");
   set_long("The sound of dripping water reaches your ears, sounding "+
      "an eerie cadence within this darkened passage. The passageway ends "+
      "here at a blank stone wall. The passage continues to the east, "+
      "heading into inky darkness. "+
      "Numerous stalagmites and stalactites litter the area, making travel "+
      "somewhat dangerous.\n");
   add_item(({"darkened passage","passage","passageway","area"}),"This "+
      "underground tunnel seems to have been created through the natural "+
      "process of water erosion. As a result, numerous stalagmites and "+
      "stalactites abound in the passage.\n");
   add_item(({"inky darkness","darkness"}),"A blackness darker even than the "+
      "darkest of moonless nights.\n");
   add_item(({"stalagmites","stalactites","stalagmite","stalactite"}),
      "They are all over the passage, forcing you to watch your step, "+
      "lest you step on a stalagmite and injure yourself.\n");
   add_item(({"ceiling"}),"The ceiling of the passageway is composed "+
      "of the same stone as the rest of the tunnel. It seems to possess "+
      "an odd, almost hollow quality to it.\n");
   add_prop(OBJ_S_SEARCH_FUN,"search_ceiling");
   add_exit(CPASS(desert/salt/l9),"east","@@hurt",1,2);
   set_alarm(1.0,0.0,"reset_room");
}
hurt()
{
   if(TP->query_base_stat(SS_DEX) < 50)
      {
      write("You stepped on a stalagmite! Ouch!\n");
      say(QCTNAME(TP) + " stepped on a stalagmite!\n");
      TP->heal_hp(-100);
      return 0;
   }
   write("You manage not to step on any stalagmites.\n");
   return 0;
}
public string
search_ceiling(object me, string arg)
{
   if(arg != "ceiling")
      return "";
   if(TP->query_skill(SS_AWARENESS) < 45)
      return "";
   add_exit(CPASS(desert/salt/l3),"up",0);
   set_alarm(10.0,0.0,"remove_exit","up");
   return "After a careful search you discover a way up.\n";
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(LIZMAN);
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(LIZMAN);
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
      tell_room(TO,"A pair of lizard men emerge from the darkness.\n");
      ob1 -> team_join(ob2);
   }
}
