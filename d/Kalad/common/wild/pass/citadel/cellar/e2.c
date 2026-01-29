/*
 * Made by Korat
 * november 1996
 *
 * A cellar/dungeon beneath the dwarven citadel
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   set_short("cellar. @@tracking@@");
   set_long("You are beneath an ancient citadel, long abandoned "+
      "by their masters and makers, the Deep Dwarves. "+
      "Large boulders and stones litter this hallway, making "+
      "it hard to find any paths inbetween them. Among the stones "+
      "large cobwebs shines in the light you carry, making it "+
      "sparkle as being covered with gems. The shadows cast "+
      "by yourself dances in the light, and mingles with the "+
      "everdark areas at the edge of your view. Some rough runes "+
      "decorate one of the pillars.\n\n" +

      /* exits are visible according to the tracking skill of
       * the player
       */

      "@@tracking@@\n");

   add_item(({"cobweb","web","silky network","silky web"}),
      "They are woven, silky networks spun by spiders through "+
      "time. All of them look to be abandoned by their creators, "+
      "much like this place itself; left alone to slowly be "+
      "grinned down by the sand carried along with the wind.\n");
   add_item(({"wall","walls","ceiling","roof"}),
      "Both the walls and the ceiling looks to be cut out of the "+
      "mountain itself. Through time green moss has managed "+
      "to cover it.\n");
   add_item("floor","The floor is covered with fine-grained, white "+
      "sand that must have been carried in here with the wind from the "+
      "great Kaladian waste.\n");
   add_item(({"boulder","boulders","rock","rocks"}),
      "They litter the area, making it very hard to see any path "+
      "that you can follow. One of them has some runes carved "+
      "into it.\n");
   add_item(({"path","paths"}), "You have a hard time to see "+
      "any paths here. @@tracking@@\n");
   add_item(({"rune","runes"}),"The runes are hard to dechiper, "+
      "but after a while you believe they simply communicate "+
      "a warning. What it is supposed to warn you about is not "+
      "mentioned in them.\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description@@\n");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_exit(CPASS(citadel/cellar/e1),"southeast","@@up",3,1);
   add_exit(CPASS(citadel/cellar/e3),"down","@@down",3,1);
}

/* give a feeling of walking on a path */
int
up()
{
   TP->catch_msg("You follow a twisting path that takes you southeastwards.\n");
   return 0;
}

/* give a feeling of going downwards */
int
down()
{
   TP->catch_msg("As you walk you notice that you decend "+
      "downwards. The roots of the mountain are getting closer...\n");
   return 0;
}

/* returns a random darkroom description */
string
dark_description()
{
   string desc;
   switch (random(5))
   {
      case 0:
         desc = "You find yourself inside utter darkness.";
         break;
      case 1:
         desc = "A weak and chilling wind is all breaks the darkness.";
         break;
      case 2:
         desc = "You think you hear some sounds in front of you, but "+
                "without vision you cannot know what it comes from.";
         break;
      case 3:
         desc = "A dark room that envelopes you like a cloak of death.";
         break;
      case 4:
         desc = "You touch the wall to make sure you walk in the right "+
                "direction.";
         break;
      default: break;
   }
   
   return desc;
}

/* 
 * function: tracking
 * description: We check if the player has good enough tracking skill
 *              to see the right path in this room. Only if the skill
 *              is high enough, will we allow the player to use the
 *              exit. This function will return the description of the
 *              exits he/she has the skill to see.
 * returns: The exits seen by the player according to tracking skill
 */
string
tracking()
{
   int skill = TP->query_skill(SS_TRACKING);

   switch (skill)
   {
      case 0 .. 20:
      {
          return "You look around but cannot see any paths "+
             "leading out of here.";
          break;
      }
      default:
      {
          return "You notice some footsteps in the dust leading "+
             "towards the southeast and downwards.";
          break;
      }
   }
}

