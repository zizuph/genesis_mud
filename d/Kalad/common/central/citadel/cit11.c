/* 
Citadel, Podium room.
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   hear_bell = 2;
   set_short("Citadel, podium");
   set_long("You gasp when you watch the size of this room. A large "+
      "vaulting dome makes this plaze into a huge and impressive place "+
      "that almost takes your breath away. Many statues lines up along "+
      "the walls, and you see several torches burning brightly between "+
      "them, mounted in long stands. This must be the place where the Lord "+
      "meets selections of his people en masse, and it must be on the large "+
      "throne he sits while giving audiences to the few lucky or maybe "+
      "unlucky, selected ones. If you walk east, south or to the southeast, "+
      "you will walk towards other parts of this huge dome.\n");
   
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
   
   add_item ("podium","The podium's edge arches from the east to the "+
      "south, making this place higher than the rest of the dome's marble-"+
      "floor. It is very hard to avoid noticing the throne that stands in "+
      "front of a large curtain in the northwestern part of the podium.\n");
   
   add_item ("throne","Covered in red velvet and decorated with intricate "+
      "gold-thread patterns, the throne seems to blend into the red curtain "+
      "behind it. Behind it you see two large candle-stands that casts of "+
      "a yellow light that mingles into the red texture, giving it a light "+
      "red colour in the light and a darker in its shadows; it reminds you "+
      "of fresh blood.\n");
   
   add_item ("curtain","It is made of a red texture, with several thin "+
      "golden lines spreading out from the centre, just like sunbeams.\n");
   
   add_exit(CENTRAL(citadel/cit10),"south",0,-1,-1);
   add_exit(CENTRAL(citadel/cit9),"southeast",0,-1,-1);
   add_exit(CENTRAL(citadel/cit12),"east",0,-1,-1);
   
   set_alarm(0.0,0.0,"reset_room");
}
void
init()
{
   ::init();
   add_action("enter","enter");
}

int
enter(string str)
{
   notify_fail("Enter what?\n");
   if (!str || str!="curtain")
      return 0;
   write ("You make sure nobody sees you, then you enter the curtain swiftly. "+
      "You see a hallway lead westwards, so you follow it. Suddenly it turns south.\n");
   say("Suddenly you notice that "+ QCTNAME(TP) +" is not here anymore!\n");
   tell_room(CENTRAL(citadel/cit19),QCTNAME(TP)+" arrives from the north.\n");
   TP->move_living("M",CENTRAL(citadel/cit19),1);
   return 1;
}

void
reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_guard");
      ob1 -> arm_me();
      ob1 -> move_living("A guard arrives and takes his post.", this_object());
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/cit_guard");
      ob2 -> arm_me();
      ob2 -> move_living("A guard arrives and takes his post.", this_object());
   }
   
   return;
}
