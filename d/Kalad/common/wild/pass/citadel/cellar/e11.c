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
   set_long("Large boulders and stones litter this hallway, making "+
      "it hard to find any paths inbetween them. Among the stones "+
      "large cobwebs shines in the light you carry, making them "+
      "sparkle as being covered with gems. The shadows cast "+
      "by yourself dances in the light, and mingles with the "+
      "everdark areas at the edge of your view.\n\n" +

      /* exits are visible through the dagger wielded by
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
      "that you can follow.\n");
   add_item(({"path","paths"}), "You have a hard time to see "+
      "any paths here. @@tracking@@\n");

   /* gives random darkness descriptions. 'A dark room' is so boring. */
   add_prop(ROOM_S_DARK_LONG,"@@dark_description@@\n");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);

   add_exit(CPASS(citadel/cellar/e10),"west",0,3,1);
   add_exit(CPASS(citadel/cellar/e12),"southeast","@@walk",3,1);
}

/* give a feeling of walking on a path */
int
walk()
{
   int skill = TP->query_skill(SS_SPELLCRAFT);
   object dagger = TP->query_weapon(W_RIGHT);

   switch (skill)
   {
      case 0 .. 15:
      {
          TP -> catch_msg("A creepy silence seems to enclose you.\n");
          return 1;
          break;
      }
      default: break;
   }
   if (!dagger->query_prop("_korat_is_kabal_dagger")) 
   {
       TP->catch_msg("A creepy silence seems to enclose you.\n");
       return 1;
   }

   TP->catch_msg("You follow a twisting path that takes you further "+
       "into this underground area.\n");
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
 * description: We return the safe exits that the player
 *              has set in it. If they stray from the path,
 *              they end in a death trap.
 * returns: The exits shown by the dagger.
 */
string
tracking()
{
   int skill = TP->query_skill(SS_SPELLCRAFT);
   object dagger = TP->query_weapon(W_RIGHT);

   switch (skill)
   {
      case 0 .. 15:
      {
          return "A creepy silence seems to enclose you.";
          break;
      }
      default: break;
   }

   if (!dagger->query_prop("_korat_is_kabal_dagger"))
      return "A creepy silence seems to enclose you.";
   

   return "The pull in the dagger seems to pull you onwards "+
      "to the southeast.";
}

