/*
 * Made by Korat
 * may 1996
 *
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
   ::create_room();
   set_short("dwarven Citadel");
   set_long("You are inside an ancient citadel, long abandoned "+
      "by their masters and makers, the deep dwarves. "+
      "Even though the citadel has clear marks of decay from "+
      "the centuries of abandonment, the masonry is of such "+
      "quality that you still have problems finding the "+
      "cracks inbetween the stoneblocks. Along one of the walls "+
      "you see some rubble containing mostly old sacks and chests. "+
      "The hallway seems to go downwards to the east, and branches "+
      "south, southwest and southeast into what looks like more rooms hidden "+
      "in a veil of darkness.\n");

   add_item(({"rubble","sacks","chests","chest","sack"}),
      "They are all smashed up with the locks on what once was "+
      "some excellent chests, almost torn off its hinges. The sacks "+
      "looks once to have contained different sorts of grains. You "+
      "understand that these must be the leftovers of several raids "+
      "against caravans. There is nothing left for you to loot though.\n");
   add_item(({"cobweb","web","silky network","silky web"}),
      "They are woven, silky networks spun by spiders through "+
      "time. All of them look to be abandoned by their creators, "+
      "much like the citadel itself; left alone to slowly be "+
      "grinned down by the sand carried along with the wind.\n");
   add_item(({"wall","walls","ceiling","roof"}),
      "Both the walls and the ceiling looks to be made by "+
      "brilliant craftsmen. This citadel was made to last ... "+
      "for thousands of years.\n");
   add_item("floor","The floor is covered with fine-grained, white "+
      "sand that must have been carried in here with the wind from the "+
      "great Kaladian waste.\n");
   add_item("citadel","The citadel you are inside is a masterpiece "+
      "of construction. Time has managed to mark it with signs of age, "+
      "but that only mystifies it more than its centuries of abandonment "+
      "manages to do alone.\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description");
   INSIDE;

   add_exit(CPASS(citadel/x17),"west",0,-1);
   add_exit(CPASS(citadel/level3/c2),"southwest","@@arch",-1);
   add_exit(CPASS(citadel/level3/c4),"southeast","@@arch",-1);
   add_exit(CPASS(citadel/level3/c3),"south","@@arch",-1);
}

/* give a feeling of passing through an arc */
void
arch()
{
   TP->catch_msg("You walk through a low passage that arches around you.\n");
   return 0;
}

/* returns a random darkroom description */
dark_description()
{
   string desc;
   switch (random(5))
   {
      case 0:
         desc = "You find yourself inside utter darkness.\n";
         break;
      case 1:
         desc = "A weak and chilling wind is all breaks the darkness.\n";
         break;
      case 2:
         desc = "You think you hear some sounds in front of you, but "+
                "without vision you cannot know what it comes from.\n";
         break;
      case 3:
         desc = "A dark room that envelopes you like a cloak of death.\n";
         break;
      case 4:
         desc = "You touch the wall to make sure you walk in the right "+
                "direction.\n";
         break;
      default: break;
   }
   
   return desc;
}
