inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define NO_OF_DIAMONDS 5
int diamond;
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_S_DARK_LONG,"A dark and chilly place.\n");
   set_short("A large oval chamber");
   set_long("Here, the tunnel has finally reached an end. A large oval "+
      "chamber lies before you, its width nearly reaching one hundred feet. "+
      "The stone ground here has been smoothed down and has in parts, been "+
      "covered with animal skins. The walls of the chamber have been "+
      "similarly smoothed down, though instead of skins, they are decorated "+
      "with the garish heads of the owners of the skins you now tread upon. "+
      "Overhead, the ceiling has been left in its pristine state, riddled "+
      "with numerous pits and scars save for one aspect. Numerous diamonds "+
      "have been embedded in its surface, casting a strange, dim light onto "+
      "your surroundings.\n");
   add_item(({"large oval chamber","large chamber","oval chamber","chamber"}),
      "A large cavity within the ground, its where you are right now.\n");
   add_item(({"stone ground","ground"}),
      "The floor of the chamber has been polished to an almost mirror-like "+
      "smoothness, your reflection looking back at you from the black rock. "+
      "In various areas of the chamber lie animal skins.\n");
   add_item(({"black rock","rock"}),
      "The dark material that this chamber is composed of.\n");
   add_item(({"animal skins","animal skin","skins","skin"}),
      "The hairless hides of numerous animals, some can be identified as "+
      "belonging to lions, lizards, rabbits and gazelle. The rest prove too "+
      "difficult to ascertain their identities.\n");
   add_item(({"walls","wall"}),
      "Smooth and mirror-like they reflect your image clearly. Positioned "+
      "within niches in its surface are the numerous heads of animals, as well "+
      "as several other beings.\n");
   add_item(({"niches","niche"}),
      "Holes that have been carved into the side of the walls, they are "+
      "almost entirely filled with the severed heads of many animals. "+
      "However, there does appear to be a few niches that are presently unoccupied.\n");
   add_item(({"ceiling"}),
      "The rough and unpolished ceiling of the chamber is astounding in one "+
      "thing only, the dozens of diamonds that riddle its pockmarked surface.\n");
   add_item(({"diamonds","diamond"}),
      "Sparkling with a strange white light of their own, their radiant "+
      "crystal beauty leaves you gasping with wonderment.\n");
   add_exit(CPASS(desert/rock/l5),"north");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   diamond = NO_OF_DIAMONDS;
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/lamia_queen));
      ob1 -> move_living("M",TO);
      tell_room(TO,"A noble lamia comes into view.\n");
   }
}
void
init()
{
   ::init();
   add_action("do_pick", "pick");
}
int
do_pick(string str)
{
   if(!str || str != "diamond")
      {
      notify_fail("You can't pick '" + str + "'.\n");
      return 0;
   }
   if(!diamond)
      {
      write("There aren't any diamonds within your reach.\n");
      return 1;
   }
   write("You pick a diamond from the ceiling.\n");
   say(QCTNAME(TP) + " manages to pick a diamond from the ceiling.\n");
   diamond--;
   clone_object("/d/Kalad/common/wild/pass/obj/diamond")->move(TP);
   return 1;
}
