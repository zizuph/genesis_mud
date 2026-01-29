inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   add_prop(ROOM_I_LIGHT,0);
   set_short("The spider room");
   set_long("This dark, nearly featureless room is dominated by one "+
      "single feature, the utter profusion of spider webs and sacs that cover "+
      "and lie in every nook and cranny.\n"+
      "A darkened archway leads to the northwest.\n");
   add_item(({"spider webs","spider web","webs","web"}),
      "Thin and delicate grey strands that are strewn in intricate patterns "+
      "throughout this room.\n");
   add_item(({"sacs","sac"}),
      "Masses of webs that hold infantile spiders.\n");
   add_item(({"darkened archway","archway"}),
      "It appears to lead out of this room.\n");
   add_exit(CPASS(drow/shop/post),"northwest",0,-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/spider_trainer));
      ob1 -> move_living("M",TO);
      tell_room(TO,"Someone emerges from behind a mass of webs.\n");
   }
}
