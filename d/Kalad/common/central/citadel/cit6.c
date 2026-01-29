/* 
Citadel, Dome room.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object ob1;
object ob2;
object ob3;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Citadel, dome");
   set_long("You gasp when you watch the size of this room. A large "+
      "vaulting dome makes this plaze into a huge and impressive place "+
      "that almost takes your breath away. Many statues lines up along "+
      "the walls, and you see several torches burning brightly between "+
      "them, mounted in long stands. This must be the place where the Lord "+
      "meets selections of his people en masse. An archway leads to the "+
      "southeast through a huge bronze gate, and to the north, west and "+
      "northwestwards the huge dome continues onwards. You notice two small "+
      "hallways leading away from the dome to the south and east.\n");

   add_item ("dome","You bend your head and look up. Its far up there, "+
      "but still you see several engravings in the vaulted roof, showing "+
      "stories of battles, sacrifices and victories. In the centre a large "+
      "shining sun can be seen. It must be an important symbol here.\n");
   add_item (({"statue","statues"}),"The statues portraits several "+
      "unknown persons, but you do recognize some of them from all "+
      "the decorations that litter this place. They must have done "+
      "some important deeds or just been a former Lord.\n");
   add_item(({"torch","torches"}),"The torches are mounted in some "+
      "large metal-stands, reaching several yards up in the air. They "+
      "cast of a yellow flickering light that are reflected in the "+
      "marble floor.\n");
   add_item(({"floor","marble","marble floor"}),"The whole floor is "+
      "made of polished marble that shines in a yellow colour, made by "+
      "the torche-light. Even though the floor seems to be polished "+
      "often, you see several cracks in it that breaks up the smooth "+
      "surface like a broken mirror.\n");

   add_exit(CENTRAL(citadel/cit7),"west",0,-1,-1);
   add_exit(CENTRAL(citadel/cit13),"east","@@turn_east@@",-1,-1);
   add_exit(CENTRAL(citadel/cit8),"north",0,-1,-1);
   add_exit(CENTRAL(citadel/cit9),"northwest",0,-1,-1);
   clone_object(CENTRAL(doors/citadel_door2))->move(TO);
   clone_object(CENTRAL(doors/citadel_belldoor2))->move(TO);
   set_alarm(0.0,0.0,"reset_room");
}

void
reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_human");
      ob1 -> arm_me();
      ob1 -> move_living("A human silently arrives.", this_object());
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/cit_guard");
      ob2 -> arm_me();
      ob2 -> move_living("A guard stands at attention.", this_object());
   }
   if (!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/cit_guard");
      ob3 -> arm_me();
      ob3 -> team_join(ob2);
      ob3 -> move_living("A guard stands at attention.", this_object());
   }

   return;
}

turn_east()
{
   write("You start to walk eastwards, and notice that the corridor "+
      "starts to bend to the north.\n\n");
}


