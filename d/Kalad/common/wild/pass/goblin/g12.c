inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GG "/d/Kalad/common/wild/pass/npc/gk_guard"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("The goblin throne room");
   set_long("You are within a large circular rock chamber, with its domed "+
      "ceiling hanging above you like a predatory bird. This place seems "+
      "to be the source of the putrid odor common in these caves, for "+
      "it veritably smells like a giant cesspit here, and not surpisingly, "+
      "large pools of murky liquid cover the floor. Three tunnels branch "+
      "from this central chamber, one to the north and two similar ones "+
      "heading east and southeast.\n");
   add_item(({"large circular chamber","large chamber","circular chamber","rock chamber","central chamber","chamber"}),
      "The area in which you are currently in.\n");
   add_item(({"domed ceiling","ceiling"}),"A roughly shaped and hewn "+
      "ceiling for this chamber.\n");
   add_item(({"large pools","pools","pool","murky liquid","liquid"}),
      "Colored a sickening shade of green with little brown chunks of "+
      "solid matter, its very presence in this room is nearly enough to "+
      "cause you to puke.\n");
   add_item(({"tunnels","tunnel"}),"Three such passages lead out of this "+
      "room, one to the north and the others to the east and southeast.\n");
   add_exit(CPASS(goblin/g15),"north",0,1,2);
   add_exit(CPASS(goblin/g13),"east",0,1,2);
   add_exit(CPASS(goblin/g10),"southeast",0,1,2);
   set_alarm(1.0,0.0,"reset_room");
   set_alarm(10.0,60.0,"eeww");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/gob_king");
      ob1 -> move_living("xxx",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(GG);
      ob2 -> move_living("xxx",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(GG);
      ob3 -> move_living("xxx",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
   }
}
eeww()
{
   tell_room(TO,"An utterly putrid smell reaches your nostrils, nearly causing you to spew the contents of your stomach.\n");
   return 1;
}
