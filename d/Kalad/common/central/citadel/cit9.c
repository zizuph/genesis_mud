/* 
Citadel, Dome room.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

object ob1;

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
      "meets selections of his people en masse. To the northwest you see a podium "+
      "with a huge throne in the centre. If you walk southeast you will "+
      "move towards the exit of the Citadel, while the other exits leads to "+
      "other parts of this huge dome.\n");
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

   add_exit(CENTRAL(citadel/cit7),"south",0,-1,-1);
   add_exit(CENTRAL(citadel/cit6),"southeast",0,-1,-1);
   add_exit(CENTRAL(citadel/cit12),"north",0,-1,-1);
   add_exit(CENTRAL(citadel/cit8),"east",0,-1,-1);
   add_exit(CENTRAL(citadel/cit10),"west",0,-1,-1);
   add_exit(CENTRAL(citadel/cit11),"northwest",0,-1,-1);

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
   return;
}
